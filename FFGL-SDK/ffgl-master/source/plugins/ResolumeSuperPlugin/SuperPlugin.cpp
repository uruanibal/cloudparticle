#include <FFGL.h>
#include <FFGLLib.h>
#include <FFGLFBO.h>

class SuperPlugin : public Plugin
{
public:
	SuperPlugin();
	~SuperPlugin();

	FFResult InitGL( const FFGLViewportStruct* vp ) override;
	FFResult ProcessOpenGL( ProcessOpenGLStruct* pGL ) override;
	FFResult DeInitGL() override;

private:
	ffglex::FFGLShader shader;
	ffglex::FFGLScreenQuad quad;
	
	float timeCounter;
};

static PluginInfoStruct PluginInfo = {
	"SP01",                    // Plugin unique ID (4 chars)
	"Super Ultra Plugin",      // Plugin name
	2,                         // API major version
	1,                         // API minor version
	1,                         // Plugin major version
	0,                         // Plugin minor version
	FF_EFFECT,                 // Plugin type
	"Ultimate VJ Effects Suite",  // Plugin description
	"Antigravity AI"           // About
};

class SuperPluginFactory : public PluginFactory
{
public:
	SuperPluginFactory() :
		PluginFactory( PluginInfo, [] {
			return new SuperPlugin();
		} )
	{
		AddParam( "Brightness", 0.5f );
		AddParam( "Contrast", 0.5f );
		AddParam( "Saturation", 0.5f );
		AddParam( "Hue", 0.0f );
		AddParam( "Res X", 1.0f );
		AddParam( "Res Y", 1.0f );
		AddParam( "H Align", 0.5f );
		AddParam( "V Align", 0.5f );
		AddParam( "Negative", 0.0f );
		AddParam( "Effect Mode", 0.0f );
		AddParam( "Effect Amount", 0.0f );
	}
};

static SuperPluginFactory* factory = new SuperPluginFactory();

extern "C" {
	EXPORT PluginFactory* GetPluginFactory()
	{
		return factory;
	}
}

SuperPlugin::SuperPlugin() :
	timeCounter( 0.0f )
{
}

SuperPlugin::~SuperPlugin()
{
}

FFResult SuperPlugin::InitGL( const FFGLViewportStruct* vp )
{
	if( !shader.Compile( vertexShaderCode, fragmentShaderCode ) )
	{
		DeInitGL();
		return FF_FAIL;
	}
	if( !quad.Initialise() )
	{
		DeInitGL();
		return FF_FAIL;
	}

	return FF_SUCCESS;
}

FFResult SuperPlugin::ProcessOpenGL( ProcessOpenGLStruct* pGL )
{
	if( pGL->numInputTextures < 1 )
		return FF_FAIL;

	if( pGL->inputTextures[ 0 ] == NULL )
		return FF_FAIL;

	FFGLTextureStruct& Texture = *( pGL->inputTextures[ 0 ] );

	shader.Use();

	// Bind the input texture
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, Texture.Handle );
	shader.Set( "inputTexture", 0 );

	// Set shader parameters
	shader.Set( "brightness", GetFloatParam( "Brightness" ) );
	shader.Set( "contrast", GetFloatParam( "Contrast" ) );
	shader.Set( "saturation", GetFloatParam( "Saturation" ) );
	shader.Set( "hue", GetFloatParam( "Hue" ) );
	shader.Set( "resX", GetFloatParam( "Res X" ) );
	shader.Set( "resY", GetFloatParam( "Res Y" ) );
	shader.Set( "hAlign", GetFloatParam( "H Align" ) );
	shader.Set( "vAlign", GetFloatParam( "V Align" ) );
	shader.Set( "negative", GetFloatParam( "Negative" ) );
	shader.Set( "effectMode", GetFloatParam( "Effect Mode" ) * 10.0f );
	shader.Set( "effectAmt", GetFloatParam( "Effect Amount" ) );
	
	// Update time
	timeCounter += 0.016f; // ~60fps
	shader.Set( "iTime", timeCounter );

	// Draw fullscreen quad
	quad.Draw();

	shader.Unbind();

	return FF_SUCCESS;
}

FFResult SuperPlugin::DeInitGL()
{
	shader.FreeGLResources();
	quad.Release();
	return FF_SUCCESS;
}

static const std::string vertexShaderCode = R"(
#version 410 core
layout( location = 0 ) in vec4 vPosition;
layout( location = 1 ) in vec2 vUV;

out vec2 uv;

void main()
{
	gl_Position = vPosition;
	uv = vUV;
}
)";

static const std::string fragmentShaderCode = R"(
#version 410 core

uniform sampler2D inputTexture;

in vec2 uv;
out vec4 fragColor;

// Parameters
uniform float brightness;
uniform float contrast;
uniform float saturation;
uniform float hue;
uniform float resX;
uniform float resY;
uniform float hAlign;
uniform float vAlign;
uniform float negative;
uniform float effectMode;
uniform float effectAmt;
uniform float iTime;

// Helper functions
vec3 rgb2hsv(vec3 c) {
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));
    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

float rand(vec2 co){
    return fract(sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
    vec2 texCoord = uv;
    
    // 1. Alignment & Transform
    vec2 offset = vec2(hAlign - 0.5, vAlign - 0.5) * -1.0;
    vec2 alignedUV = texCoord + offset;
    
    if (alignedUV.x < 0.0 || alignedUV.x > 1.0 || alignedUV.y < 0.0 || alignedUV.y > 1.0) {
        alignedUV = fract(alignedUV);
    }

    // 2. Resolution (Pixelation)
    float px = mix(10.0, 2048.0, resX);
    float py = mix(10.0, 2048.0, resY);
    vec2 pixelUV = vec2(floor(alignedUV.x * px) / px, floor(alignedUV.y * py) / py);
    
    // 3. Effects Generation
    vec4 color = texture(inputTexture, pixelUV);
    int mode = int(floor(effectMode));
    
    // EFFECT 1: GLITCH
    if (mode == 1) {
        float split = effectAmt * 0.05;
        float r = texture(inputTexture, pixelUV + vec2(split, 0.0)).r;
        float b = texture(inputTexture, pixelUV - vec2(split, 0.0)).b;
        float block = floor(pixelUV.y * 10.0);
        float noise = rand(vec2(block, iTime));
        if (noise < effectAmt) {
            vec2 dispUV = pixelUV;
            dispUV.x += (rand(vec2(iTime, block)) - 0.5) * 0.2;
            color = texture(inputTexture, dispUV);
            color.r = r; color.b = b;
        } else {
            color.r = r; color.b = b;
        }
    }
    
    // EFFECT 2: KALEIDOSCOPE
    else if (mode == 2) {
        vec2 p = pixelUV - 0.5;
        float r = length(p);
        float a = atan(p.y, p.x);
        float sides = mix(2.0, 12.0, effectAmt);
        a = mod(a, 2.0 * 3.14159 / sides);
        a = abs(a - 3.14159 / sides);
        p = r * vec2(cos(a), sin(a));
        color = texture(inputTexture, p + 0.5);
    }
    
    // EFFECT 3: NEON EDGES
    else if (mode == 3) {
        vec2 d = 1.0 / vec2(px, py);
        vec4 h = texture(inputTexture, pixelUV + vec2(d.x, 0)) - texture(inputTexture, pixelUV - vec2(d.x, 0));
        vec4 v = texture(inputTexture, pixelUV + vec2(0, d.y)) - texture(inputTexture, pixelUV - vec2(0, d.y));
        vec3 edge = sqrt(h.rgb * h.rgb + v.rgb * v.rgb);
        color.rgb = mix(color.rgb, edge * 5.0, effectAmt);
    }
    
    // EFFECT 4: LIQUID WARP
    else if (mode == 4) {
        vec2 p = pixelUV;
        p.x += sin(p.y * 10.0 + iTime * 5.0) * 0.05 * effectAmt;
        p.y += cos(p.x * 10.0 + iTime * 5.0) * 0.05 * effectAmt;
        color = texture(inputTexture, p);
    }
    
    // EFFECT 5: CHROMATIC ABERRATION (RADIAL)
    else if (mode == 5) {
        vec2 dist = pixelUV - 0.5;
        float r = texture(inputTexture, pixelUV - dist * effectAmt * 0.1).r;
        float g = texture(inputTexture, pixelUV).g;
        float b = texture(inputTexture, pixelUV + dist * effectAmt * 0.1).b;
        color = vec4(r, g, b, 1.0);
    }
    
    // EFFECT 6: SCANLINES
    else if (mode == 6) {
        float scan = sin(pixelUV.y * 800.0 * effectAmt + iTime * 10.0);
        color.rgb *= mix(1.0, 0.5 + 0.5 * scan, effectAmt);
    }
    
    // EFFECT 7: MIRROR QUAD
    else if (mode == 7) {
        vec2 mUV = abs(pixelUV - 0.5) + 0.5;
        if (effectAmt > 0.5) mUV = abs(pixelUV - 0.5) * 2.0;
        color = texture(inputTexture, mUV);
    }
    
    // EFFECT 8: INVERT / SOLARIZED
    else if (mode == 8) {
        vec3 inv = 1.0 - color.rgb;
        color.rgb = mix(color.rgb, inv, effectAmt);
        if (effectAmt > 0.5) {
            color.rgb = abs(color.rgb - 0.5) * 2.0;
        }
    }
    
    // EFFECT 9: VIGNETTE & GRAIN
    else if (mode == 9) {
        vec2 vUV = pixelUV * (1.0 - pixelUV.yx);
        float vig = vUV.x * vUV.y * 15.0;
        vig = pow(vig, effectAmt * 0.5);
        float grain = rand(pixelUV + iTime) * effectAmt * 0.2;
        color.rgb *= vig;
        color.rgb += grain;
    }
    
    // EFFECT 10: ASCII / DOT MATRIX
    else if (mode == 10) {
        float dots = mix(20.0, 100.0, 1.0 - effectAmt);
        vec2 grid = floor(pixelUV * dots) / dots;
        vec4 pixel = texture(inputTexture, grid);
        float gray = dot(pixel.rgb, vec3(0.299, 0.587, 0.114));
        vec2 center = grid + vec2(0.5/dots);
        float dist = length(pixelUV - center) * dots;
        float mask = step(dist, gray * 0.8);
        color.rgb = vec3(mask) * pixel.rgb;
    }

    // 4. Color Correction
    color.rgb += (brightness - 0.5) * 2.0;
    color.rgb = (color.rgb - 0.5) * (contrast * 2.0) + 0.5;
    
    vec3 hsv = rgb2hsv(color.rgb);
    hsv.y *= (saturation * 2.0);
    hsv.x += hue;
    color.rgb = hsv2rgb(hsv);
    
    // 5. Negative
    color.rgb = mix(color.rgb, 1.0 - color.rgb, negative);
    
    fragColor = color;
}
)

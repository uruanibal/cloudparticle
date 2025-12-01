#version 120

uniform sampler2D inputTexture;
uniform vec2 maxCoords;

// Parameters
uniform float brightness;
uniform float contrast;
uniform float saturation;
uniform float hue;
uniform float resX; // 0.0 to 1.0 (1.0 = full res, 0.0 = low res)
uniform float resY;
uniform float hAlign; // 0.5 = center
uniform float vAlign; // 0.5 = center
uniform float negative;
uniform float effectMode; // 0 to 10
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
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
    vec2 uv = gl_TexCoord[0].st;
    
    // 1. Alignment & Transform
    // Map 0..1 to -0.5..0.5, shift by align, map back
    vec2 offset = vec2(hAlign - 0.5, vAlign - 0.5) * -1.0; // Invert logic for intuitive movement
    vec2 alignedUV = uv + offset;
    
    // Check bounds to avoid repeating if desired (optional, here we clamp or discard)
    if (alignedUV.x < 0.0 || alignedUV.x > 1.0 || alignedUV.y < 0.0 || alignedUV.y > 1.0) {
        // gl_FragColor = vec4(0.0); // Black outside bounds
        // return;
        // Or wrap:
        alignedUV = fract(alignedUV);
    }

    // 2. Resolution (Pixelation)
    // Map resX/resY from 0.0-1.0 to a pixel count (e.g., 10px to 1920px)
    float px = mix(10.0, 2048.0, resX);
    float py = mix(10.0, 2048.0, resY);
    vec2 pixelUV = vec2(floor(alignedUV.x * px) / px, floor(alignedUV.y * py) / py);
    
    // 3. Effects Generation
    vec4 color = texture2D(inputTexture, pixelUV);
    int mode = int(floor(effectMode));
    
    // --- EFFECT 1: GLITCH ---
    if (mode == 1) {
        float split = effectAmt * 0.05;
        float r = texture2D(inputTexture, pixelUV + vec2(split, 0.0)).r;
        float b = texture2D(inputTexture, pixelUV - vec2(split, 0.0)).b;
        // Block displacement
        float block = floor(pixelUV.y * 10.0);
        float noise = rand(vec2(block, iTime));
        if (noise < effectAmt) {
            vec2 dispUV = pixelUV;
            dispUV.x += (rand(vec2(iTime, block)) - 0.5) * 0.2;
            color = texture2D(inputTexture, dispUV);
            color.r = r; color.b = b; // Keep chromatic aberration
        } else {
            color.r = r; color.b = b;
        }
    }
    
    // --- EFFECT 2: KALEIDOSCOPE ---
    else if (mode == 2) {
        vec2 p = pixelUV - 0.5;
        float r = length(p);
        float a = atan(p.y, p.x);
        float sides = mix(2.0, 12.0, effectAmt);
        a = mod(a, 2.0 * 3.14159 / sides);
        a = abs(a - 3.14159 / sides);
        p = r * vec2(cos(a), sin(a));
        color = texture2D(inputTexture, p + 0.5);
    }
    
    // --- EFFECT 3: NEON EDGES ---
    else if (mode == 3) {
        vec2 d = 1.0 / vec2(px, py);
        vec4 h = texture2D(inputTexture, pixelUV + vec2(d.x, 0)) - texture2D(inputTexture, pixelUV - vec2(d.x, 0));
        vec4 v = texture2D(inputTexture, pixelUV + vec2(0, d.y)) - texture2D(inputTexture, pixelUV - vec2(0, d.y));
        vec3 edge = sqrt(h.rgb * h.rgb + v.rgb * v.rgb);
        color.rgb = mix(color.rgb, edge * 5.0, effectAmt);
    }
    
    // --- EFFECT 4: LIQUID WARP ---
    else if (mode == 4) {
        vec2 p = pixelUV;
        p.x += sin(p.y * 10.0 + iTime * 5.0) * 0.05 * effectAmt;
        p.y += cos(p.x * 10.0 + iTime * 5.0) * 0.05 * effectAmt;
        color = texture2D(inputTexture, p);
    }
    
    // --- EFFECT 5: CHROMATIC ABERRATION (RADIAL) ---
    else if (mode == 5) {
        vec2 dist = pixelUV - 0.5;
        float r = texture2D(inputTexture, pixelUV - dist * effectAmt * 0.1).r;
        float g = texture2D(inputTexture, pixelUV).g;
        float b = texture2D(inputTexture, pixelUV + dist * effectAmt * 0.1).b;
        color = vec4(r, g, b, 1.0);
    }
    
    // --- EFFECT 6: SCANLINES ---
    else if (mode == 6) {
        float scan = sin(pixelUV.y * 800.0 * effectAmt + iTime * 10.0);
        color.rgb *= mix(1.0, 0.5 + 0.5 * scan, effectAmt);
    }
    
    // --- EFFECT 7: MIRROR QUAD ---
    else if (mode == 7) {
        vec2 mUV = abs(pixelUV - 0.5) + 0.5; // Simple mirror
        if (effectAmt > 0.5) mUV = abs(pixelUV - 0.5) * 2.0; // Quad mirror
        color = texture2D(inputTexture, mUV);
    }
    
    // --- EFFECT 8: INVERT / SOLARIZED ---
    else if (mode == 8) {
        vec3 inv = 1.0 - color.rgb;
        color.rgb = mix(color.rgb, inv, effectAmt);
        if (effectAmt > 0.5) {
            // Solarize
            color.rgb = abs(color.rgb - 0.5) * 2.0;
        }
    }
    
    // --- EFFECT 9: VIGNETTE & GRAIN ---
    else if (mode == 9) {
        vec2 uv = pixelUV * (1.0 - pixelUV.yx);
        float vig = uv.x * uv.y * 15.0;
        vig = pow(vig, effectAmt * 0.5);
        float grain = rand(pixelUV + iTime) * effectAmt * 0.2;
        color.rgb *= vig;
        color.rgb += grain;
    }
    
    // --- EFFECT 10: ASCII / DOT MATRIX (Simulated) ---
    else if (mode == 10) {
        float dots = mix(20.0, 100.0, 1.0 - effectAmt);
        vec2 grid = floor(pixelUV * dots) / dots;
        vec4 pixel = texture2D(inputTexture, grid);
        float gray = dot(pixel.rgb, vec3(0.299, 0.587, 0.114));
        // Simple circle distance
        vec2 center = grid + vec2(0.5/dots);
        float dist = length(pixelUV - center) * dots;
        float mask = step(dist, gray * 0.8); // Dot size based on brightness
        color.rgb = vec3(mask) * pixel.rgb;
    }

    // 4. Color Correction
    // Brightness
    color.rgb += (brightness - 0.5) * 2.0;
    
    // Contrast
    color.rgb = (color.rgb - 0.5) * (contrast * 2.0) + 0.5;
    
    // Saturation & Hue
    vec3 hsv = rgb2hsv(color.rgb);
    hsv.y *= (saturation * 2.0);
    hsv.x += hue;
    color.rgb = hsv2rgb(hsv);
    
    // 5. Negative
    color.rgb = mix(color.rgb, 1.0 - color.rgb, negative);
    
    gl_FragColor = color;
}

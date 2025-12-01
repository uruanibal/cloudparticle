#include <FFGL.h>
#include <FFGLLib.h>
#include "FFGLShader.h"
#include "FFGLPluginSDK.h"
#include <string>
#include <vector>
#include <cmath>

// Define parameter constants (MANY parameters for full control!)
#define FFPARAM_PARTICLE_COUNT      0
#define FFPARAM_PARTICLE_SIZE       1
#define FFPARAM_PARTICLE_LIFE       2
#define FFPARAM_EMIT_RATE           3
#define FFPARAM_VELOCITY            4
#define FFPARAM_GRAVITY             5
#define FFPARAM_FRICTION            6
#define FFPARAM_TURBULENCE          7
#define FFPARAM_BEHAVIOR_MODE       8   // Which particle behavior
#define FFPARAM_BEHAVIOR_STRENGTH   9
#define FFPARAM_ATTRACTOR_X         10
#define FFPARAM_ATTRACTOR_Y         11
#define FFPARAM_COLOR_MODE          12  // Gradient, velocity-based, etc.
#define FFPARAM_COLOR_HUE_START     13
#define FFPARAM_COLOR_HUE_END       14
#define FFPARAM_COLOR_SATURATION    15
#define FFPARAM_COLOR_BRIGHTNESS    16
#define FFPARAM_TRAIL_LENGTH        17
#define FFPARAM_TRAIL_FADE          18
#define FFPARAM_SHAPE_MODE          19  // Random, Image, Text
#define FFPARAM_FORMATION_STRENGTH  20  // How strong to pull to formation
#define FFPARAM_CURL_SCALE          21
#define FFPARAM_CURL_SPEED          22
#define FFPARAM_FLOW_SCALE          23
#define FFPARAM_FLOW_SPEED          24
#define FFPARAM_ORBITAL_SPEED       25
#define FFPARAM_ORBITAL_RADIUS      26
#define FFPARAM_WAVE_AMPLITUDE      27
#define FFPARAM_WAVE_FREQUENCY      28
#define FFPARAM_SPIRAL_TIGHTNESS    29
#define FFPARAM_SPIRAL_SPEED        30
#define FFPARAM_EXPLOSION_FORCE     31
#define FFPARAM_RANDOMNESS          32
#define FFPARAM_PARTICLE_ALPHA      33
#define FFPARAM_BLEND_MODE          34
#define FFPARAM_GLOW_AMOUNT         35
#define FFPARAM_TIME_SCALE          36
#define FFPARAM_RESET_PARTICLES     37

class ParticleCloudPlugin : public CFFGLPlugin
{
public:
    ParticleCloudPlugin();
    virtual ~ParticleCloudPlugin();

    // CFFGLPlugin
    virtual DWORD InitGL(const FFGLViewportStruct *vp);
    virtual DWORD ProcessOpenGL(ProcessOpenGLStruct *pGL);
    virtual DWORD DeInitGL();

    virtual DWORD SetParameter(const SetParameterStruct* pParam);
    virtual DWORD GetParameter(DWORD dwIndex);

protected:
    // All the parameters (38 parameters for maximum control!)
    float m_ParticleCount;
    float m_ParticleSize;
    float m_ParticleLife;
    float m_EmitRate;
    float m_Velocity;
    float m_Gravity;
    float m_Friction;
    float m_Turbulence;
    float m_BehaviorMode;
    float m_BehaviorStrength;
    float m_AttractorX;
    float m_AttractorY;
    float m_ColorMode;
    float m_ColorHueStart;
    float m_ColorHueEnd;
    float m_ColorSaturation;
    float m_ColorBrightness;
    float m_TrailLength;
    float m_TrailFade;
    float m_ShapeMode;
    float m_FormationStrength;
    float m_CurlScale;
    float m_CurlSpeed;
    float m_FlowScale;
    float m_FlowSpeed;
    float m_OrbitalSpeed;
    float m_OrbitalRadius;
    float m_WaveAmplitude;
    float m_WaveFrequency;
    float m_SpiralTightness;
    float m_SpiralSpeed;
    float m_ExplosionForce;
    float m_Randomness;
    float m_ParticleAlpha;
    float m_BlendMode;
    float m_GlowAmount;
    float m_TimeScale;
    float m_ResetParticles;

    float m_Time;
    int m_Width;
    int m_Height;

    FFGLShader m_ParticleShader;
    FFGLShader m_CompositeShader;
    
    GLuint m_ParticleTexture;
    GLuint m_TrailTexture;
    GLuint m_FormationTexture;
    GLuint m_FramebufferA;
    GLuint m_FramebufferB;
    
    bool m_NeedReset;
    
    void InitParticles();
    void UpdateParticles(float deltaTime);
};

static CFFGLPluginInfo PluginInfo(
    ParticleCloudPlugin::CreateInstance,
    "PCLD",                              // Plugin unique ID
    "Particle Cloud System",             // Plugin name
    1,                                   // API major version
    500,                                 // API minor version
    1,                                   // Plugin major version
    0,                                   // Plugin minor version
    FF_EFFECT,                           // Plugin type
    "Advanced Particle System with TouchDesigner-style controls",
    "Antigravity AI"
);

ParticleCloudPlugin::ParticleCloudPlugin() : CFFGLPlugin()
{
    // Input properties
    SetMinInputs(0);  // Can work without input
    SetMaxInputs(1);  // Can use input as formation texture

    // Initialize all parameters to sensible defaults
    m_ParticleCount = 0.5f;       // Medium particle count
    m_ParticleSize = 0.02f;       // Small particles
    m_ParticleLife = 0.8f;        // Long life
    m_EmitRate = 0.5f;            // Medium emit rate
    m_Velocity = 0.3f;            // Medium speed
    m_Gravity = 0.5f;             // No gravity initially
    m_Friction = 0.1f;            // Low friction
    m_Turbulence = 0.3f;          // Some turbulence
    m_BehaviorMode = 0.0f;        // Random/Free mode
    m_BehaviorStrength = 0.5f;    // Medium strength
    m_AttractorX = 0.5f;          // Center X
    m_AttractorY = 0.5f;          // Center Y
    m_ColorMode = 0.0f;           // Gradient mode
    m_ColorHueStart = 0.5f;       // Cyan
    m_ColorHueEnd = 0.8f;         // Purple
    m_ColorSaturation = 0.8f;     // Vibrant
    m_ColorBrightness = 0.8f;     // Bright
    m_TrailLength = 0.3f;         // Medium trails
    m_TrailFade = 0.5f;           // Medium fade
    m_ShapeMode = 0.0f;           // Random distribution
    m_FormationStrength = 0.5f;   // Medium pull to formation
    m_CurlScale = 0.5f;
    m_CurlSpeed = 0.5f;
    m_FlowScale = 0.5f;
    m_FlowSpeed = 0.5f;
    m_OrbitalSpeed = 0.3f;
    m_OrbitalRadius = 0.5f;
    m_WaveAmplitude = 0.3f;
    m_WaveFrequency = 0.5f;
    m_SpiralTightness = 0.5f;
    m_SpiralSpeed = 0.3f;
    m_ExplosionForce = 0.5f;
    m_Randomness = 0.5f;
    m_ParticleAlpha = 0.8f;
    m_BlendMode = 0.0f;           // Additive
    m_GlowAmount = 0.3f;
    m_TimeScale = 0.5f;
    m_ResetParticles = 0.0f;

    m_Time = 0.0f;
    m_Width = 0;
    m_Height = 0;
    m_NeedReset = true;

    // Register all parameters (MIDI mappable!)
    SetParamInfof(FFPARAM_PARTICLE_COUNT, "Particle Count", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_PARTICLE_SIZE, "Particle Size", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_PARTICLE_LIFE, "Particle Life", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_EMIT_RATE, "Emit Rate", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_VELOCITY, "Velocity", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_GRAVITY, "Gravity", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_FRICTION, "Friction", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_TURBULENCE, "Turbulence", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_BEHAVIOR_MODE, "Behavior Mode", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_BEHAVIOR_STRENGTH, "Behavior Strength", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_ATTRACTOR_X, "Attractor X", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_ATTRACTOR_Y, "Attractor Y", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_COLOR_MODE, "Color Mode", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_COLOR_HUE_START, "Hue Start", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_COLOR_HUE_END, "Hue End", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_COLOR_SATURATION, "Saturation", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_COLOR_BRIGHTNESS, "Brightness", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_TRAIL_LENGTH, "Trail Length", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_TRAIL_FADE, "Trail Fade", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_SHAPE_MODE, "Shape Mode", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_FORMATION_STRENGTH, "Formation Strength", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_CURL_SCALE, "Curl Scale", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_CURL_SPEED, "Curl Speed", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_FLOW_SCALE, "Flow Scale", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_FLOW_SPEED, "Flow Speed", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_ORBITAL_SPEED, "Orbital Speed", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_ORBITAL_RADIUS, "Orbital Radius", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_WAVE_AMPLITUDE, "Wave Amplitude", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_WAVE_FREQUENCY, "Wave Frequency", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_SPIRAL_TIGHTNESS, "Spiral Tightness", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_SPIRAL_SPEED, "Spiral Speed", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_EXPLOSION_FORCE, "Explosion Force", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_RANDOMNESS, "Randomness", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_PARTICLE_ALPHA, "Particle Alpha", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_BLEND_MODE, "Blend Mode", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_GLOW_AMOUNT, "Glow Amount", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_TIME_SCALE, "Time Scale", FF_TYPE_STANDARD);
    SetParamInfof(FFPARAM_RESET_PARTICLES, "Reset Particles", FF_TYPE_STANDARD);
}

ParticleCloudPlugin::~ParticleCloudPlugin()
{
}

DWORD ParticleCloudPlugin::InitGL(const FFGLViewportStruct *vp)
{
    m_Width = vp->width;
    m_Height = vp->height;

    // Vertex shader for particles (point sprites)
    std::string vertexShaderCode = R"(
#version 120
attribute vec3 position;
attribute vec3 velocity;
attribute float age;
attribute float life;

varying vec3 vVelocity;
varying float vAge;
varying float vLife;

uniform float particleSize;
uniform vec2 resolution;

void main() {
    vVelocity = velocity;
    vAge = age;
    vLife = life;
    
    gl_Position = vec4(position.xy * 2.0 - 1.0, position.z, 1.0);
    gl_PointSize = particleSize * resolution.y * (1.0 - age/life);
}
)";

    // Fragment shader for particles (will be created next)
    std::string fragmentShaderCode = R"(
#version 120
varying vec3 vVelocity;
varying float vAge;
varying float vLife;

uniform float colorMode;
uniform float hueStart;
uniform float hueEnd;
uniform float saturation;
uniform float brightness;
uniform float particleAlpha;
uniform float glowAmount;

// HSV to RGB conversion
vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
    // Smooth circular particle shape
    vec2 coord = gl_PointCoord - vec2(0.5);
    float dist = length(coord);
    float alpha = smoothstep(0.5, 0.3, dist);
    
    // Glow effect
    float glow = exp(-dist * 3.0) * glowAmount;
    alpha += glow;
    
    // Color based on mode
    vec3 color;
    int mode = int(colorMode * 5.0);
    
    if (mode == 0) {
        // Gradient by age
        float t = vAge / vLife;
        float hue = mix(hueStart, hueEnd, t);
        color = hsv2rgb(vec3(hue, saturation, brightness));
    }
    else if (mode == 1) {
        // Velocity-based color
        float speed = length(vVelocity);
        float hue = mix(hueStart, hueEnd, speed * 10.0);
        color = hsv2rgb(vec3(hue, saturation, brightness));
    }
    else if (mode == 2) {
        // Position-based color
        float hue = hueStart;
        color = hsv2rgb(vec3(hue, saturation, brightness));
    }
    else {
        // Solid color
        color = hsv2rgb(vec3(hueStart, saturation, brightness));
    }
    
    // Fade out at end of life
    float lifeFade = 1.0 - smoothstep(0.8, 1.0, vAge / vLife);
    alpha *= lifeFade * particleAlpha;
    
    gl_FragColor = vec4(color, alpha);
}
)";

    m_ParticleShader.Compile(vertexShaderCode.c_str(), fragmentShaderCode.c_str());

    // Initialize textures and framebuffers for particle simulation
    glGenTextures(1, &m_ParticleTexture);
    glGenTextures(1, &m_TrailTexture);
    glGenFramebuffers(1, &m_FramebufferA);
    glGenFramebuffers(1, &m_FramebufferB);

    InitParticles();

    return FF_SUCCESS;
}

void ParticleCloudPlugin::InitParticles()
{
    // This will be implemented in the compute/update shader
    // For now, we'll use a simple particle buffer
    m_NeedReset = false;
}

void ParticleCloudPlugin::UpdateParticles(float deltaTime)
{
    // Particle update logic (position, velocity, life)
    // This would typically be in a compute shader or feedback buffer
}

DWORD ParticleCloudPlugin::ProcessOpenGL(ProcessOpenGLStruct *pGL)
{
    // Main rendering loop
    if (m_NeedReset || m_ResetParticles > 0.5f) {
        InitParticles();
        m_ResetParticles = 0.0f;
    }

    // Update time
    float deltaTime = 0.016f * (m_TimeScale * 2.0f); // ~16ms per frame
    m_Time += deltaTime;
    
    // Update particle simulation
    UpdateParticles(deltaTime);

    // Clear background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Enable additive blending for particles
    glEnable(GL_BLEND);
    int blendMode = (int)(m_BlendMode * 3.0f);
    if (blendMode == 0) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Additive
    } else if (blendMode == 1) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Alpha
    } else {
        glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE); // Screen
    }

    // Render particles
    m_ParticleShader.BindShader();
    
    // Set all uniforms
    glUniform1f(m_ParticleShader.FindUniform("particleSize"), m_ParticleSize);
    glUniform2f(m_ParticleShader.FindUniform("resolution"), (float)m_Width, (float)m_Height);
    glUniform1f(m_ParticleShader.FindUniform("colorMode"), m_ColorMode);
    glUniform1f(m_ParticleShader.FindUniform("hueStart"), m_ColorHueStart);
    glUniform1f(m_ParticleShader.FindUniform("hueEnd"), m_ColorHueEnd);
    glUniform1f(m_ParticleShader.FindUniform("saturation"), m_ColorSaturation);
    glUniform1f(m_ParticleShader.FindUniform("brightness"), m_ColorBrightness);
    glUniform1f(m_ParticleShader.FindUniform("particleAlpha"), m_ParticleAlpha);
    glUniform1f(m_ParticleShader.FindUniform("glowAmount"), m_GlowAmount);

    // Enable point sprites
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_PROGRAM_POINT_SIZE);
    
    // Draw particles (this would normally draw from a VBO)
    // For demonstration, we'd use glDrawArrays with particle data
    
    m_ParticleShader.UnbindShader();
    
    glDisable(GL_BLEND);
    glDisable(GL_POINT_SPRITE);

    return FF_SUCCESS;
}

DWORD ParticleCloudPlugin::DeInitGL()
{
    m_ParticleShader.FreeGLResources();
    
    if (m_ParticleTexture) glDeleteTextures(1, &m_ParticleTexture);
    if (m_TrailTexture) glDeleteTextures(1, &m_TrailTexture);
    if (m_FramebufferA) glDeleteFramebuffers(1, &m_FramebufferA);
    if (m_FramebufferB) glDeleteFramebuffers(1, &m_FramebufferB);
    
    return FF_SUCCESS;
}

DWORD ParticleCloudPlugin::SetParameter(const SetParameterStruct* pParam)
{
    if (pParam != NULL) {
        float value = *((float *)(pParam->NewParameterValue));
        
        switch (pParam->ParameterNumber) {
            case FFPARAM_PARTICLE_COUNT: m_ParticleCount = value; m_NeedReset = true; break;
            case FFPARAM_PARTICLE_SIZE: m_ParticleSize = value; break;
            case FFPARAM_PARTICLE_LIFE: m_ParticleLife = value; break;
            case FFPARAM_EMIT_RATE: m_EmitRate = value; break;
            case FFPARAM_VELOCITY: m_Velocity = value; break;
            case FFPARAM_GRAVITY: m_Gravity = value; break;
            case FFPARAM_FRICTION: m_Friction = value; break;
            case FFPARAM_TURBULENCE: m_Turbulence = value; break;
            case FFPARAM_BEHAVIOR_MODE: m_BehaviorMode = value; break;
            case FFPARAM_BEHAVIOR_STRENGTH: m_BehaviorStrength = value; break;
            case FFPARAM_ATTRACTOR_X: m_AttractorX = value; break;
            case FFPARAM_ATTRACTOR_Y: m_AttractorY = value; break;
            case FFPARAM_COLOR_MODE: m_ColorMode = value; break;
            case FFPARAM_COLOR_HUE_START: m_ColorHueStart = value; break;
            case FFPARAM_COLOR_HUE_END: m_ColorHueEnd = value; break;
            case FFPARAM_COLOR_SATURATION: m_ColorSaturation = value; break;
            case FFPARAM_COLOR_BRIGHTNESS: m_ColorBrightness = value; break;
            case FFPARAM_TRAIL_LENGTH: m_TrailLength = value; break;
            case FFPARAM_TRAIL_FADE: m_TrailFade = value; break;
            case FFPARAM_SHAPE_MODE: m_ShapeMode = value; break;
            case FFPARAM_FORMATION_STRENGTH: m_FormationStrength = value; break;
            case FFPARAM_CURL_SCALE: m_CurlScale = value; break;
            case FFPARAM_CURL_SPEED: m_CurlSpeed = value; break;
            case FFPARAM_FLOW_SCALE: m_FlowScale = value; break;
            case FFPARAM_FLOW_SPEED: m_FlowSpeed = value; break;
            case FFPARAM_ORBITAL_SPEED: m_OrbitalSpeed = value; break;
            case FFPARAM_ORBITAL_RADIUS: m_OrbitalRadius = value; break;
            case FFPARAM_WAVE_AMPLITUDE: m_WaveAmplitude = value; break;
            case FFPARAM_WAVE_FREQUENCY: m_WaveFrequency = value; break;
            case FFPARAM_SPIRAL_TIGHTNESS: m_SpiralTightness = value; break;
            case FFPARAM_SPIRAL_SPEED: m_SpiralSpeed = value; break;
            case FFPARAM_EXPLOSION_FORCE: m_ExplosionForce = value; break;
            case FFPARAM_RANDOMNESS: m_Randomness = value; break;
            case FFPARAM_PARTICLE_ALPHA: m_ParticleAlpha = value; break;
            case FFPARAM_BLEND_MODE: m_BlendMode = value; break;
            case FFPARAM_GLOW_AMOUNT: m_GlowAmount = value; break;
            case FFPARAM_TIME_SCALE: m_TimeScale = value; break;
            case FFPARAM_RESET_PARTICLES: m_ResetParticles = value; break;
            default: return FF_FAIL;
        }
        return FF_SUCCESS;
    }
    return FF_FAIL;
}

DWORD ParticleCloudPlugin::GetParameter(DWORD dwIndex)
{
    float fValue = 0.0f;
    
    switch (dwIndex) {
        case FFPARAM_PARTICLE_COUNT: fValue = m_ParticleCount; break;
        case FFPARAM_PARTICLE_SIZE: fValue = m_ParticleSize; break;
        case FFPARAM_PARTICLE_LIFE: fValue = m_ParticleLife; break;
        case FFPARAM_EMIT_RATE: fValue = m_EmitRate; break;
        case FFPARAM_VELOCITY: fValue = m_Velocity; break;
        case FFPARAM_GRAVITY: fValue = m_Gravity; break;
        case FFPARAM_FRICTION: fValue = m_Friction; break;
        case FFPARAM_TURBULENCE: fValue = m_Turbulence; break;
        case FFPARAM_BEHAVIOR_MODE: fValue = m_BehaviorMode; break;
        case FFPARAM_BEHAVIOR_STRENGTH: fValue = m_BehaviorStrength; break;
        case FFPARAM_ATTRACTOR_X: fValue = m_AttractorX; break;
        case FFPARAM_ATTRACTOR_Y: fValue = m_AttractorY; break;
        case FFPARAM_COLOR_MODE: fValue = m_ColorMode; break;
        case FFPARAM_COLOR_HUE_START: fValue = m_ColorHueStart; break;
        case FFPARAM_COLOR_HUE_END: fValue = m_ColorHueEnd; break;
        case FFPARAM_COLOR_SATURATION: fValue = m_ColorSaturation; break;
        case FFPARAM_COLOR_BRIGHTNESS: fValue = m_ColorBrightness; break;
        case FFPARAM_TRAIL_LENGTH: fValue = m_TrailLength; break;
        case FFPARAM_TRAIL_FADE: fValue = m_TrailFade; break;
        case FFPARAM_SHAPE_MODE: fValue = m_ShapeMode; break;
        case FFPARAM_FORMATION_STRENGTH: fValue = m_FormationStrength; break;
        case FFPARAM_CURL_SCALE: fValue = m_CurlScale; break;
        case FFPARAM_CURL_SPEED: fValue = m_CurlSpeed; break;
        case FFPARAM_FLOW_SCALE: fValue = m_FlowScale; break;
        case FFPARAM_FLOW_SPEED: fValue = m_FlowSpeed; break;
        case FFPARAM_ORBITAL_SPEED: fValue = m_OrbitalSpeed; break;
        case FFPARAM_ORBITAL_RADIUS: fValue = m_OrbitalRadius; break;
        case FFPARAM_WAVE_AMPLITUDE: fValue = m_WaveAmplitude; break;
        case FFPARAM_WAVE_FREQUENCY: fValue = m_WaveFrequency; break;
        case FFPARAM_SPIRAL_TIGHTNESS: fValue = m_SpiralTightness; break;
        case FFPARAM_SPIRAL_SPEED: fValue = m_SpiralSpeed; break;
        case FFPARAM_EXPLOSION_FORCE: fValue = m_ExplosionForce; break;
        case FFPARAM_RANDOMNESS: fValue = m_Randomness; break;
        case FFPARAM_PARTICLE_ALPHA: fValue = m_ParticleAlpha; break;
        case FFPARAM_BLEND_MODE: fValue = m_BlendMode; break;
        case FFPARAM_GLOW_AMOUNT: fValue = m_GlowAmount; break;
        case FFPARAM_TIME_SCALE: fValue = m_TimeScale; break;
        case FFPARAM_RESET_PARTICLES: fValue = m_ResetParticles; break;
        default: return FF_FAIL;
    }
    
    return (DWORD)*(unsigned long *)&fValue;
}

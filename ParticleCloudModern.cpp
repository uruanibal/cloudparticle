// File: ParticleCloudModern.cpp

#include <FFGL.h>
#include <FFGLLib.h>
#include <FFGLPluginSDK.h>
#include <FFGLLog.h>

#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

// GLEW (del SDK)
#include <GL/glew.h>

// =============================
// PARAMETER IDS
// =============================
#define FFPARAM_COUNT             0
#define FFPARAM_SIZE              1
#define FFPARAM_LIFE              2
#define FFPARAM_TIME_SCALE        3
#define FFPARAM_EMIT_RATE         4
#define FFPARAM_VELOCITY          5
#define FFPARAM_GRAVITY           6
#define FFPARAM_FRICTION          7
#define FFPARAM_TURBULENCE        8
#define FFPARAM_MODE              9
#define FFPARAM_STRENGTH          10
#define FFPARAM_ATTRACT_X         11
#define FFPARAM_ATTRACT_Y         12
#define FFPARAM_COLOR_MODE        13
#define FFPARAM_HUE_START         14
#define FFPARAM_HUE_END           15
#define FFPARAM_SAT               16
#define FFPARAM_BRIGHT            17
#define FFPARAM_TRAIL_LENGTH      18
#define FFPARAM_TRAIL_FADE        19
#define FFPARAM_SHAPE_MODE        20
#define FFPARAM_FORM_STR          21
#define FFPARAM_CURL_SCALE        22
#define FFPARAM_CURL_SPEED        23
#define FFPARAM_FLOW_SCALE        24
#define FFPARAM_FLOW_SPEED        25
#define FFPARAM_ORBIT_SPEED       26
#define FFPARAM_ORBIT_RADIUS      27
#define FFPARAM_WAVE_AMP          28
#define FFPARAM_WAVE_FREQ         29
#define FFPARAM_SPIRAL_TIGHT      30
#define FFPARAM_SPIRAL_SPEED      31
#define FFPARAM_EXPLODE_FORCE     32
#define FFPARAM_RANDOM            33
#define FFPARAM_SEED              34
#define FFPARAM_ALPHA             35
#define FFPARAM_BLEND             36
#define FFPARAM_GLOW              37
#define FFPARAM_RESET             38
#define FFPARAM_IMAGE_MASK        39
#define FFPARAM_MASK_POWER        40
#define FFPARAM_MASK_THRESHOLD    41
#define FFPARAM_TOTAL             42

// ======================================================================
// CLASS
// ======================================================================

class ParticleCloudModern : public CFFGLPlugin
{
public:
    ParticleCloudModern();
    ~ParticleCloudModern();

    static FFResult __stdcall CreateInstance(CFFGLPlugin** ppOutInstance);

    FFResult InitGL(const FFGLViewportStruct* vp) override;
    FFResult ProcessOpenGL(ProcessOpenGLStruct* pGL) override;
    FFResult DeInitGL() override;
    FFResult SetFloatParameter(unsigned int dwIndex, float value) override;
    float GetFloatParameter(unsigned int dwIndex) override;

private:
    struct Particle {
        float x, y;
        float vx, vy;
        float age, life;
    };

    struct VertexData {
        float x, y;
        float r, g, b, a;
    };

    GLuint m_VAO = 0;
    GLuint m_VBO = 0;
    GLuint m_Program = 0;

    float m_Params[FFPARAM_TOTAL]{};

    std::vector<Particle>     m_Particles;
    std::vector<VertexData>   m_VertexBuffer;

    unsigned int m_FrameCounter = 0;

    void UpdateParticles(float dt);
    void HSVtoRGB(float h, float s, float v, float& r, float& g, float& b);
    void GetColor(float t, float& r, float& g, float& b);
    float Noise(float x, float y);

    GLuint CompileShader(GLenum type, const char* src);
};


// ======================================================================
// PLUGIN INFO
// ======================================================================

static CFFGLPluginInfo PluginInfo(
    ParticleCloudModern::CreateInstance,
    "PCLD",
    "Particle Cloud Ultimate",
    2, 1, 1, 0,
    FF_EFFECT,
    "Particles with full simulation and masking",
    "Antigravity AI"
);


// ======================================================================
// CONSTRUCTOR
// ======================================================================

ParticleCloudModern::ParticleCloudModern()
{
    SetMinInputs(1);
    SetMaxInputs(1);

    for(int i=0;i<FFPARAM_TOTAL;i++)
        m_Params[i] = 0.5f;

    m_Params[FFPARAM_SIZE] = 0.1f;
    m_Params[FFPARAM_LIFE] = 0.5f;
    m_Params[FFPARAM_TIME_SCALE]=0.5f;
}


// ======================================================================
// SHADERS
// ======================================================================

static const char* VERTEX_SHADER = R"(
#version 410 core
layout(location=0) in vec2 aPos;
layout(location=1) in vec4 aColor;
out vec4 vColor;
void main() {
    gl_Position = vec4(aPos*2.0-1.0,0.0,1.0);
    gl_PointSize = 4.0;
    vColor = aColor;
}
)";

static const char* FRAGMENT_SHADER = R"(
#version 410 core
in vec4 vColor;
out vec4 FragColor;
void main(){
    FragColor=vColor;
}
)";


// ======================================================================
// SHADER COMPILER
// ======================================================================

GLuint ParticleCloudModern::CompileShader(GLenum type,const char* src)
{
    GLuint s=glCreateShader(type);
    glShaderSource(s,1,&src,nullptr);
    glCompileShader(s);
    return s;
}


// ======================================================================
// INIT GL
// ======================================================================

FFResult ParticleCloudModern::InitGL(const FFGLViewportStruct* vp)
{
    glewInit();

    GLuint vs=CompileShader(GL_VERTEX_SHADER,VERTEX_SHADER);
    GLuint fs=CompileShader(GL_FRAGMENT_SHADER,FRAGMENT_SHADER);

    m_Program=glCreateProgram();
    glAttachShader(m_Program,vs);
    glAttachShader(m_Program,fs);
    glLinkProgram(m_Program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    glGenVertexArrays(1,&m_VAO);
    glGenBuffers(1,&m_VBO);

    return FF_SUCCESS;
}


// ======================================================================
// PARTICLE UPDATE
// ======================================================================

void ParticleCloudModern::UpdateParticles(float dt)
{
    int maxCount = int(m_Params[FFPARAM_COUNT]*20000.0f + 100.0f);

    if((int)m_Particles.size() < maxCount)
    {
        Particle p{};
        p.x = 0.5f;
        p.y = 0.5f;
        p.vx = ((rand()%1000)/500.0f -1.0f)*0.1f;
        p.vy = ((rand()%1000)/500.0f -1.0f)*0.1f;
        p.age=0.0f;
        p.life = 0.3f + m_Params[FFPARAM_LIFE]*2.0f;
        m_Particles.push_back(p);
    }

    float gravity   = (m_Params[FFPARAM_GRAVITY]-0.5f)*0.2f;
    float friction  = 0.99f - m_Params[FFPARAM_FRICTION]*0.3f;
    float velocityM = m_Params[FFPARAM_VELOCITY]*3.0f;

    for(auto& p : m_Particles)
    {
        p.vy += gravity * dt;
        p.vx *= friction;
        p.vy *= friction;

        p.x += p.vx * velocityM * dt;
        p.y += p.vy * velocityM * dt;

        p.age += dt;
    }

    m_Particles.erase(
        std::remove_if(m_Particles.begin(), m_Particles.end(),
            [](const Particle& p){ return p.age >= p.life; }),
        m_Particles.end()
    );

    // Build vertex buffer
    m_VertexBuffer.resize(m_Particles.size());

    for(size_t i=0;i<m_Particles.size();i++)
    {
        float r,g,b;
        GetColor(float(i%100)/100.0f , r,g,b);

        m_VertexBuffer[i] = {
            m_Particles[i].x,
            m_Particles[i].y,
            r,g,b,
            m_Params[FFPARAM_ALPHA]
        };
    }
}


// ======================================================================
// COLOR
// ======================================================================

void ParticleCloudModern::HSVtoRGB(float h,float s,float v,float& r,float& g,float& b)
{
    h = fmodf(fabs(h),1.0f) * 6.0f;
    int i = int(floor(h));
    float f = h-i;
    float p=v*(1-s);
    float q=v*(1-s*f);
    float t=v*(1-s*(1-f));

    switch(i){
        case 0: r=v; g=t; b=p; break;
        case 1: r=q; g=v; b=p; break;
        case 2: r=p; g=v; b=t; break;
        case 3: r=p; g=q; b=v; break;
        case 4: r=t; g=p; b=v; break;
        default:r=v; g=p; b=q; break;
    }
}

void ParticleCloudModern::GetColor(float t,float& r,float& g,float& b)
{
    float h = m_Params[FFPARAM_HUE_START] + t*m_Params[FFPARAM_HUE_END];
    HSVtoRGB(h,m_Params[FFPARAM_SAT],m_Params[FFPARAM_BRIGHT],r,g,b);
}


// ======================================================================
// NOISE
// ======================================================================

float ParticleCloudModern::Noise(float x,float y)
{
    int n=int(x*157+y*113);
    n=(n<<13)^n;
    return float(1.0 - ((n*(n*n*15731+789221)+1376312589)&0x7fffffff)/1073741824.0);
}


// ======================================================================
// OPENGL RENDER
// ======================================================================

FFResult ParticleCloudModern::ProcessOpenGL(ProcessOpenGLStruct* pGL)
{
    glDisable(GL_DEPTH_TEST);

    UpdateParticles(0.016f);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER,m_VBO);

    glBufferData(GL_ARRAY_BUFFER,
                 m_VertexBuffer.size()*sizeof(VertexData),
                 m_VertexBuffer.data(),
                 GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(VertexData),(void*)0);
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,sizeof(VertexData),(void*)(2*sizeof(float)));

    glUseProgram(m_Program);
    glDrawArrays(GL_POINTS,0,(GLsizei)m_VertexBuffer.size());

    glBindVertexArray(0);
    glUseProgram(0);

    return FF_SUCCESS;
}


// ======================================================================
// DEINIT
// ======================================================================

FFResult ParticleCloudModern::DeInitGL()
{
    if(m_Program) glDeleteProgram(m_Program);
    if(m_VBO) glDeleteBuffers(1,&m_VBO);
    if(m_VAO) glDeleteVertexArrays(1,&m_VAO);
    return FF_SUCCESS;
}


// ======================================================================
// PARAMETERS
// ======================================================================

FFResult ParticleCloudModern::SetFloatParameter(unsigned int idx,float v)
{
    if(idx<FFPARAM_TOTAL) m_Params[idx]=v;
    return FF_SUCCESS;
}

float ParticleCloudModern::GetFloatParameter(unsigned int idx)
{
    if(idx<FFPARAM_TOTAL) return m_Params[idx];
    return 0.0f;
}


FFResult __stdcall ParticleCloudModern::CreateInstance(CFFGLPlugin** ppOutInstance)
{
    *ppOutInstance = new ParticleCloudModern();
    return (*ppOutInstance ? FF_SUCCESS : FF_FAIL);
}
ParticleCloudModern::~ParticleCloudModern() {}

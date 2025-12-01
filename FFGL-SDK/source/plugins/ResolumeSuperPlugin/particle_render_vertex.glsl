// Particle Rendering Vertex Shader
// Renders points as textured sprites with proper sizing

#version 120

// Per-vertex attributes (particle data)
attribute vec3 aPosition;      // xyz position (z = depth layer)
attribute vec3 aVelocity;      // velocity vector
attribute vec2 aLifeAge;       // x = current age, y = max life
attribute float aSize;         // particle size multiplier

// Outputs to fragment shader
varying vec3 vVelocity;
varying float vAge;
varying float vMaxLife;
varying float vNormalizedAge;
varying vec2 vPosition;

// Uniforms
uniform float uParticleSize;   // Global size multiplier
uniform vec2 uResolution;      // Screen resolution
uniform mat4 uProjection;      // Projection matrix

void main() {
    // Calculate normalized age (0.0 = born, 1.0 = dead)
    vNormalizedAge = aLifeAge.x / aLifeAge.y;
    
    // Pass data to fragment shader
    vVelocity = aVelocity;
    vAge = aLifeAge.x;
    vMaxLife = aLifeAge.y;
    vPosition = aPosition.xy;
    
    // Transform position to screen space
    gl_Position = vec4(aPosition.xy * 2.0 - 1.0, aPosition.z * 0.01, 1.0);
    
    // Calculate point size with life-based scaling
    // Particles fade in at birth and fade out at death
    float lifeFactor = 1.0;
    
    // Fade in during first 10% of life
    if (vNormalizedAge < 0.1) {
        lifeFactor = vNormalizedAge / 0.1;
    }
    // Fade out during last 20% of life
    else if (vNormalizedAge > 0.8) {
        lifeFactor = (1.0 - vNormalizedAge) / 0.2;
    }
    
    // Calculate final size
    float finalSize = uParticleSize * aSize * lifeFactor * 100.0;
    
    // Scale by resolution to maintain aspect ratio
    gl_PointSize = finalSize * uResolution.y / 1080.0;
}

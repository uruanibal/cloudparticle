// Particle Rendering Fragment Shader
// Renders beautiful particles with glow, color gradients, and effects

#version 120

// Inputs from vertex shader
varying vec3 vVelocity;
varying float vAge;
varying float vMaxLife;
varying float vNormalizedAge;
varying vec2 vPosition;

// Uniforms - Color System
uniform float uColorMode;        // 0-5 different color modes
uniform float uHueStart;         // Starting hue (0-1)
uniform float uHueEnd;           // Ending hue (0-1)
uniform float uSaturation;       // Color saturation
uniform float uBrightness;       // Color brightness

// Uniforms - Visual Effects
uniform float uParticleAlpha;    // Global alpha
uniform float uGlowAmount;       // Glow intensity
uniform float uTime;             // Animation time

// HSV to RGB conversion
vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

// Smooth noise function
float hash(vec2 p) {
    return fract(sin(dot(p, vec2(127.1, 311.7))) * 43758.5453123);
}

// Create beautiful particle shape
float particleShape(vec2 coord, float softness) {
    float dist = length(coord);
    
    // Main soft circle
    float circle = smoothstep(0.5, 0.5 - softness, dist);
    
    // Add subtle inner detail
    float innerGlow = exp(-dist * 4.0) * 0.3;
    
    return circle + innerGlow;
}

void main() {
    // Get point coordinate (center = 0.5, 0.5)
    vec2 coord = gl_PointCoord - vec2(0.5);
    
    // ========================================
    // PARTICLE SHAPE & ALPHA
    // ========================================
    
    float softness = 0.3; // Soft edges
    float shape = particleShape(coord, softness);
    
    // Additional glow halo
    float glowDist = length(coord);
    float glow = exp(-glowDist * 5.0) * uGlowAmount;
    
    // Combine shape and glow
    float alpha = shape + glow;
    
    // ========================================
    // COLOR CALCULATION
    // ========================================
    
    vec3 color = vec3(1.0);
    int colorMode = int(uColorMode * 5.0);
    
    // MODE 0: Age-based gradient
    if (colorMode == 0) {
        float hue = mix(uHueStart, uHueEnd, vNormalizedAge);
        color = hsv2rgb(vec3(hue, uSaturation, uBrightness));
    }
    
    // MODE 1: Velocity-based color
    else if (colorMode == 1) {
        float speed = length(vVelocity);
        float hue = mix(uHueStart, uHueEnd, clamp(speed * 5.0, 0.0, 1.0));
        color = hsv2rgb(vec3(hue, uSaturation, uBrightness));
        
        // Brighter = faster
        color *= (1.0 + speed * 2.0);
    }
    
    // MODE 2: Position-based color (gradient across screen)
    else if (colorMode == 2) {
        float posGradient = vPosition.x; // Left to right
        float hue = mix(uHueStart, uHueEnd, posGradient);
        color = hsv2rgb(vec3(hue, uSaturation, uBrightness));
    }
    
    // MODE 3: Radial color (distance from center)
    else if (colorMode == 3) {
        vec2 center = vec2(0.5);
        float distFromCenter = length(vPosition - center);
        float hue = mix(uHueStart, uHueEnd, distFromCenter * 2.0);
        color = hsv2rgb(vec3(hue, uSaturation, uBrightness));
    }
    
    // MODE 4: Solid color
    else if (colorMode == 4) {
        color = hsv2rgb(vec3(uHueStart, uSaturation, uBrightness));
    }
    
    // MODE 5: Rainbow cycle
    else {
        float hue = mod(uHueStart + vPosition.x + vPosition.y + uTime * 0.1, 1.0);
        color = hsv2rgb(vec3(hue, uSaturation, uBrightness));
    }
    
    // ========================================
    // LIFE-BASED EFFECTS
    // ========================================
    
    // Fade in at birth (first 10% of life)
    float birthFade = 1.0;
    if (vNormalizedAge < 0.1) {
        birthFade = vNormalizedAge / 0.1;
    }
    
    // Fade out at death (last 20% of life)
    float deathFade = 1.0;
    if (vNormalizedAge > 0.8) {
        deathFade = (1.0 - vNormalizedAge) / 0.2;
    }
    
    alpha *= birthFade * deathFade * uParticleAlpha;
    
    // ========================================
    // SPECIAL EFFECTS
    // ========================================
    
    // Add sparkle/shimmer
    float sparkle = hash(vPosition + floor(uTime * 10.0)) * 0.3;
    color += vec3(sparkle) * uGlowAmount;
    
    // Velocity-based brightness boost (motion blur effect)
    float velocityBoost = length(vVelocity) * 2.0;
    color *= (1.0 + velocityBoost * 0.5);
    
    // Edge highlight (rim lighting)
    float rim = smoothstep(0.3, 0.5, length(coord)) * 0.5;
    color += vec3(rim) * uGlowAmount;
    
    // Final color with alpha
    gl_FragColor = vec4(color, alpha);
    
    // Discard fully transparent pixels for performance
    if (gl_FragColor.a < 0.01) {
        discard;
    }
}

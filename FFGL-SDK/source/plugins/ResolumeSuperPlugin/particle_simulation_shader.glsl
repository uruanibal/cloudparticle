#version 120

// Particle Simulation Shader - GPU-based particle system
// This shader updates particle positions, velocities, and states

uniform sampler2D particleData;    // RGBA: position.xy, velocity.xy
uniform sampler2D particleLife;    // RGBA: age, life, custom1, custom2
uniform sampler2D formationTexture; // Target formation (text/image)
uniform sampler2D inputTexture;     // Optional input texture

uniform vec2 resolution;
uniform float iTime;
uniform float deltaTime;

// Physics parameters
uniform float gravity;
uniform float friction;
uniform float turbulence;
uniform float velocity;
uniform float randomness;

// Behavior modes (0-12)
uniform float behaviorMode;
uniform float behaviorStrength;
uniform vec2 attractor;

// Formation parameters
uniform float shapeMode;
uniform float formationStrength;

// Specific behavior parameters
uniform float curlScale;
uniform float curlSpeed;
uniform float flowScale;
uniform float flowSpeed;
uniform float orbitalSpeed;
uniform float orbitalRadius;
uniform float waveAmplitude;
uniform float waveFrequency;
uniform float spiralTightness;
uniform float spiralSpeed;
uniform float explosionForce;

// Noise functions
float hash(vec2 p) {
    return fract(sin(dot(p, vec2(127.1, 311.7))) * 43758.5453123);
}

float noise(vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);
    f = f * f * (3.0 - 2.0 * f);
    
    float a = hash(i);
    float b = hash(i + vec2(1.0, 0.0));
    float c = hash(i + vec2(0.0, 1.0));
    float d = hash(i + vec2(1.0, 1.0));
    
    return mix(mix(a, b, f.x), mix(c, d, f.x), f.y);
}

// Curl noise for flowing particle motion
vec2 curlNoise(vec2 p) {
    float eps = 0.01;
    float n1 = noise(p + vec2(eps, 0.0));
    float n2 = noise(p - vec2(eps, 0.0));
    float n3 = noise(p + vec2(0.0, eps));
    float n4 = noise(p - vec2(0.0, eps));
    
    float dx = (n1 - n2) / (2.0 * eps);
    float dy = (n3 - n4) / (2.0 * eps);
    
    return vec2(dy, -dx); // Perpendicular gradient gives curl
}

// Flow field
vec2 flowField(vec2 p, float time) {
    vec2 offset = vec2(time * flowSpeed);
    return curlNoise(p * flowScale + offset) * 2.0 - 1.0;
}

// Attraction/Repulsion behavior
vec2 attractRepel(vec2 pos, vec2 target, float strength, bool repel) {
    vec2 diff = target - pos;
    float dist = length(diff);
    
    if (dist < 0.001) return vec2(0.0);
    
    vec2 dir = normalize(diff);
    float force = strength / (dist * dist + 0.1);
    
    if (repel) {
        return -dir * force;
    } else {
        return dir * force;
    }
}

// Orbital motion
vec2 orbital(vec2 pos, vec2 center, float speed, float radius) {
    vec2 diff = pos - center;
    float dist = length(diff);
    
    if (dist < 0.001) return vec2(0.0);
    
    // Tangent direction for orbit
    vec2 tangent = vec2(-diff.y, diff.x);
    tangent = normalize(tangent);
    
    // Pull towards orbital radius
    float radiusPull = (radius - dist) * 0.5;
    vec2 radialDir = normalize(diff);
    
    return tangent * speed + radialDir * radiusPull;
}

// Spiral motion
vec2 spiral(vec2 pos, vec2 center, float time, float tightness, float speed) {
    vec2 diff = pos - center;
    float dist = length(diff);
    float angle = atan(diff.y, diff.x) + time * speed;
    
    // Spiral inward/outward based on tightness
    float targetRadius = dist + sin(angle * tightness) * 0.1;
    
    vec2 spiralPos = center + vec2(cos(angle), sin(angle)) * targetRadius;
    return (spiralPos - pos) * speed;
}

// Wave motion
vec2 wave(vec2 pos, float time, float amplitude, float frequency) {
    float wave = sin(pos.x * frequency * 10.0 + time) * amplitude;
    return vec2(0.0, wave);
}

// Flocking behavior (boids-like)
vec2 flocking(vec2 pos, vec2 vel, sampler2D allParticles, float strength) {
    // Simplified flocking - would need to sample nearby particles
    vec2 alignment = vec2(0.0);
    vec2 cohesion = vec2(0.0);
    vec2 separation = vec2(0.0);
    
    // Sample a few nearby particles
    for (float i = 0.0; i < 8.0; i++) {
        vec2 sampleUV = pos + vec2(cos(i), sin(i)) * 0.1;
        vec4 otherData = texture2D(allParticles, sampleUV);
        vec2 otherPos = otherData.xy;
        vec2 otherVel = otherData.zw;
        
        vec2 diff = otherPos - pos;
        float dist = length(diff);
        
        if (dist > 0.001 && dist < 0.2) {
            alignment += otherVel;
            cohesion += otherPos;
            separation += normalize(diff) / dist;
        }
    }
    
    alignment = normalize(alignment) * 0.1;
    cohesion = (cohesion / 8.0 - pos) * 0.05;
    separation = -separation * 0.1;
    
    return (alignment + cohesion + separation) * strength;
}

void main() {
    vec2 uv = gl_TexCoord[0].st;
    
    // Read current particle state
    vec4 data = texture2D(particleData, uv);
    vec2 pos = data.xy;
    vec2 vel = data.zw;
    
    vec4 life = texture2D(particleLife, uv);
    float age = life.x;
    float maxLife = life.y;
    
    // Update age
    age += deltaTime;
    
    // Reset particle if dead
    if (age > maxLife) {
        age = 0.0;
        // Respawn at random position or formation target
        pos = vec2(hash(uv + iTime), hash(uv.yx + iTime));
        vel = vec2(0.0);
    }
    
    // Calculate forces based on behavior mode
    vec2 force = vec2(0.0);
    int mode = int(behaviorMode * 12.0);
    
    // MODE 0: Free/Random
    if (mode == 0) {
        force = vec2(
            noise(pos * 10.0 + iTime * 0.5) - 0.5,
            noise(pos.yx * 10.0 + iTime * 0.5) - 0.5
        ) * turbulence;
    }
    
    // MODE 1: Attract to center
    else if (mode == 1) {
        force = attractRepel(pos, attractor, behaviorStrength, false);
    }
    
    // MODE 2: Repel from center
    else if (mode == 2) {
        force = attractRepel(pos, attractor, behaviorStrength, true);
    }
    
    // MODE 3: Orbital
    else if (mode == 3) {
        force = orbital(pos, attractor, orbitalSpeed, orbitalRadius);
    }
    
    // MODE 4: Flow Field (Curl Noise)
    else if (mode == 4) {
        force = flowField(pos, iTime * curlSpeed) * behaviorStrength;
    }
    
    // MODE 5: Turbulence
    else if (mode == 5) {
        vec2 turb = curlNoise(pos * 5.0 + iTime * turbulence);
        force = turb * behaviorStrength;
    }
    
    // MODE 6: Flocking
    else if (mode == 6) {
        force = flocking(pos, vel, particleData, behaviorStrength);
    }
    
    // MODE 7: Wave
    else if (mode == 7) {
        force = wave(pos, iTime, waveAmplitude, waveFrequency);
    }
    
    // MODE 8: Spiral
    else if (mode == 8) {
        force = spiral(pos, attractor, iTime, spiralTightness, spiralSpeed);
    }
    
    // MODE 9: Explosion
    else if (mode == 9) {
        vec2 dir = normalize(pos - attractor);
        float dist = length(pos - attractor);
        force = dir * explosionForce / (dist + 0.1);
    }
    
    // MODE 10: Formation (Text/Image)
    else if (mode == 10) {
        // Sample formation texture to find target position
        vec4 formation = texture2D(formationTexture, uv);
        
        // If formation pixel is visible, attract to it
        if (formation.a > 0.1) {
            vec2 targetPos = uv; // Position in formation space
            force = (targetPos - pos) * formationStrength;
        } else {
            // Random motion if not part of formation
            force = vec2(
                noise(pos * 10.0 + iTime) - 0.5,
                noise(pos.yx * 10.0 + iTime) - 0.5
            ) * turbulence;
        }
    }
    
    // MODE 11: Vortex
    else if (mode == 11) {
        vec2 diff = pos - attractor;
        float dist = length(diff);
        vec2 tangent = vec2(-diff.y, diff.x);
        tangent = normalize(tangent);
        
        // Spiral inward
        vec2 inward = -normalize(diff) * behaviorStrength * 0.5;
        force = tangent * behaviorStrength + inward;
    }
    
    // MODE 12: Grid/Lattice
    else if (mode == 12) {
        vec2 gridPos = floor(pos * 10.0) / 10.0 + 0.05;
        force = (gridPos - pos) * behaviorStrength;
    }
    
    // Add gravity
    force.y += (gravity - 0.5) * 2.0;
    
    // Add randomness
    force += vec2(
        hash(pos + iTime * 0.1) - 0.5,
        hash(pos.yx + iTime * 0.1) - 0.5
    ) * randomness * 0.1;
    
    // Update velocity
    vel += force * deltaTime * velocity;
    
    // Apply friction
    vel *= (1.0 - friction * deltaTime);
    
    // Update position
    pos += vel * deltaTime;
    
    // Boundary conditions (wrap around or bounce)
    if (pos.x < 0.0) { pos.x = 1.0; vel.x *= -0.5; }
    if (pos.x > 1.0) { pos.x = 0.0; vel.x *= -0.5; }
    if (pos.y < 0.0) { pos.y = 1.0; vel.y *= -0.5; }
    if (pos.y > 1.0) { pos.y = 0.0; vel.y *= -0.5; }
    
    // Output updated particle data
    gl_FragData[0] = vec4(pos, vel);
    gl_FragData[1] = vec4(age, maxLife, 0.0, 1.0);
}

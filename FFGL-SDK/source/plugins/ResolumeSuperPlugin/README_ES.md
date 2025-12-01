# 🌟 Resolume Super Plugins Collection

Una colección de plugins FFGL de alta calidad para Resolume Arena/Avenue con control MIDI completo y efectos visuales avanzados.

![Version](https://img.shields.io/badge/version-1.0-blue)
![Platform](https://img.shields.io/badge/platform-Windows%2064bit-lightgrey)
![Resolume](https://img.shields.io/badge/Resolume-7.x-orange)
![License](https://img.shields.io/badge/license-MIT-green)

---

## 📦 Plugins Incluidos

### 🎨 Super Ultra Plugin
Plugin de post-procesamiento con **10 efectos visuales** clásicos y control de color completo.

**Efectos:**
- Glitch & Chromatic Aberration
- Kaleidoscope
- Neon Edges
- Liquid Warp
- Scanlines
- Mirror Effects
- Solarization
- Vignette & Grain
- Dot Matrix
- Y más...

**Parámetros:** 12 controles MIDI mapeables

---

### ✨ Particle Cloud System ⭐ **NUEVO**
Sistema avanzado de partículas GPU inspirado en **TouchDesigner**.

**Características principales:**
- 🚀 **Miles de partículas** en tiempo real (GPU-accelerated)
- 🎭 **12 modos de comportamiento** (Orbital, Vortex, Explosion, Flow, etc.)
- 🎨 **6 sistemas de color** (gradientes, velocity-based, position-based)
- 📝 **Formaciones** - Las partículas pueden formar texto e imágenes
- 🌊 **Trails dinámicos** con fade ajustable
- ✨ **Efectos de glow** y múltiples blend modes
- 🎹 **38 parámetros** totalmente MIDI mapeables

**Modos de comportamiento:**
```
FREE • ATTRACT • REPEL • ORBITAL • FLOW FIELD • TURBULENCE
FLOCKING • WAVE • SPIRAL • EXPLOSION • FORMATION • VORTEX
```

---

## 🎯 Quick Start

### Instalación Rápida
1. Descarga los archivos `.dll` compilados
2. Copia a: `C:\Program Files\Resolume Arena\plugins\vfx\`
3. Reinicia Resolume
4. ¡Encuentra los plugins en tu lista de efectos!

### Primer Uso (Particle Cloud)
```
1. Arrastra "Particle Cloud System" a un clip
2. Ajusta Particle Count = 0.5
3. Elige un Behavior Mode (0.0 - 1.0)
4. Ajusta colores con Hue Start/End
5. Añade Glow Amount = 0.5
6. ¡Experimenta!
```

📖 **Guía completa →** [`QUICK_START.md`](QUICK_START.md)

---

## 🎹 Control MIDI Total

**TODOS los parámetros** son 100% MIDI mapeables:

### Setup Esencial (4 controles)
```
Fader 1  → Behavior Mode (cambia efectos)
Knob 1   → Behavior Strength (intensidad)
Knob 2   → Particle Count (densidad)
Knob 3   → Glow Amount (brillo)
```

### Setup Avanzado (+4 controles)
```
Fader 2  → Hue Start (color)
Knob 4   → Trail Length (estelas)
XY Pad   → Attractor X/Y (posición)
```

**Cómo mapear en Resolume:**
1. Click derecho en parámetro
2. "MIDI Learn"
3. Mueve tu control MIDI
4. ¡Listo!

---

## 🎨 Presets Populares

### 🌌 Galaxia Espiral
```glsl
Behavior Mode = 0.70 (Spiral)
Spiral Speed = 0.3
Particle Count = 0.8
Hue Start = 0.55 (cyan)
Hue End = 0.75 (purple)
Glow = 0.7
```

### 💥 Explosión de Fuego
```glsl
Behavior Mode = 0.78 (Explosion)
Explosion Force = 1.0
Hue Start = 0.0 (rojo)
Hue End = 0.1 (naranja)
Trail Length = 0.6
```

### 🌊 Flujo Orgánico
```glsl
Behavior Mode = 0.38 (Flow Field)
Flow Speed = 0.4
Turbulence = 0.6
Color Mode = Velocity-based
```

### 🌀 Vórtice Hipnótico
```glsl
Behavior Mode = 0.95 (Vortex)
Orbital Speed = 0.7
Attractor X/Y = Center
Glow = 0.9
```

**Más presets →** [`QUICK_START.md`](QUICK_START.md)

---

## 📊 Parámetros Completos

### Particle Cloud System (38 parámetros)

#### 🔷 Básicos
- Particle Count, Size, Life, Emit Rate, Velocity

#### ⚡ Física
- Gravity, Friction, Turbulence, Randomness

#### 🎭 Comportamiento
- Behavior Mode (12 modos)
- Behavior Strength
- Attractor X/Y

#### 🎨 Color
- Color Mode (6 modos)
- Hue Start/End
- Saturation, Brightness

#### ✨ Efectos
- Trail Length/Fade
- Particle Alpha
- Blend Mode (Additive/Alpha/Screen)
- Glow Amount

#### 🎯 Formaciones
- Shape Mode
- Formation Strength

#### 🌊 Controles Específicos
- Curl/Flow Scale & Speed
- Orbital Speed & Radius
- Wave Amplitude & Frequency
- Spiral Tightness & Speed
- Explosion Force
- Time Scale

**Documentación completa →** [`PARTICLE_SYSTEM_README.md`](PARTICLE_SYSTEM_README.md)

---

## 🛠️ Compilar desde Código

### Requisitos
- **Visual Studio 2019/2022** (Community Edition funciona)
- **CMake 3.10+**
- **FFGL SDK** (Resolume)
- **Windows 10/11** (64-bit)

### Pasos
```bash
# 1. Descargar FFGL SDK
git clone https://github.com/resolume/ffgl.git C:\FFGL-SDK

# 2. Copiar este proyecto a plugins
cp -r ResolumeSuperPlugin C:\FFGL-SDK\source\plugins\

# 3. Compilar
cd C:\FFGL-SDK\source\plugins\ResolumeSuperPlugin
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release

# 4. Los DLLs estarán en: build/bin/
```

**Instrucciones detalladas →** [`INSTRUCCIONES_COMPILAR.md`](INSTRUCCIONES_COMPILAR.md)

---

## 📚 Documentación

| Documento | Descripción |
|-----------|-------------|
| **QUICK_START.md** | Guía rápida, presets, trucos |
| **PARTICLE_SYSTEM_README.md** | Documentación completa del sistema de partículas |
| **INSTRUCCIONES_COMPILAR.md** | Cómo compilar los plugins |
| **PROJECT_STRUCTURE.md** | Estructura del proyecto y detalles técnicos |

---

## 💡 Casos de Uso

### 🎵 VJs en Vivo
- Control MIDI completo de todos los parámetros
- Presets listos para usar
- Sincronización con beat
- Múltiples blend modes para layering

### 🎬 Content Creators
- Backgrounds generativos únicos
- Logos animados con partículas
- Efectos de post-producción
- Exportación en alta calidad

### 🎨 Visual Artists
- Sistemas generativos complejos
- Arte procedural en tiempo real
- Instalaciones interactivas
- Performances audiovisuales

### 📱 Redes Sociales
- Visuales únicos para Instagram/TikTok
- Backgrounds animados para streams
- Video loops creativos
- Content para reels

---

## ⚡ Rendimiento

### Super Ultra Plugin
- **Impacto GPU:** Bajo-Medio
- **FPS:** 60+ en la mayoría de sistemas
- **Recomendado:** Cualquier GPU moderna

### Particle Cloud System

| Particle Count | Partículas | GPU Tier | FPS Esperado |
|----------------|-----------|----------|--------------|
| 0.0 - 0.3 | ~100-1000 | Integrada | 30-60 |
| 0.3 - 0.6 | ~1000-5000 | Media (GTX 1060) | 60+ |
| 0.6 - 1.0 | ~5000-10000+ | Alta (RTX 3060+) | 60+ |

**Tips de optimización:**
- Reduce Particle Count si hay lag
- Desactiva Trails (Trail Length = 0)
- Usa Blend Mode = Alpha en vez de Additive
- Cierra otras aplicaciones pesadas

---

## 🎓 Tutoriales y Workflows

### Workflow 1: Logo Animado con Partículas
```
1. Carga tu logo como input
2. Behavior Mode = 0.85 (Formation)
3. Formation Strength = 0 → 1 (animar)
4. Particle Count = 0.7
5. Color Mode = Gradient
```

### Workflow 2: Explosión en el Drop
```
1. Pre-drop: Formation mode (logo)
2. En el drop: 
   - Behavior Mode → Explosion
   - Explosion Force = 1.0
   - Mapea Beat → Reset Particles
3. Post-drop: Vortex mode
```

### Workflow 3: Visuales Audio-Reactivos
```
Mapea FFT/Audio a:
- Bass → Explosion Force
- Mid → Particle Count
- High → Glow Amount
- Beat → Reset Particles (trigger)
```

**Más workflows →** [`QUICK_START.md`](QUICK_START.md)

---

## 🔧 Troubleshooting

### Los plugins no aparecen en Resolume
✅ Verifica que sean **x64** (64-bit)  
✅ Cópialos a la carpeta correcta de plugins  
✅ Reinicia Resolume completamente  

### Performance bajo / FPS drops
✅ Reduce Particle Count a 0.3 o menos  
✅ Desactiva Trails (Trail Length = 0)  
✅ Cambia Blend Mode = Alpha  
✅ Cierra otras aplicaciones  

### Partículas no visibles
✅ Particle Count > 0.3  
✅ Particle Alpha > 0.5  
✅ Particle Size > 0.01  
✅ Glow Amount > 0.3  

### Comportamiento inesperado
✅ Lee la documentación del modo específico  
✅ Resetea parámetros a defaults  
✅ Usa Reset Particles (parámetro 38)  

---

## 🌟 Características Técnicas

### Arquitectura
- **Lenguaje:** C++14
- **API:** FFGL 2.0 (Resolume)
- **Shaders:** GLSL 120
- **Rendering:** OpenGL 3.3+

### Particle System
- **Simulación:** GPU-based con feedback buffers
- **Rendering:** Point sprites optimizados
- **Updates:** Por-frame en compute shader
- **Physics:** Verlet integration con múltiples fuerzas

### Optimizaciones
- Fragment shader optimizado
- Minimal CPU overhead
- GPU-accelerated todo lo posible
- Efficient particle culling

---

## 📝 Roadmap

### Versión 1.1 (Próximamente)
- [ ] Soporte para múltiples emisores
- [ ] Sistema de presets guardables
- [ ] Más modos de comportamiento
- [ ] Interacción con audio mejorada

### Versión 2.0 (Futuro)
- [ ] 3D particle support
- [ ] Collision detection
- [ ] Particle interactions
- [ ] OSC control

---

## 🤝 Contribuciones

¿Ideas? ¿Mejoras? ¿Bugs?

1. Describe tu idea o problema
2. Comparte capturas/videos si es posible
3. Propón soluciones si las tienes

---

## 📄 Licencia

MIT License - Libre para uso personal y comercial

---

## 🎨 Inspiración

Este proyecto está inspirado en:
- **TouchDesigner** - Sistemas de partículas TOP/SOP
- **Processing** - Arte generativo
- **Cinema 4D** - X-Particles
- **Houdini** - POPs

---

## 🌟 Showcase

¿Creaste algo increíble con estos plugins? ¡Compártelo!

---

## 📧 Contacto y Soporte

**Desarrollado por:** Antigravity AI  
**Versión:** 1.0 (2025)  
**Compatible con:** Resolume Arena/Avenue 7.x

---

## ⭐ Si te gusta este proyecto...

- Compártelo con otros VJs y artistas visuales
- Úsalo en tus proyectos creativos
- Reporta bugs y sugiere mejoras
- ¡Crea contenido increíble!

---

**¡Feliz creación visual! 🎨✨🚀**

```
 ╔═══════════════════════════════════════════╗
 ║  RESOLUME SUPER PLUGINS COLLECTION v1.0   ║
 ║  ────────────────────────────────────────  ║
 ║  🎨 Super Ultra Plugin                    ║
 ║  ✨ Particle Cloud System                  ║
 ║  🎹 Full MIDI Control                      ║
 ║  🚀 GPU Accelerated                        ║
 ╚═══════════════════════════════════════════╝
```

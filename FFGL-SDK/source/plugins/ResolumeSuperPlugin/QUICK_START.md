# 🎮 GUÍA RÁPIDA - Particle Cloud System

## ⚡ INICIO RÁPIDO (5 minutos)

### Setup Básico
1. Arrastra el plugin a tu clip en Resolume
2. Ajusta estos 5 parámetros esenciales:
   - **Particle Count**: 0.5 (cantidad media)
   - **Particle Size**: 0.02-0.05 (tamaño pequeño-medio)
   - **Behavior Mode**: Prueba diferentes modos
   - **Color Hue Start**: Tu color favorito
   - **Glow Amount**: 0.5 (brillo medio)

### 🎯 PRESETS RÁPIDOS

#### 1. **Galaxia Espiral** ⭐
```
Behavior Mode = 0.70 (Spiral)
Spiral Speed = 0.3
Particle Count = 0.8
Hue Start = 0.55 (cyan)
Hue End = 0.75 (purple)
Glow Amount = 0.7
```

#### 2. **Explosión** 💥
```
Behavior Mode = 0.78 (Explosion)
Explosion Force = 1.0
Particle Count = 0.7
Hue Start = 0.0 (rojo)
Hue End = 0.1 (naranja)
Trail Length = 0.6
```

#### 3. **Flujo Líquido** 🌊
```
Behavior Mode = 0.38 (Flow Field)
Flow Speed = 0.4
Turbulence = 0.6
Particle Count = 0.6
Color Mode = 0.15 (velocity)
```

#### 4. **Portal/Vórtex** 🌀
```
Behavior Mode = 0.95 (Vortex)
Attractor X = 0.5
Attractor Y = 0.5
Particle Count = 0.9
Glow Amount = 0.9
Trail Length = 0.8
```

#### 5. **Logo Animado** 📝
```
1. Input: Tu logo/texto
2. Behavior Mode = 0.85 (Formation)
3. Formation Strength = 0.0 → 1.0 (animar)
4. Particle Count = 0.7
5. Color Mode = 0.0 (gradient)
```

---

## 🎹 MAPEO MIDI ESENCIAL

### Setup Mínimo (4 controles)
1. **Fader 1** → Behavior Mode
   - Desliza para cambiar entre efectos
   
2. **Knob 1** → Behavior Strength
   - Intensidad del efecto

3. **Knob 2** → Particle Count
   - Densidad de partículas

4. **Knob 3** → Glow Amount
   - Brillo/resplandor

### Setup Avanzado (8 controles)
**Añade:**
5. **Fader 2** → Hue Start (color principal)
6. **Knob 4** → Trail Length (estelas)
7. **XY Pad X** → Attractor X
8. **XY Pad Y** → Attractor Y

---

## 🔥 TRUCOS RÁPIDOS

### Para Performance Live
- **Botón MIDI** → Reset Particles (trigger en drops)
- **BPM Sync** → Time Scale (sincroniza con música)
- **Encoder** → Turbulence (añade caos en momentos clave)

### Para Visuales Impactantes
1. **Doble capa**: 
   - Capa 1: Particles (Additive)
   - Capa 2: Feedback + Blur
   
2. **Audio-reactivo**:
   - Bass → Explosion Force
   - High Freq → Particle Count
   - Beat → Reset trigger

3. **Color dinámico**:
   - Anima Hue Start con LFO
   - Color Mode = Velocity
   - Saturation al máximo

### Optimización de Performance
| FPS Bajo? | Solución |
|-----------|----------|
| Lag general | Reduce Particle Count a 0.3 |
| Stuttering | Desactiva Trails (Trail Length = 0) |
| Render lento | Blend Mode = Alpha (en vez de Additive) |

---

## 📊 TABLA DE MODOS

| Valor | Modo | Efecto | Mejor Para |
|-------|------|--------|------------|
| 0.00-0.08 | Free | Flotando libremente | Ambientes, fondos |
| 0.08-0.17 | Attract | Implosión al centro | Portales, energía |
| 0.17-0.25 | Repel | Explosión desde centro | Ondas expansivas |
| 0.25-0.33 | Orbital | Gira alrededor | Planetas, órbitas |
| 0.33-0.42 | Flow | Flujo continuo | Humo, agua, fluidos |
| 0.42-0.50 | Turbulence | Caos controlado | Tormentas, energía |
| 0.50-0.58 | Flocking | Comportamiento enjambre | Pájaros, peces |
| 0.58-0.67 | Wave | Ondas | Agua, oscilaciones |
| 0.67-0.75 | Spiral | Espiral | Galaxias, vórtices |
| 0.75-0.83 | Explosion | Estallido | Explosiones, fireworks |
| 0.83-0.92 | Formation | Forma imagen/texto | Logos, texto animado |
| 0.92-1.00 | Vortex | Vórtice giratorio | Tornados, black holes |

---

## 🎨 PALETAS DE COLOR RECOMENDADAS

### Fuego 🔥
```
Hue Start = 0.0 (rojo)
Hue End = 0.1 (naranja/amarillo)
Saturation = 1.0
Brightness = 0.9
```

### Ocean 🌊
```
Hue Start = 0.5 (cyan)
Hue End = 0.6 (azul)
Saturation = 0.8
Brightness = 0.7
```

### Neón 💜
```
Hue Start = 0.75 (magenta)
Hue End = 0.55 (cyan)
Saturation = 1.0
Brightness = 1.0
Color Mode = 0.15 (velocity)
```

### Galaxia ⭐
```
Hue Start = 0.55 (cyan)
Hue End = 0.8 (purple)
Saturation = 0.9
Brightness = 0.8
Glow = 0.8
```

### Oro Místico ✨
```
Hue Start = 0.12 (dorado)
Hue End = 0.15 (amarillo)
Saturation = 0.7
Brightness = 1.0
Glow = 0.9
```

---

## ⚙️ TROUBLESHOOTING

### Problema: No veo partículas
✅ **Soluciones:**
- Particle Count > 0.3
- Particle Alpha > 0.5
- Particle Size > 0.01

### Problema: Partículas muy lentas
✅ **Soluciones:**
- Velocity > 0.3
- Time Scale = 0.5-0.7
- Reduce Friction a 0.1

### Problema: Efecto muy sutil
✅ **Soluciones:**
- Behavior Strength = 0.7-1.0
- Glow Amount > 0.5
- Blend Mode = Additive

### Problema: Partículas desaparecen rápido
✅ **Soluciones:**
- Particle Life = 0.8-1.0
- Trail Fade = 0.3 (más lento)

---

## 💡 COMBOS CREATIVOS

### Combo 1: "Fuego Artificial"
1. Explosion Force = 1.0
2. Gravity = 0.8 (caen)
3. Trail Length = 0.7
4. Color = Fuego 🔥

### Combo 2: "Tornado Cósmico"
1. Vortex mode
2. Spiral Tightness = 0.6
3. Turbulence = 0.8
4. Color = Galaxia ⭐

### Combo 3: "Enjambre Inteligente"
1. Flocking mode
2. Randomness = 0.6
3. Velocity = 0.4
4. Particle Count = 0.9

### Combo 4: "Texto que Explota"
1. Formation mode (con texto)
2. Anima Formation Strength 1.0 → 0.0
3. Explosion Force aumenta
4. Trails activados

---

## 🚀 WORKFLOW PROFESIONAL

### Para VJs en vivo:
1. **Pre-show**: Crea 5-6 presets diferentes
2. **Durante show**: 
   - USA Behavior Mode como "macro" control
   - Mapea Beat detection a Reset
   - Automatiza Hue con LFO lento
3. **Transiciones**: Cruza entre layers con diferentes modos

### Para content creators:
1. Renderiza a 60fps
2. Usa Formation mode con tu logo
3. Graba variaciones con diferentes colors
4. Combina con video feedback

---

## 📱 CHEAT SHEET DE 1 MINUTO

**Quick start:**
```
1. Particle Count = 0.5
2. Pick a Behavior Mode
3. Adjust Behavior Strength
4. Choose colors (Hue Start/End)
5. Add glow
6. ¡LISTO!
```

**Best settings para cada situación:**
- **Ambient chill**: Flow (0.38), low velocity
- **Drop intenso**: Explosion (0.78), high glow
- **Build-up**: Formation → Explosion
- **Breakdown**: Spiral (0.70), slow time

---

**¡Experimenta y crea! 🎨✨**

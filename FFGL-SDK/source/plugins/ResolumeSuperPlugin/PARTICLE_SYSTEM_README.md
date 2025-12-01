# 🌟 Particle Cloud System - Plugin de Nubes de Puntos para Resolume

## 🎯 Descripción

Un sistema avanzado de partículas estilo **TouchDesigner** para Resolume Arena/Avenue. Genera nubes de puntos GPU totalmente editables que pueden tomar la forma de imágenes, texto, y responder a múltiples comportamientos físicos.

## ✨ Características Principales

- **GPU-Accelerated**: Miles de partículas en tiempo real
- **38 Parámetros MIDI Mapeables**: Control total de cada aspecto
- **12 Modos de Comportamiento**: De partículas libres a formaciones complejas
- **Sistema de Color Avanzado**: Gradientes, basado en velocidad, posición
- **Trails/Estelas**: Rastros de movimiento ajustables
- **Múltiples Modos de Blend**: Additive, Alpha, Screen
- **Formaciones**: Las partículas pueden formar texto e imágenes

---

## 🎮 PARÁMETROS (Todos MIDI Mapeables)

### 🔷 Parámetros Básicos de Partículas

1. **Particle Count** (0.0 - 1.0)
   - Cantidad de partículas activas
   - 0.0 = ~100 partículas
   - 1.0 = ~10,000+ partículas

2. **Particle Size** (0.0 - 1.0)
   - Tamaño de cada partícula
   - 0.0 = Muy pequeñas (puntos)
   - 1.0 = Grandes (esferas)

3. **Particle Life** (0.0 - 1.0)
   - Vida útil de cada partícula
   - 0.0 = Vida corta (efímeras)
   - 1.0 = Vida larga (persistentes)

4. **Emit Rate** (0.0 - 1.0)
   - Velocidad de emisión de nuevas partículas
   - 0.0 = Emisión lenta
   - 1.0 = Emisión rápida/continua

---

### ⚡ Parámetros de Física

5. **Velocity** (0.0 - 1.0)
   - Velocidad base de las partículas
   - 0.0 = Movimiento muy lento
   - 1.0 = Movimiento rápido

6. **Gravity** (0.0 - 1.0)
   - Fuerza gravitacional
   - 0.0 = Gravedad hacia arriba
   - 0.5 = Sin gravedad
   - 1.0 = Gravedad hacia abajo fuerte

7. **Friction** (0.0 - 1.0)
   - Fricción del aire/resistencia
   - 0.0 = Sin fricción (movimiento perpetuo)
   - 1.0 = Fricción alta (se detienen rápido)

8. **Turbulence** (0.0 - 1.0)
   - Cantidad de ruido/caos en el movimiento
   - 0.0 = Movimiento suave
   - 1.0 = Muy caótico

---

### 🎭 MODOS DE COMPORTAMIENTO

9. **Behavior Mode** (0.0 - 1.0) - Selector de modo
   
   **Divide el rango 0-1 en 12 zonas:**

   - **0.00 - 0.08**: MODE 0 - **FREE/RANDOM**
     - Partículas flotando libremente con movimiento aleatorio
     - Ideal para: Ambientes, fondos, efectos atmosféricos
   
   - **0.08 - 0.17**: MODE 1 - **ATTRACT**
     - Atracción hacia el punto central (Attractor X/Y)
     - Ideal para: Implosiones, centros de energía, portales
   
   - **0.17 - 0.25**: MODE 2 - **REPEL**
     - Repulsión desde el punto central
     - Ideal para: Explosiones, ondas expansivas
   
   - **0.25 - 0.33**: MODE 3 - **ORBITAL**
     - Movimiento orbital alrededor del atractor
     - Ideal para: Sistemas planetarios, vórtices circulares
     - Usa: Orbital Speed y Orbital Radius
   
   - **0.33 - 0.42**: MODE 4 - **FLOW FIELD**
     - Campo de flujo continuo (curl noise)
     - Ideal para: Fluidos, humo, efectos orgánicos
     - Usa: Flow Scale y Flow Speed
   
   - **0.42 - 0.50**: MODE 5 - **TURBULENCE**
     - Alta turbulencia y caos controlado
     - Ideal para: Tormentas, energía caótica
   
   - **0.50 - 0.58**: MODE 6 - **FLOCKING**
     - Comportamiento de bandada (boids)
     - Ideal para: Pájaros, peces, enjambres
   
   - **0.58 - 0.67**: MODE 7 - **WAVE**
     - Movimiento ondulatorio
     - Ideal para: Ondas de agua, oscilaciones
     - Usa: Wave Amplitude y Wave Frequency
   
   - **0.67 - 0.75**: MODE 8 - **SPIRAL**
     - Movimiento espiral
     - Ideal para: Galaxias, espirales, vórtices
     - Usa: Spiral Tightness y Spiral Speed
   
   - **0.75 - 0.83**: MODE 9 - **EXPLOSION**
     - Explosión desde el centro
     - Ideal para: Explosiones, estallidos, supernovas
     - Usa: Explosion Force
   
   - **0.83 - 0.92**: MODE 10 - **FORMATION** ⭐
     - Las partículas forman la imagen/texto de entrada
     - Ideal para: Logos animados, texto, formas específicas
     - Usa: Formation Strength
   
   - **0.92 - 1.00**: MODE 11 - **VORTEX**
     - Vórtex giratorio que atrae hacia el centro
     - Ideal para: Tornados, agujeros negros

10. **Behavior Strength** (0.0 - 1.0)
    - Intensidad del comportamiento seleccionado
    - 0.0 = Efecto sutil
    - 1.0 = Efecto máximo

11. **Attractor X** (0.0 - 1.0)
    - Posición X del punto de atracción/repulsión/órbita
    - 0.0 = Izquierda
    - 0.5 = Centro
    - 1.0 = Derecha

12. **Attractor Y** (0.0 - 1.0)
    - Posición Y del punto de atracción
    - 0.0 = Arriba
    - 0.5 = Centro
    - 1.0 = Abajo

---

### 🎨 Sistema de Color

13. **Color Mode** (0.0 - 1.0)
    - **0.0 - 0.2**: Gradiente por edad de partícula
    - **0.2 - 0.4**: Color por velocidad
    - **0.4 - 0.6**: Color por posición
    - **0.6 - 0.8**: Color sólido
    - **0.8 - 1.0**: Color personalizado

14. **Hue Start** (0.0 - 1.0)
    - Color inicial del gradiente (rueda de color)
    - 0.0 = Rojo
    - 0.33 = Verde
    - 0.66 = Azul

15. **Hue End** (0.0 - 1.0)
    - Color final del gradiente

16. **Saturation** (0.0 - 1.0)
    - Saturación del color
    - 0.0 = Gris/blanco
    - 1.0 = Colores vibrantes

17. **Brightness** (0.0 - 1.0)
    - Brillo general
    - 0.0 = Oscuro
    - 1.0 = Muy brillante

---

### ✨ Efectos Visuales

18. **Trail Length** (0.0 - 1.0)
    - Longitud de las estelas/trails
    - 0.0 = Sin estelas
    - 1.0 = Estelas largas

19. **Trail Fade** (0.0 - 1.0)
    - Velocidad de desvanecimiento de trails
    - 0.0 = Desvanecen rápido
    - 1.0 = Persisten más tiempo

20. **Particle Alpha** (0.0 - 1.0)
    - Transparencia de partículas
    - 0.0 = Transparentes
    - 1.0 = Opacas

21. **Blend Mode** (0.0 - 1.0)
    - **0.0 - 0.33**: Additive (suma colores, brilla más)
    - **0.33 - 0.67**: Alpha (transparencia normal)
    - **0.67 - 1.0**: Screen (modo pantalla)

22. **Glow Amount** (0.0 - 1.0)
    - Cantidad de resplandor/glow
    - 0.0 = Sin glow
    - 1.0 = Glow intenso

---

### 🎯 Formaciones (Texto e Imágenes)

23. **Shape Mode** (0.0 - 1.0)
    - **0.0 - 0.33**: Distribución aleatoria
    - **0.33 - 0.67**: Formación de imagen (usa input)
    - **0.67 - 1.0**: Formación de texto

24. **Formation Strength** (0.0 - 1.0)
    - Qué tan fuerte las partículas se adhieren a la formación
    - 0.0 = Ignoran la formación
    - 1.0 = Se adhieren completamente

---

### 🌊 Parámetros Específicos de Comportamiento

#### Curl Noise / Flow
25. **Curl Scale** (0.0 - 1.0)
    - Escala del ruido curl
    - 0.0 = Flujo amplio
    - 1.0 = Flujo detallado

26. **Curl Speed** (0.0 - 1.0)
    - Velocidad de evolución del flujo

27. **Flow Scale** (0.0 - 1.0)
    - Escala del campo de flujo

28. **Flow Speed** (0.0 - 1.0)
    - Velocidad del campo de flujo

#### Orbital
29. **Orbital Speed** (0.0 - 1.0)
    - Velocidad de rotación orbital

30. **Orbital Radius** (0.0 - 1.0)
    - Radio de la órbita
    - 0.0 = Órbita cerrada
    - 1.0 = Órbita amplia

#### Wave
31. **Wave Amplitude** (0.0 - 1.0)
    - Altura de las ondas

32. **Wave Frequency** (0.0 - 1.0)
    - Frecuencia de las ondas
    - 0.0 = Ondas largas
    - 1.0 = Ondas rápidas

#### Spiral
33. **Spiral Tightness** (0.0 - 1.0)
    - Qué tan apretada es la espiral

34. **Spiral Speed** (0.0 - 1.0)
    - Velocidad de rotación espiral

#### Explosion
35. **Explosion Force** (0.0 - 1.0)
    - Fuerza de la explosión

---

### 🔧 Parámetros Globales

36. **Randomness** (0.0 - 1.0)
    - Cantidad de aleatoriedad añadida a todos los movimientos
    - 0.0 = Movimiento predecible
    - 1.0 = Muy aleatorio

37. **Time Scale** (0.0 - 1.0)
    - Escala de tiempo de toda la simulación
    - 0.0 = Congelado
    - 0.5 = Tiempo normal
    - 1.0 = Tiempo acelerado

38. **Reset Particles** (0.0 - 1.0)
    - Reinicia todas las partículas
    - Pon en 1.0 momentáneamente para reiniciar

---

## 🎹 CONTROL MIDI

**TODOS los 38 parámetros son 100% mapeables a MIDI** en Resolume:

1. Click derecho en cualquier parámetro
2. Selecciona "MIDI Learn"
3. Mueve el control MIDI deseado
4. ¡Listo! Control en tiempo real

### Recomendaciones de Mapeo MIDI:

**Controles Esenciales:**
- **Fader 1**: Behavior Mode (cambiar entre efectos)
- **Fader 2**: Behavior Strength (intensidad)
- **Knob 1**: Particle Count (densidad)
- **Knob 2**: Particle Size (tamaño)
- **XY Pad**: Attractor X/Y (posición del atractor)

**Efectos Visuales:**
- **Fader 3**: Hue Start (color)
- **Fader 4**: Glow Amount (brillo)
- **Knob 3**: Trail Length (estelas)
- **Knob 4**: Turbulence (caos)

**Performance Live:**
- **Botón 1**: Reset Particles (trigger)
- **Encoder 1**: Time Scale (tempo)
- **Encoder 2**: Formation Strength (morphing)

---

## 🎨 FLUJOS DE TRABAJO CREATIVOS

### 1. Logo Animado
```
1. Carga tu logo/texto como Layer input
2. Behavior Mode = 0.85 (Formation)
3. Formation Strength = 0.8
4. Particle Count = 0.7
5. Color Mode = Gradient
6. Anima: Formation Strength 0 → 1 (aparece)
```

### 2. Explosión Cósmica
```
1. Behavior Mode = 0.78 (Explosion)
2. Explosion Force = 1.0
3. Color Hue Start = 0.0 (rojo)
4. Color Hue End = 0.1 (naranja)
5. Glow Amount = 0.8
6. Trail Length = 0.6
```

### 3. Flujo Orgánico
```
1. Behavior Mode = 0.38 (Flow Field)
2. Flow Scale = 0.3
3. Flow Speed = 0.4
4. Turbulence = 0.6
5. Trail Length = 0.8
6. Blend Mode = 0.0 (Additive)
```

### 4. Vórtice Hipnótico
```
1. Behavior Mode = 0.95 (Vortex)
2. Orbital Speed = 0.7
3. Attractor X/Y = 0.5 (centro)
4. Particle Count = 0.9
5. Color Mode = Velocity-based
6. Glow Amount = 0.9
```

### 5. Galaxia Espiral
```
1. Behavior Mode = 0.70 (Spiral)
2. Spiral Tightness = 0.6
3. Spiral Speed = 0.3
4. Particle Count = 0.8
5. Hue Start = 0.55 (cyan)
6. Hue End = 0.75 (purple)
```

---

## 🔥 TIPS PRO

1. **Combina con otros efectos de Resolume**: Prueba encadenar con Bloom, Blur, o feedback loops

2. **Automatiza parámetros**: Usa el BPM Sync de Resolume para animar parámetros al ritmo

3. **Capas múltiples**: Usa varias instancias del plugin con diferentes comportamientos superpuestos

4. **Audio reactivo**: Mapea FFT/Beat a parámetros como:
   - Bass → Explosion Force
   - High → Particle Count
   - Beat → Reset Particles (trigger)

5. **Formaciones dinámicas**: Usa generadores de texto de Resolume como input para formaciones que cambian en tiempo real

---

## 📊 RENDIMIENTO

- **Bajo** (Particle Count < 0.3): ~1000 partículas, 60+ FPS
- **Medio** (Particle Count 0.3-0.6): ~5000 partículas, 30-60 FPS
- **Alto** (Particle Count > 0.6): ~10000+ partículas, puede bajar a 30 FPS

**Optimización:**
- Reduce Particle Count si tienes lag
- Disable Trails si necesitas más rendimiento
- Usa Blend Mode Alpha en vez de Additive para mejor performance

---

## 🚀 INSTALACIÓN

Ver `INSTRUCCIONES_COMPILAR.md` para compilar el plugin.

Una vez compilado:
1. Copia `ParticleCloudPlugin.dll` a:
   ```
   C:\Program Files\Resolume Arena\plugins\vfx\
   ```
2. Reinicia Resolume
3. ¡Busca "Particle Cloud System" en tus efectos!

---

## 💡 INSPIRACIÓN

Este plugin está inspirado en:
- **TouchDesigner** - Sistema de partículas TOP/SOP
- **Processing** - Sistemas de partículas generativos
- **Cinema 4D** - X-Particles
- **Houdini** - POPs (Particle Operators)

---

## 📝 CHANGELOG

### v1.0 (2025)
- ✨ 38 parámetros MIDI mapeables
- 🎭 12 modos de comportamiento
- 🎨 Sistema de color avanzado
- 🌊 Soporte para formaciones (texto/imagen)
- ⚡ GPU-accelerated rendering
- ✨ Trails y glow effects
- 🎮 Control total en tiempo real

---

## 🆘 SOPORTE

¿Problemas o preguntas? Comparte tu setup y te ayudaré a optimizarlo.

---

**¡Disfruta creando universos de partículas! ✨🌌🎆**

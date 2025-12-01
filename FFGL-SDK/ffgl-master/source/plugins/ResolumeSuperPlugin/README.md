# Super Plugin para Resolume - Guía de Instalación

## 📦 Paso 1: Preparar el SDK de FFGL

1. **Descarga el SDK**:
   ```powershell
   cd C:\
   git clone https://github.com/resolume/ffgl.git FFGL-SDK
   ```
   
   O si no tienes Git, descarga ZIP desde: https://github.com/resolume/ffgl

2. **Estructura correcta**:
   ```
   C:\FFGL-SDK\
   ├── cmake\
   ├── source\
   │   ├── lib\
   │   └── plugins\
   └── CMakeLists.txt
   ```

## 📂 Paso 2: Instalar el Plugin

Copia la carpeta `ResolumeSuperPlugin` dentro de:
```
C:\FFGL-SDK\source\plugins\
```

Debe quedar así:
```
C:\FFGL-SDK\source\plugins\ResolumeSuperPlugin\
├── SuperPlugin.cpp
├── CMakeLists.txt
└── README.md
```

## 🔧 Paso 3: Compilar SOLO nuestro plugin

Para evitar errores de los plugins de ejemplo, compila **solo** el Super Plugin:

```powershell
cd C:\FFGL-SDK
mkdir build
cd build

# Generar proyecto de Visual Studio
cmake .. -G "Visual Studio 17 2022" -A x64

# Compilar SOLO nuestro plugin (no todos los ejemplos)
cmake --build . --config Release --target SuperPlugin
```

## 📍 Paso 4: Encontrar el DLL

Tu plugin compilado estará en:
```
C:\FFGL-SDK\build\binaries\Release\SuperPlugin.dll
```

## 🎯 Paso 5: Instalar en Resolume

Copia `SuperPlugin.dll` a una de estas carpetas:

**Opción A (Recomendada)**:
```
C:\Users\[TuUsuario]\Documents\Resolume Arena\Extra Effects\
```

**Opción B**:
```
C:\Program Files\Resolume Arena\plugins\vfx\
```

## ✅ Paso 6: Usar en Resolume

1. Abre Resolume Arena
2. Carga un clip
3. Ve a la pestaña **Composition**
4. Busca **"Super Ultra Plugin"** en la lista de efectos
5. ¡Aplícalo y disfruta!

---

## 🎨 Controles del Plugin

| Parámetro | Función |
|-----------|---------|
| **Brightness** | Ajusta el brillo (0.5 = normal) |
| **Contrast** | Ajusta el contraste |
| **Saturation** | Saturación de color |
| **Hue** | Rotación de matiz/color |
| **Res X / Res Y** | Pixelación (1.0 = HD, 0.0 = muy pixelado) |
| **H Align / V Align** | Mueve el clip horizontal/verticalmente |
| **Negative** | Invierte los colores |
| **Effect Mode** | Selecciona efecto (0.0-1.0 = modos 0-10) |
| **Effect Amount** | Intensidad del efecto |

## 🌟 Los 10 Efectos

Mueve **Effect Mode** de 0.0 a 1.0 para cambiar entre:

| Valor | Modo | Efecto |
|-------|------|--------|
| 0.0 | 0 | Normal (sin efecto) |
| 0.1 | 1 | Cyber Glitch |
| 0.2 | 2 | Kaleidoscope |
| 0.3 | 3 | Neon Edges |
| 0.4 | 4 | Liquid Warp |
| 0.5 | 5 | Radial Chromatic |
| 0.6 | 6 | Scanlines CRT |
| 0.7 | 7 | Mirror Quad |
| 0.8 | 8 | Solarize |
| 0.9 | 9 | Cinematic Vignette |
| 1.0 | 10 | Dot Matrix LED |

---

## ⚠️ Solución de Problemas

### Error: "CFreeFrameGLPlugin no definido"
✅ **Solucionado** - Ahora usa la API moderna de FFGL 2.x

### Error al compilar otros plugins de ejemplo
✅ **Solución**: Compila SOLO el Super Plugin con:
```powershell
cmake --build . --config Release --target SuperPlugin
```

### El DLL no aparece en Resolume
- Verifica que sea **x64** (64-bit)
- Revisa el log de Resolume en: `%APPDATA%\Resolume Arena\`
- Asegúrate que la versión de Resolume sea 7.3+

---

## 🚀 ¡Listo!

Ahora tienes un plugin profesional con 10 efectos avanzados para Resolume.

**Tip Pro**: Combina varios parámetros a la vez (ej: Glitch + Chromatic + Saturation) para crear efectos únicos.

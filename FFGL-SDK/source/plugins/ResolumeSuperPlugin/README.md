# Super Plugin para Resolume Arena

## 🎯 ¿Qué es esto?

Este es un plugin **FFGL** (FreeFrameGL) para Resolume Arena/Avenue que incluye:

✅ **Edición de color completa**: Brillo, Contraste, Saturación, Hue  
✅ **Controles de resolución**: Efecto pixelado (ResX/ResY)  
✅ **Alineación**: H Align / V Align para mover el clip  
✅ **Inversión de color**: Efecto Negative  
✅ **10 Efectos Avanzados** (modo seleccionable 0-10):

| Modo | Efecto | Descripción |
|------|--------|-------------|
| 0 | Normal | Sin efecto especial |
| 1 | **Cyber Glitch** | Desplazamiento de bloques + aberración cromática |
| 2 | **Kaleidoscope** | Espejos radiales psicodélicos |
| 3 | **Neon Edges** | Detección de bordes brillantes |
| 4 | **Liquid Warp** | Distorsión fluida animada |
| 5 | **Radial Chromatic** | Separación RGB desde el centro |
| 6 | **Scanlines** | Efecto CRT / TV antigua |
| 7 | **Mirror Quad** | Espejo de 4 vías |
| 8 | **Solarize** | Inversión selectiva de color |
| 9 | **Cinematic** | Viñeta + grano de película |
| 10 | **Dot Matrix** | Simulación de pantalla LED |

---

## 📦 Archivos Incluidos

- `SuperPlugin.cpp` - Código fuente principal (C++)
- `shader.glsl` - Shader GLSL (sólo referencia, ya está integrado en el .cpp)
- `CMakeLists.txt` - Configuración de compilación
- `INSTRUCCIONES_COMPILAR.md` - **Guía paso a paso para compilar**
- `README.md` - Este archivo

---

## 🔧 Compilación Rápida

### Requisitos:
1. **Visual Studio 2022** (Community es gratis)
2. **SDK de FFGL**: https://github.com/resolume/ffgl

### Pasos:

1. **Descarga el SDK de FFGL**:
   ```
   git clone https://github.com/resolume/ffgl.git C:\FFGL-SDK
   ```

2. **Copia este plugin** dentro del SDK:
   ```
   Copiar carpeta "ResolumeSuperPlugin" a:
   C:\FFGL-SDK\ffgl\source\plugins\
   ```

3. **Compila usando CMake**:
   ```powershell
   cd C:\FFGL-SDK\ffgl
   mkdir build
   cd build
   cmake .. -G "Visual Studio 17 2022" -A x64
   cmake --build . --config Release
   ```

4. **Resultado**: Encontrarás `SuperPlugin.dll` en:
   ```
   C:\FFGL-SDK\ffgl\build\binaries\Release\
   ```

5. **Instalación**: Copia el DLL a:
   ```
   C:\Users\[TuUsuario]\Documents\Resolume Arena\Extra Effects\
   ```

---

## 📖 Instrucciones Detalladas

Lee el archivo **`INSTRUCCIONES_COMPILAR.md`** para una guía completa con soluciones a problemas comunes.

---

## 🎨 Cómo Usar el Plugin en Resolume

1. Abre Resolume Arena
2. Carga un clip/layer
3. Ve a la pestaña **Composition**
4. Busca "Super Ultra Plugin" en la lista de efectos
5. Ajusta los parámetros:
   - **Brightness/Contrast/Saturation/Hue**: Corrección de color
   - **Res X/Y**: Baja la resolución para efecto pixelado
   - **H/V Align**: Mueve el clip
   - **Effect Mode**: Cambia de 0.0 a 1.0 para seleccionar efectos (0=normal, 0.1=glitch, 0.2=kaleidoscope, etc.)
   - **Effect Amount**: Intensidad del efecto
   - **Negative**: Inversión de color

---

## ⚠️ Notas Importantes

### Sobre el Texto
Como mencioné en las instrucciones originales, implementar un motor completo de texto dentro de un plugin de efectos es técnicamente complicado y poco eficiente.

**Solución Recomendada:**
1. Usa la fuente de **Texto** nativa de Resolume
2. Aplica este plugin **sobre** el texto
3. Ahora tendrás texto con Glitch, Neón, Líquido, etc.

### Compatibilidad
- Compilado para **64-bit** (x64)
- Compatible con **Resolume 7.x** y superior
- Requiere OpenGL 2.1+

---

## 🆘 Soporte

Si tienes problemas compilando o usando el plugin:
1. Revisa `INSTRUCCIONES_COMPILAR.md`
2. Verifica que tu sistema tenga Visual Studio 2022
3. Asegúrate de compilar en modo **Release** y **x64**

---

## 📝 Créditos

- Desarrollado usando el SDK FFGL de Resolume
- Creado con Antigravity AI
- Efectos de shader inspirados en las mejores técnicas de VJing del mundo

---

## 🎉 ¡Disfruta!

Este plugin te da lo mejor de lo mejor en un solo lugar. Experimenta combinando efectos, ajustando parámetros en tiempo real y creando visuales increíbles.

**¡A rockear con Resolume!** 🚀🎨

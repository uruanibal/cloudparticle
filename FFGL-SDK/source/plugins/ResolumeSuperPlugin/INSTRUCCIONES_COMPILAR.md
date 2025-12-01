# 🚀 Instrucciones para Compilar los Plugins de Resolume

Este proyecto incluye **DOS plugins**:
1. **SuperPlugin** - Plugin original con 10 efectos visuales
2. **ParticleCloudPlugin** - Sistema avanzado de partículas con 38 parámetros MIDI

## Paso 1: Descargar el SDK de FFGL

1. Ve a: **https://github.com/resolume/ffgl**
2. Haz clic en el botón verde **"Code"** → **"Download ZIP"**
3. Extrae el ZIP en una carpeta, por ejemplo: `C:\FFGL-SDK\`

## Paso 2: Configurar el Proyecto

### Opción A: Usar CMake (Recomendado)

1. Instala **CMake** desde: https://cmake.org/download/ (si no lo tienes)
2. Abre una terminal en la carpeta del SDK (`C:\FFGL-SDK\ffgl-master\`)
3. Copia la carpeta `ResolumeSuperPlugin` dentro de `C:\FFGL-SDK\ffgl-master\source\plugins\`
4. Ejecuta:
```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
```

### Opción B: Proyecto Manual de Visual Studio

Si prefieres no usar CMake, puedes crear el proyecto manualmente:

1. Abre **Visual Studio 2022**
2. **Archivo** → **Nuevo** → **Proyecto**
3. Busca "DLL" y selecciona **"Biblioteca de vínculos dinámicos (DLL)"**
4. Nombre: `SuperPlugin`
5. Configura:
   - **Plataforma**: x64
   - **Configuración**: Release

#### Configurar Include Directories:
- Proyecto → Propiedades → C/C++ → General → Directorios de inclusión adicionales:
  ```
  C:\FFGL-SDK\ffgl-master\source\lib\ffgl
  C:\FFGL-SDK\ffgl-master\source\lib\ffglquickstart
  ```

#### Configurar Preprocessor:
- Proyecto → Propiedades → C/C++ → Preprocesador → Definiciones:
  ```
  FFGL_EXPORTS
  _WINDOWS
  ```

#### Agregar archivos:
- Copia `SuperPlugin.cpp` a la carpeta del proyecto
- Agrega todos los archivos `.cpp` del SDK de FFGL que necesites

## Paso 3: Modificar el Código (Importante)

Antes de compilar, necesitas **integrar el shader** en el código C++.

Abre `SuperPlugin.cpp` y busca estas líneas (alrededor de la línea 67):

```cpp
std::string vertexShaderCode = "..."; // Standard pass-through vertex shader
std::string fragmentShaderCode = "..."; // The complex shader provided separately
```

Reemplázalas con:

```cpp
std::string vertexShaderCode = R"(
#version 120
void main() {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
)";

std::string fragmentShaderCode = R"(
// PEGA AQUÍ TODO EL CONTENIDO DE shader.glsl
)";
```

**NOTA IMPORTANTE:** Copia TODO el contenido del archivo `shader.glsl` y pégalo dentro de las comillas `R"( ... )"` del `fragmentShaderCode`.

## Paso 4: Compilar

1. En Visual Studio, selecciona **Release** y **x64** en la barra superior
2. **Compilar** → **Compilar solución** (F7)
3. Si todo va bien, encontrarás **AMBOS plugins** en:
   ```
   ResolumeSuperPlugin\build\bin\
   ```
   
   Archivos generados:
   - **SuperPlugin.dll** - Plugin de efectos original
   - **ParticleCloudPlugin.dll** - Plugin de sistema de partículas

## Paso 5: Instalar en Resolume

1. Copia **AMBOS archivos .dll**
2. Pégalos en la carpeta de plugins de Resolume:
   ```
   C:\Program Files\Resolume Arena\plugins\vfx\
   ```
   O en:
   ```
   C:\Users\[TuUsuario]\Documents\Resolume Arena\Extra Effects\
   ```

## Paso 6: ¡Úsalos!

1. Abre Resolume
2. En la pestaña **Composition**, busca en la lista de efectos:
   - **"Super Ultra Plugin"** - 10 efectos visuales clásicos
   - **"Particle Cloud System"** - Sistema de partículas avanzado
3. Arrastra el que quieras usar a tu clip
4. **Para Particle Cloud System**: Lee `PARTICLE_SYSTEM_README.md` para todos los detalles
5. **Quick Start**: Lee `QUICK_START.md` para presets listos para usar
6. ¡Disfruta!

---

## ⚠️ Problemas Comunes

### Error: "No se puede encontrar FFGL.h"
- Verifica que los directorios de inclusión estén correctamente configurados

### Error: "unresolved external symbol"
- Necesitas agregar los archivos `.cpp` del SDK de FFGL a tu proyecto

### El DLL no aparece en Resolume
- Asegúrate de compilar en **x64** (64 bits)
- Verifica que el DLL esté en la carpeta correcta
- Revisa el log de Resolume en: `%APPDATA%\Resolume Arena\`

---

## 🆘 Si tienes problemas...

Avísame y te ayudo a resolver cualquier error específico que te aparezca.

cmake_minimum_required(VERSION 3.10)
project(ParticleCloudPlugin)
set(CMAKE_CXX_STANDARD 14)

# Ruta del SDK (se puede pasar desde GitHub o usar local por defecto)
if(NOT DEFINED FFGL_SDK_ROOT)
    set(FFGL_SDK_ROOT "${CMAKE_SOURCE_DIR}/FFGL-SDK")
endif()

set(FFGL_SOURCE_DIR "${FFGL_SDK_ROOT}/source")

message(STATUS "Usando FFGL SDK en: ${FFGL_SDK_ROOT}")

# Includes necesarios
include_directories(
    ${FFGL_SOURCE_DIR}/lib/ffgl
    ${FFGL_SOURCE_DIR}/lib/ffglquickstart
    ${FFGL_SOURCE_DIR}/lib/glad/include
)

# Código fuente del plugin
set(PLUGIN_SOURCES
    ParticleCloudModern.cpp
    ${FFGL_SOURCE_DIR}/lib/ffgl/FFGLPluginSDK.cpp
    ${FFGL_SOURCE_DIR}/lib/ffgl/FFGL.cpp
    ${FFGL_SOURCE_DIR}/lib/glad/src/glad.c
)

# Crear librería compartida (.dll o .bundle según sistema)
add_library(ParticleCloudPlugin SHARED ${PLUGIN_SOURCES})

# Definiciones necesarias
target_compile_definitions(ParticleCloudPlugin PRIVATE
    FFGL_EXPORTS
    _WINDOWS
)

# Vincular OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(ParticleCloudPlugin ${OPENGL_gl_LIBRARY})

# Directorios de salida
set_target_properties(ParticleCloudPlugin PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# Para macOS: crear .bundle en lugar de .dylib
if(APPLE)
    set_target_properties(ParticleCloudPlugin PROPERTIES BUNDLE TRUE)
    set_target_properties(ParticleCloudPlugin PROPERTIES
        MACOSX_BUNDLE TRUE
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bundle"
    )
endif()

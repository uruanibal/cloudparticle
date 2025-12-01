cmake_minimum_required(VERSION 3.10)

project(ResolumeSuperPlugins)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define paths (adjust these to match your FFGL SDK location)
set(FFGL_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" CACHE PATH "Path to FFGL SDK root")

# Include directories
include_directories(
    ${FFGL_SDK_PATH}/lib/ffgl
    ${FFGL_SDK_PATH}/lib/ffglquickstart
    ${FFGL_SDK_PATH}/lib/glad/include
)

# Common FFGL source files
set(FFGL_COMMON_SOURCES
    ${FFGL_SDK_PATH}/lib/ffgl/FFGLPluginSDK.cpp
    ${FFGL_SDK_PATH}/lib/ffgl/FFGL.cpp
    ${FFGL_SDK_PATH}/lib/ffglquickstart/FFGLShader.cpp
    ${FFGL_SDK_PATH}/lib/glad/src/glad.c
)

# ========================================
# PLUGIN 1: SuperPlugin (Original Effects)
# ========================================
set(SUPERPLUGIN_SOURCES
    SuperPlugin.cpp
    ${FFGL_COMMON_SOURCES}
)

add_library(SuperPlugin SHARED ${SUPERPLUGIN_SOURCES})

target_compile_definitions(SuperPlugin PRIVATE
    FFGL_EXPORTS
    _WINDOWS
)

find_package(OpenGL REQUIRED)
target_link_libraries(SuperPlugin ${OPENGL_gl_LIBRARY})

set_target_properties(SuperPlugin PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# ========================================
# PLUGIN 2: ParticleCloudPlugin (Particle System)
# ========================================
set(PARTICLECLOUD_SOURCES
    ParticleCloudPlugin.cpp
    ${FFGL_COMMON_SOURCES}
)

add_library(ParticleCloudPlugin SHARED ${PARTICLECLOUD_SOURCES})

target_compile_definitions(ParticleCloudPlugin PRIVATE
    FFGL_EXPORTS
    _WINDOWS
)

target_link_libraries(ParticleCloudPlugin ${OPENGL_gl_LIBRARY})

set_target_properties(ParticleCloudPlugin PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# ========================================
# Install targets
# ========================================
install(TARGETS SuperPlugin ParticleCloudPlugin
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)

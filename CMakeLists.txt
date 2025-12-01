cmake_minimum_required(VERSION 3.10)
project(ParticleCloudPlugin)
set(CMAKE_CXX_STANDARD 14)

# FFGL SDK paths
set(FFGL_SDK_ROOT "${CMAKE_SOURCE_DIR}/ffgl-sdk")
set(FFGL_SOURCE_DIR "${FFGL_SDK_ROOT}/source")

include_directories(
    ${FFGL_SOURCE_DIR}/lib/ffgl
    ${FFGL_SOURCE_DIR}/lib/ffglquickstart
    ${FFGL_SDK_ROOT}/deps/glew-2.1.0/include
)

# FFGL core sources (EXACTOS en tu SDK)
set(FFGL_CORE_SOURCES
    ${FFGL_SOURCE_DIR}/lib/ffgl/FFGL.cpp
    ${FFGL_SOURCE_DIR}/lib/ffgl/FFGLLog.cpp
    ${FFGL_SOURCE_DIR}/lib/ffgl/FFGLPluginInfo.cpp
    ${FFGL_SOURCE_DIR}/lib/ffgl/FFGLPluginInfoData.cpp
    ${FFGL_SOURCE_DIR}/lib/ffgl/FFGLPluginManager.cpp
    ${FFGL_SOURCE_DIR}/lib/ffgl/FFGLPluginSDK.cpp
    ${FFGL_SOURCE_DIR}/lib/ffgl/FFGLThumbnailInfo.cpp
)

# Plugin source
set(PLUGIN_SOURCES
    ParticleCloudModern.cpp
    ${FFGL_CORE_SOURCES}
)

add_library(ParticleCloudPlugin SHARED ${PLUGIN_SOURCES})

find_package(OpenGL REQUIRED)
target_link_libraries(ParticleCloudPlugin ${OPENGL_gl_LIBRARY})

# GLEW static lib (exists in your SDK)
target_link_libraries(ParticleCloudPlugin
    ${FFGL_SDK_ROOT}/deps/glew-2.1.0/lib/Release/x64/glew32s.lib
)

set_target_properties(ParticleCloudPlugin PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

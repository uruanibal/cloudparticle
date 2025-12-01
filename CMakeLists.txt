cmake_minimum_required(VERSION 3.15)
project(ParticleCloudModern)

set(CMAKE_CXX_STANDARD 17)

# Path to the embedded FFGL SDK
set(FFGL_SDK_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/ffgl-sdk")

include(${FFGL_SDK_ROOT}/cmake/macros.cmake)

add_subdirectory(${FFGL_SDK_ROOT} ffgl_build)

add_library(ParticleCloudModern SHARED
    ParticleCloudModern.cpp
)

target_include_directories(ParticleCloudModern PRIVATE
    ${FFGL_SDK_ROOT}/source
)

target_link_libraries(ParticleCloudModern
    FFGLSDK
)

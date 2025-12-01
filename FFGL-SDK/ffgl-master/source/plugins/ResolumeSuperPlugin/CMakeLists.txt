cmake_minimum_required(VERSION 3.10)

project(SuperPlugin)

# Assuming this CMakeLists.txt is in: FFGL_SDK/source/plugins/SuperPlugin/
# So FFGL_ROOT is 3 levels up
get_filename_component(FFGL_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../.." ABSOLUTE)

include(${FFGL_ROOT}/cmake/macros.cmake)

# Create the plugin
ffgl_create_effect_plugin(
	TARGET SuperPlugin
	PLUGIN_INFO
		"SP01"                      # Plugin ID (4 chars)
		"Super Ultra Plugin"        # Plugin Name
		"Antigravity AI"            # About
		"Ultimate VJ Effects Suite" # Description
		1                           # Major version
		0                           # Minor version
	SOURCES
		SuperPlugin.cpp
)

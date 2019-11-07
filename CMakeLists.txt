# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

include(vendor/cmake-precompiled-header/PrecompiledHeader.cmake)

project ("Hazel" VERSION 0.1 DESCRIPTION "Hazel Interactive App Engine")

add_subdirectory("Hazel")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("Hazel/vendor/glfw")

add_subdirectory("Hazel/vendor/glad")

add_subdirectory("Hazel/vendor/glm")

add_subdirectory("Hazel/vendor/imgui")

add_subdirectory("Hazel/vendor/spdlog")

add_subdirectory("Sandbox")

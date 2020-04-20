cmake_minimum_required (VERSION 3.10)

include(vendor/cmake-precompiled-header/PrecompiledHeader.cmake)
project ("Hazel" VERSION 0.1 DESCRIPTION "Hazel Interactive App Engine")

set(CMAKE_CXX_STANDARD 17)

add_subdirectory("Hazel")
add_subdirectory("Sandbox")

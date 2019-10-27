# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

project ("Hazel" VERSION 0.1 DESCRIPTION "Hazel Interactive App Engine")

add_subdirectory ("Hazel")
add_subdirectory ("Sandbox")

# CMakeList.txt : CMake project for Hazel shared library, include source and define
# Hazel shared library project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

add_library(
   Hazel SHARED
   "src/Hazel.cpp"
)

target_include_directories(
   Hazel PUBLIC
   "include"
)

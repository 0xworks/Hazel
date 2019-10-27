# CMakeList.txt : CMake project for Hazel shared library, include source and define
# Hazel shared library project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

add_library(
   Hazel SHARED
   "src/Events/ApplicationEvent.cpp"
   "src/Events/Event.cpp"
   "src/Events/KeyEvent.cpp"
   "src/Events/MouseEvent.cpp"
   "src/Application.cpp"
   "src/Log.cpp"
)

target_include_directories(
   Hazel PUBLIC
   "include"
   "vendor/spdlog/include"
)

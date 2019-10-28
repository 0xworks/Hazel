# CMakeList.txt : CMake project for Hazel shared library, include source and define
# Hazel shared library project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

set(
   HazelSources
   "src/Events/ApplicationEvent.cpp"
   "src/Events/Event.cpp"
   "src/Events/KeyEvent.cpp"
   "src/Events/MouseEvent.cpp"
   "src/Application.cpp"
   "src/hzpch.cpp"
   "src/Log.cpp"
   "src/Window.cpp"
)

if(WIN32)
   list(
      APPEND HazelSources
      "Platform/Windows/WindowsWindow.cpp"
   )
endif()

set(
   HazelIncludes
   "."
   "include"
   "vendor/spdlog/include"
   "vendor/glfw/include"
)

if(WIN32)
   list(
      APPEND HazelIncludes
      "Platform/Windows"
   )
endif(WIN32)

set(
   HazelLibs
   "glfw"
)

add_library(Hazel SHARED ${HazelSources})

add_precompiled_header(Hazel "include/hzpch.h" SOURCE_CXX "src/hzpch.cpp")

target_compile_definitions(
   Hazel PUBLIC
  "$<$<CONFIG:DEBUG>:HZ_ENABLE_ASSERTS>"
)

target_include_directories(Hazel PUBLIC ${HazelIncludes})

target_link_libraries(Hazel PUBLIC ${HazelLibs})

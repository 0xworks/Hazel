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
   "hzpch.cpp"
   "src/ImGuiLayer.cpp"
   "src/Layer.cpp"
   "src/LayerStack.cpp"
   "src/Log.cpp"
   "src/Window.cpp"
   "Platform/OpenGL/imgui_impl_opengl3.cpp"
)

if(WIN32)
   list(
      APPEND HazelSources
      "Platform/Windows/WindowsInput.cpp"
      "Platform/Windows/WindowsWindow.cpp"
   )
endif()

set(
   HazelIncludes
   "."
   "include"
)

if(WIN32)
   list(
      APPEND HazelIncludes
      "Platform/Windows"
   )
endif(WIN32)

set(
   HazelLibs
   "glad"
   "glfw"
   "imgui"
   "spdlog"
)

add_library(Hazel STATIC ${HazelSources})


add_precompiled_header(Hazel "hzpch.h" SOURCE_CXX "hzpch.cpp")

set_target_properties(
   Hazel PROPERTIES
   CXX_STANDARD 17
)

target_compile_definitions(
   Hazel PRIVATE
   GLFW_INCLUDE_NONE
  "$<$<CONFIG:DEBUG>:HZ_ENABLE_ASSERTS>"
)

target_include_directories(Hazel PUBLIC ${HazelIncludes})

target_link_libraries(Hazel PRIVATE ${HazelLibs})

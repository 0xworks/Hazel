# CMakeList.txt : CMake project for Hazel shared library, include source and define
# Hazel shared library project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

#
# IMGUI library
# This is here (as opposed to in vendor/imgui folder) for two reasons
# 1) I dont want to make any changes to the imgui submodule
# 2) Some of this is not specific to imgui but rather is stuff that we are borrowing from the imgui examples
#    in order to implment IMGUI in our application

add_library(
   imgui STATIC
   "vendor/imgui/imgui.cpp"
   "vendor/imgui/imgui_draw.cpp"
   "vendor/imgui/imgui_widgets.cpp"
   "vendor/imgui/imgui_demo.cpp"
   "vendor/imgui/examples/imgui_impl_opengl3.cpp"
   "vendor/imgui/examples/imgui_impl_glfw.cpp"
)

target_compile_definitions(
   imgui PRIVATE
   IMGUI_IMPL_OPENGL_LOADER_GLAD
)

target_include_directories(
   imgui PUBLIC
   "vendor/imgui"
)

target_link_libraries(
   imgui PUBLIC
   "glad"
   "glfw"
)

set(
   HazelSources
   "src/Application.cpp"
   "src/Events/ApplicationEvent.cpp"
   "src/Events/Event.cpp"
   "src/Events/KeyEvent.cpp"
   "src/Events/MouseEvent.cpp"
   "hzpch.cpp"
   "src/ImGuiLayer.cpp"
   "src/Layer.cpp"
   "src/LayerStack.cpp"
   "src/Log.cpp"
   "src/Renderer/IndexBuffer.cpp"
   "src/Renderer/Renderer.cpp"
   "src/Renderer/Shader.cpp"
   "src/Renderer/VertexBuffer.cpp"
   "src/Window.cpp"
)

if(WIN32)
   list(
      APPEND HazelSources
      "Platform/OpenGL/OpenGLContext.cpp"
      "Platform/OpenGL/OpenGLIndexBuffer.cpp"
      "Platform/OpenGL/OpenGLVertexBuffer.cpp"
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
   "glm"
   "imgui"
   "spdlog_header_only"
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

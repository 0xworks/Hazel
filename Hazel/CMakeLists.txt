# CMakeList.txt : CMake project for Hazel shared library, include source and define
# Hazel shared library project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(imgui REQUIRED)
find_package(spdlog REQUIRED)
find_package(Stb REQUIRED)

set(
   HazelSources
   "hzpch.cpp"
   "src/Core/Application.cpp"
   "src/Core/stb_image.cpp"
   "src/Core/Window.cpp"
   "src/Core/ImGuiLayer.cpp"
   "src/Core/Layer.cpp"
   "src/Core/LayerStack.cpp"
   "src/Core/Log.cpp"
   "src/Events/ApplicationEvent.cpp"
   "src/Events/Event.cpp"
   "src/Events/KeyEvent.cpp"
   "src/Events/MouseEvent.cpp"
   "src/Renderer/BufferLayout.cpp"
   "src/Renderer/IndexBuffer.cpp"
   "src/Renderer/OrthographicCamera.cpp"
   "src/Renderer/OrthographicCameraController.cpp"
   "src/Renderer/RenderCommand.cpp"
   "src/Renderer/Renderer.cpp"
   "src/Renderer/Renderer2D.cpp"
   "src/Renderer/RendererAPI.cpp"
   "src/Renderer/Shader.cpp"
   "src/Renderer/ShaderLibrary.cpp"
   "src/Renderer/Texture.cpp"
   "src/Renderer/VertexArray.cpp"
   "src/Renderer/VertexBuffer.cpp"
   "Platform/OpenGL/OpenGLContext.cpp"
   "Platform/OpenGL/OpenGLIndexBuffer.cpp"
   "Platform/OpenGL/OpenGLRendererAPI.cpp"
   "Platform/OpenGL/OpenGLShader.cpp"
   "Platform/OpenGL/OpenGLTexture.cpp"
   "Platform/OpenGL/OpenGLVertexArray.cpp"
   "Platform/OpenGL/OpenGLVertexBuffer.cpp"
   "vendor/imgui/imgui_impl_glfw.h"
   "vendor/imgui/imgui_impl_glfw.cpp"
   "vendor/imgui/imgui_impl_opengl3.h"
   "vendor/imgui/imgui_impl_opengl3.cpp"
   "../vendor/Tracy/TracyClient.cpp"
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
   "vendor/imgui"
)

if(WIN32)
   list(
      APPEND HazelIncludes
      "Platform/Windows"
   )
endif(WIN32)

set(
   HazelLibs
   "glad::glad"
   "glfw"
   "glm"
   "imgui::imgui"
   "spdlog::spdlog_header_only"
)

add_library(Hazel STATIC ${HazelSources})

set_target_properties(
   Hazel PROPERTIES
   CXX_STANDARD 17
)

add_precompiled_header(Hazel "hzpch.h" SOURCE_CXX "hzpch.cpp")

# no precompiled header for imgui impls
set_source_files_properties(
   "vendor/imgui/imgui_impl_glfw.cpp" PROPERTIES
   COMPILE_FLAGS /Y-
)

set_source_files_properties(
   "vendor/imgui/imgui_impl_opengl3.cpp" PROPERTIES
   COMPILE_FLAGS /Y-
)

# no precompiled header for TracyClient.cpp
set_source_files_properties(
   "../vendor/Tracy/TracyClient.cpp" PROPERTIES
   COMPILE_FLAGS /Y-
)


target_compile_definitions(
   Hazel PUBLIC
   FMT_HEADER_ONLY
   GLFW_INCLUDE_NONE
   IMGUI_IMPL_OPENGL_LOADER_GLAD
  "$<$<CONFIG:DEBUG>:HZ_ENABLE_ASSERTS>"
)

target_include_directories(
   Hazel PUBLIC
   ${HazelIncludes}
)

target_link_libraries(
   Hazel
   PUBLIC ${HazelLibs}
)

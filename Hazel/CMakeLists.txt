# CMakeList.txt : CMake project for Hazel shared library, include source and define
# Hazel shared library project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(imgui REQUIRED)
find_package(spdlog REQUIRED)

set(ProjectName Hazel)

set(
   ProjectSources
   "hzpch.cpp"
   "Core/Application.h"
   "Core/Application.cpp"
   "Core/Window.h"
   "Core/Window.cpp"
   "Core/ImGuiLayer.h"
   "Core/ImGuiLayer.cpp"
   "Core/Layer.h"
   "Core/Layer.cpp"
   "Core/LayerStack.h"
   "Core/LayerStack.cpp"
   "Core/Log.h"
   "Core/Log.cpp"
   "Events/ApplicationEvent.h"
   "Events/ApplicationEvent.cpp"
   "Events/Event.h"
   "Events/Event.cpp"
   "Events/KeyEvent.h"
   "Events/KeyEvent.cpp"
   "Events/MouseEvent.h"
   "Events/MouseEvent.cpp"
   "Renderer/BufferLayout.h"
   "Renderer/BufferLayout.cpp"
   "Renderer/IndexBuffer.h"
   "Renderer/IndexBuffer.cpp"
   "Renderer/OrthographicCamera.h"
   "Renderer/OrthographicCamera.cpp"
   "Renderer/OrthographicCameraController.h"
   "Renderer/OrthographicCameraController.cpp"
   "Renderer/RenderCommand.h"
   "Renderer/RenderCommand.cpp"
   "Renderer/Renderer.h"
   "Renderer/Renderer.cpp"
   "Renderer/Renderer2D.h"
   "Renderer/Renderer2D.cpp"
   "Renderer/RendererAPI.h"
   "Renderer/RendererAPI.cpp"
   "Renderer/Shader.h"
   "Renderer/Shader.cpp"
   "Renderer/ShaderLibrary.h"
   "Renderer/ShaderLibrary.cpp"
   "Renderer/Texture.h"
   "Renderer/Texture.cpp"
   "Renderer/VertexArray.h"
   "Renderer/VertexArray.cpp"
   "Renderer/VertexBuffer.h"
   "Renderer/VertexBuffer.cpp"
   "Platform/OpenGL/OpenGLContext.h"
   "Platform/OpenGL/OpenGLContext.cpp"
   "Platform/OpenGL/OpenGLIndexBuffer.h"
   "Platform/OpenGL/OpenGLIndexBuffer.cpp"
   "Platform/OpenGL/OpenGLRendererAPI.h"
   "Platform/OpenGL/OpenGLRendererAPI.cpp"
   "Platform/OpenGL/OpenGLShader.h"
   "Platform/OpenGL/OpenGLShader.cpp"
   "Platform/OpenGL/OpenGLTexture.h"
   "Platform/OpenGL/OpenGLTexture.cpp"
   "Platform/OpenGL/OpenGLVertexArray.h"
   "Platform/OpenGL/OpenGLVertexArray.cpp"
   "Platform/OpenGL/OpenGLVertexBuffer.h"
   "Platform/OpenGL/OpenGLVertexBuffer.cpp"
   "vendor/imgui/imgui_impl_glfw.h"
   "vendor/imgui/imgui_impl_glfw.cpp"
   "vendor/imgui/imgui_impl_opengl3.h"
   "vendor/imgui/imgui_impl_opengl3.cpp"
   "vendor/stb/stb_image.h"
   "vendor/stb/stb_image.cpp"
   "../vendor/Tracy/TracyClient.cpp"
)

if(WIN32)
   list(
      APPEND ProjectSources
      "Platform/Windows/WindowsInput.cpp"
      "Platform/Windows/WindowsWindow.cpp"
   )
endif()

set(
   ProjectIncludes
   "."
   "vendor/imgui"
)

if(WIN32)
   list(
      APPEND ProjectIncludes
      "Platform/Windows"
   )
endif(WIN32)

set(
   ProjectLibs
   "glad::glad"
   "glfw"
   "glm"
   "imgui::imgui"
   "spdlog::spdlog_header_only"
)

add_library(${ProjectName} STATIC ${ProjectSources})

set_target_properties(
   ${ProjectName} PROPERTIES
   CXX_STANDARD 17
)

add_precompiled_header(${ProjectName} "hzpch.h" SOURCE_CXX "hzpch.cpp")

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
   ${ProjectName} PUBLIC
   FMT_HEADER_ONLY
   GLFW_INCLUDE_NONE
   IMGUI_IMPL_OPENGL_LOADER_GLAD
  "$<$<CONFIG:DEBUG>:HZ_ENABLE_ASSERTS>"
)

target_include_directories(
   ${ProjectName} PRIVATE
   ${ProjectIncludes}
)

target_include_directories(
   ${ProjectName} PUBLIC
   "${PROJECT_SOURCE_DIR}"
)

target_link_libraries(
   ${ProjectName} PUBLIC
   ${ProjectLibs}
)

cmake_minimum_required (VERSION 3.10)

find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(imgui REQUIRED)
find_package(spdlog REQUIRED)

project ("Hazel" VERSION 0.1 DESCRIPTION "Hazel Interactive App Engine")

set(
	ProjectSources
	"src/hzpch.cpp"
	"src/Hazel/Components/Camera.h"
	"src/Hazel/Components/Transform.h"
	"src/Hazel/Core/Application.h"
	"src/Hazel/Core/Application.cpp"
	"src/Hazel/Core/Core.h"
	"src/Hazel/Core/EntryPoint.h"
	"src/Hazel/Core/ImGuiLayer.h"
	"src/Hazel/Core/ImGuiLayer.cpp"
	"src/Hazel/Core/Input.h"
	"src/Hazel/Core/KeyCodes.h"
	"src/Hazel/Core/Layer.h"
	"src/Hazel/Core/Layer.cpp"
	"src/Hazel/Core/LayerStack.h"
	"src/Hazel/Core/LayerStack.cpp"
	"src/Hazel/Core/Log.h"
	"src/Hazel/Core/Log.cpp"
	"src/Hazel/Core/MouseButtonCodes.h"
	"src/Hazel/Core/Timestep.h"
	"src/Hazel/Core/Window.h"
	"src/Hazel/Core/Window.cpp"
	"src/Hazel/Debug/Instrumentor.h"
	"src/Hazel/ECS/ComponentArray.h"
	"src/Hazel/ECS/ComponentManager.h"
	"src/Hazel/ECS/ECS.h"
	"src/Hazel/ECS/ECS.cpp"
	"src/Hazel/ECS/ECSType.h"
	"src/Hazel/ECS/EntityManager.h"
	"src/Hazel/ECS/System.h"
	"src/Hazel/ECS/SystemManager.h"
	"src/Hazel/Events/Event.h"
	"src/Hazel/Events/EventManager.h"
	"src/Hazel/Events/Events.h"
	"src/Hazel/Events/Events.cpp"
	"src/Hazel/Events/EventType.h"
	"src/Hazel/Events/KeyEvent.h"
	"src/Hazel/Events/MouseEvent.h"
	"src/Hazel/Events/WindowEvent.h"
	"src/Hazel/Renderer/BufferLayout.h"
	"src/Hazel/Renderer/BufferLayout.cpp"
	"src/Hazel/Renderer/GraphicsContext.h"
	"src/Hazel/Renderer/IndexBuffer.h"
	"src/Hazel/Renderer/IndexBuffer.cpp"
	"src/Hazel/Renderer/RenderCommand.h"
	"src/Hazel/Renderer/RenderCommand.cpp"
	"src/Hazel/Renderer/Renderer.h"
	"src/Hazel/Renderer/Renderer.cpp"
	"src/Hazel/Renderer/Renderer2D.h"
	"src/Hazel/Renderer/Renderer2D.cpp"
	"src/Hazel/Renderer/RendererAPI.h"
	"src/Hazel/Renderer/RendererAPI.cpp"
	"src/Hazel/Renderer/Shader.h"
	"src/Hazel/Renderer/Shader.cpp"
	"src/Hazel/Renderer/ShaderLibrary.h"
	"src/Hazel/Renderer/ShaderLibrary.cpp"
	"src/Hazel/Renderer/Texture.h"
	"src/Hazel/Renderer/Texture.glsl.h"
	"src/Hazel/Renderer/Texture.cpp"
	"src/Hazel/Renderer/VertexArray.h"
	"src/Hazel/Renderer/VertexArray.cpp"
	"src/Hazel/Renderer/VertexBuffer.h"
	"src/Hazel/Renderer/VertexBuffer.cpp"
	"src/Hazel/Systems/CameraController2D.h"
	"src/Hazel/Systems/CameraController2D.cpp"
	"src/Platform/OpenGL/OpenGLContext.h"
	"src/Platform/OpenGL/OpenGLContext.cpp"
	"src/Platform/OpenGL/OpenGLIndexBuffer.h"
	"src/Platform/OpenGL/OpenGLIndexBuffer.cpp"
	"src/Platform/OpenGL/OpenGLRendererAPI.h"
	"src/Platform/OpenGL/OpenGLRendererAPI.cpp"
	"src/Platform/OpenGL/OpenGLShader.h"
	"src/Platform/OpenGL/OpenGLShader.cpp"
	"src/Platform/OpenGL/OpenGLTexture.h"
	"src/Platform/OpenGL/OpenGLTexture.cpp"
	"src/Platform/OpenGL/OpenGLVertexArray.h"
	"src/Platform/OpenGL/OpenGLVertexArray.cpp"
	"src/Platform/OpenGL/OpenGLVertexBuffer.h"
	"src/Platform/OpenGL/OpenGLVertexBuffer.cpp"
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
		"src/Platform/Windows/WindowsInput.cpp"
		"src/Platform/Windows/WindowsWindow.cpp"
	)
endif()

set(
	ProjectIncludes
	"src"
	"vendor"
)

if(WIN32)
	list(
		APPEND ProjectIncludes
		"src/Platform/Windows"
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

add_library(${PROJECT_NAME} STATIC ${ProjectSources})

set_target_properties(
	${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 17
)

add_precompiled_header(${PROJECT_NAME} "hzpch.h" SOURCE_CXX "src/hzpch.cpp")

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
	${PROJECT_NAME} PUBLIC
	FMT_HEADER_ONLY
	GLFW_INCLUDE_NONE
	IMGUI_IMPL_OPENGL_LOADER_GLAD
  "$<$<CONFIG:DEBUG>:HZ_ENABLE_ASSERTS>"
)

target_include_directories(
	${PROJECT_NAME} PRIVATE
	${ProjectIncludes}
)

target_include_directories(
	${PROJECT_NAME} PUBLIC
	"src"
	"../vendor"
)

target_link_libraries(
	${PROJECT_NAME} PUBLIC
	${ProjectLibs}
)

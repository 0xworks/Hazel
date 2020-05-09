#pragma once

#include "Hazel/Renderer/RenderCommand.h"
#include "Hazel/Renderer/Shader.h"

namespace Hazel {

	class Renderer {
	public:
		static RendererAPI::API GetRendererAPI();

		static void Init();
		static void ShutDown();

		static void BeginScene(const glm::mat4& viewProjectionMatrix);
		static void EndScene();

		static void Submit(Shader& shader, const VertexArray& vertexArray, const glm::mat4& transform);

		static void OnWindowResized(const uint32_t width, const uint32_t height);

	};

}
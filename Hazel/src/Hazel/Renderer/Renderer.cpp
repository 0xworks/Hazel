#include "hzpch.h"
#include "Renderer.h"

#include "Hazel/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Hazel {

	static glm::mat4 s_viewProjectionMatrix;

	RendererAPI::API Renderer::GetRendererAPI() {
		return RendererAPI::GetAPI();
	}


	void Renderer::Init() {
		RenderCommand::Init();
		Renderer2D::Init();
	}


	void Renderer::ShutDown() {
		Renderer2D::ShutDown();
	}


	void Renderer::BeginScene(const glm::mat4& viewProjectionMatrix) {
		s_viewProjectionMatrix = viewProjectionMatrix;
	}


	void Renderer::EndScene() {}


	void Renderer::Submit(Shader& shader, const VertexArray& vertexArray, const glm::mat4& transform) {
		shader.Bind();
		shader.SetMat4("u_viewProjection", s_viewProjectionMatrix);
		shader.SetMat4("u_transform", transform);
		vertexArray.Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::OnWindowResized(const uint32_t width, const uint32_t height) {
		RenderCommand::SetViewport(0, 0, width, height);
	}

}

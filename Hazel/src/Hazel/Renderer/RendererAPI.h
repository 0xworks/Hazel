#pragma once

#include "Hazel/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Hazel {

	class RendererAPI {
	public:

		enum class API {
			None = 0,
			OpenGL
		};

	public:
		virtual void Init() = 0;
		virtual void SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const VertexArray& vertexArray, const uint32_t indexCount = 0) = 0;

		static API GetAPI();

	private:
		static API s_API;

	};
}

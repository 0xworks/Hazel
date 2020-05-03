#include "hzpch.h"
#include "VertexBuffer.h"

#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGlVertexBuffer.h"

namespace Hazel {

	std::unique_ptr<Hazel::VertexBuffer> VertexBuffer::Create(const uint32_t size) {
		if (Renderer::GetRendererAPI() == RendererAPI::API::OpenGL) {
			return std::make_unique<OpenGLVertexBuffer>(size);
		}
		HZ_CORE_ASSERT(false, "Renderer API not supported!")
			return  nullptr;
	}


	std::unique_ptr<VertexBuffer> VertexBuffer::Create(const float* vertices, const uint32_t size) {
		if (Renderer::GetRendererAPI() == RendererAPI::API::OpenGL) {
			return std::make_unique<OpenGLVertexBuffer>(vertices, size);
		}
		HZ_CORE_ASSERT(false, "Renderer API not supported!")
			return  nullptr;
	}

}

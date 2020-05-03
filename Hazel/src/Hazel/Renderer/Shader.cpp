#include "hzpch.h"
#include "Shader.h"

#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel {

	std::unique_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
		if (Renderer::GetRendererAPI() == RendererAPI::API::OpenGL) {
			return std::make_unique<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		HZ_CORE_ASSERT(false, "Renderer API not supported!");
		return  nullptr;
	}


	std::unique_ptr<Hazel::Shader> Shader::Create(const std::string& path, const std::string& name) {
		if (Renderer::GetRendererAPI() == RendererAPI::API::OpenGL) {
			return std::make_unique<OpenGLShader>(path, name);
		}
		HZ_CORE_ASSERT(false, "Renderer API not supported!");
		return  nullptr;
	}

}

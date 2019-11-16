#include "hzpch.h"
#include "Renderer/Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer/Renderer.h"

namespace Hazel {

   std::unique_ptr<Shader> Shader::Create(const std::string& sVertexSrc, const std::string& sFragmentSrc) {
      if (Renderer::GetRendererAPI() == RendererAPI::API::OpenGL) {
         return std::make_unique<OpenGLShader>(sVertexSrc, sFragmentSrc);
      }
      HZ_CORE_ASSERT(false, "Renderer API not supported!")
      return  nullptr;
   }

}

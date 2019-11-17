#include "hzpch.h"
#include "Renderer/Texture.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGlTexture.h"

namespace Hazel {

   std::unique_ptr<Texture2D> Texture2D::Create(const std::string& path) {
      if (Renderer::GetRendererAPI() == RendererAPI::API::OpenGL) {
         return std::make_unique<OpenGLTexture2D>(path);
      }
      HZ_CORE_ASSERT(false, "Renderer API not supported!")
         return  nullptr;
   }

}

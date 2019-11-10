#include "hzpch.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGlIndexBuffer.h"

namespace Hazel {
   std::unique_ptr<IndexBuffer> IndexBuffer::Create(const uint32_t* indices, const uint32_t count) {
      if (Renderer::GetRendererAPI() == RendererAPI::OpenGL) {
         return std::make_unique<OpenGLIndexBuffer>(indices, count);
      }
      HZ_CORE_ASSERT(false, "Renderer API not supported!")
      return  nullptr;
   }

}

#include "hzpch.h"
#include "Renderer/VertexBuffer.h"

#include "Platform/OpenGL/OpenGlVertexBuffer.h"
#include "Renderer/Renderer.h"

namespace Hazel {

   std::unique_ptr<VertexBuffer> VertexBuffer::Create(const float* vertices, const uint32_t count) {
      if (Renderer::GetRendererAPI() == RendererAPI::API::OpenGL) {
         return std::make_unique<OpenGLVertexBuffer>(vertices, count);
      }
      HZ_CORE_ASSERT(false, "Renderer API not supported!")
      return  nullptr;
   }

}

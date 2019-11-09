#include "hzpch.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGlVertexBuffer.h"

namespace Hazel {
   VertexBuffer* VertexBuffer::Create(const float* vertices, const size_t count) {
      if (Renderer::GetRendererAPI() == RendererAPI::OpenGL) {
         return new OpenGLVertexBuffer(vertices, count);
      }
      HZ_CORE_ASSERT(false, "Renderer API not supported!")
      return  nullptr;
   }

}

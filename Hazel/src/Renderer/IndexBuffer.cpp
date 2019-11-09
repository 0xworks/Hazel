#include "hzpch.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGlIndexBuffer.h"

namespace Hazel {
   IndexBuffer* IndexBuffer::Create(const unsigned int* indices, const size_t count) {
      if (Renderer::GetRendererAPI() == RendererAPI::OpenGL) {
         return new OpenGLIndexBuffer(indices, count);
      }
      HZ_CORE_ASSERT(false, "Renderer API not supported!")
      return  nullptr;
   }

}

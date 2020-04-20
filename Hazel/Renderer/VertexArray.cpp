#include "hzpch.h"
#include "Renderer/VertexArray.h"

#include "Platform/OpenGL/OpenGlVertexArray.h"
#include "Renderer/Renderer.h"

namespace Hazel {

   std::unique_ptr<VertexArray> VertexArray::Create() {
      if (Renderer::GetRendererAPI() == RendererAPI::API::OpenGL) {
         return std::make_unique<OpenGLVertexArray>();
      }
      HZ_CORE_ASSERT(false, "Renderer API not supported!")
         return  nullptr;
   }

}

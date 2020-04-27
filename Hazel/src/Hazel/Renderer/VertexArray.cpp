#include "hzpch.h"
#include "Hazel/Renderer/VertexArray.h"

#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGlVertexArray.h"

namespace Hazel {

   std::unique_ptr<VertexArray> VertexArray::Create() {
      if (Renderer::GetRendererAPI() == RendererAPI::API::OpenGL) {
         return std::make_unique<OpenGLVertexArray>();
      }
      HZ_CORE_ASSERT(false, "Renderer API not supported!")
         return  nullptr;
   }

}

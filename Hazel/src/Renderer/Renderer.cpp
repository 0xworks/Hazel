#include "hzpch.h"
#include "Renderer/Renderer.h"

namespace Hazel {

   RendererAPI::API Renderer::GetRendererAPI() {
      return RendererAPI::GetAPI();
   }


   void Renderer::BeginScene() {}


   void Renderer::EndScene() {}


   void Renderer::Submit(const VertexArray& vertexArray) {
      vertexArray.Bind();
      RenderCommand::DrawIndexed(vertexArray);
   }

}
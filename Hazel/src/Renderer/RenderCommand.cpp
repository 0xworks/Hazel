#include "hzpch.h"
#include "Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel {

   std::unique_ptr<RendererAPI> RenderCommand::sm_rendererAPI = std::make_unique<OpenGLRendererAPI>();

   void RenderCommand::SetClearColor(glm::vec4 color) {
      sm_rendererAPI->SetClearColor(color);
   }

   void RenderCommand::Clear() {
      sm_rendererAPI->Clear();
   }

   void RenderCommand::DrawIndexed(const VertexArray& vertexArray) {
      sm_rendererAPI->DrawIndexed(vertexArray);
   }

}
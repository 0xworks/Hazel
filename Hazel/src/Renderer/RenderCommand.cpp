#include "hzpch.h"
#include "Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel {

   std::unique_ptr<RendererAPI> RenderCommand::sm_rendererAPI = std::make_unique<OpenGLRendererAPI>();

   void RenderCommand::Init() {
      sm_rendererAPI->Init();
   }

   void RenderCommand::SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height) {
      sm_rendererAPI->SetViewport(x, y, width, height);
   }

   void RenderCommand::SetClearColor(const glm::vec4& color) {
      sm_rendererAPI->SetClearColor(color);
   }

   void RenderCommand::Clear() {
      sm_rendererAPI->Clear();
   }

   void RenderCommand::DrawIndexed(const VertexArray& vertexArray) {
      sm_rendererAPI->DrawIndexed(vertexArray);
   }

}
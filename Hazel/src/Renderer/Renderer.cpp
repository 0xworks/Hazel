#include "hzpch.h"
#include "Renderer/Renderer.h"

#include "glm/glm.hpp"

namespace Hazel {

   static glm::mat4 s_viewProjectionMatrix;

   RendererAPI::API Renderer::GetRendererAPI() {
      return RendererAPI::GetAPI();
   }


   void Renderer::BeginScene(const OrthographicCamera& camera) {
      s_viewProjectionMatrix = camera.GetViewProjectionMatrix();
   }


   void Renderer::EndScene() {}


   void Renderer::Submit(const Shader& shader, const VertexArray& vertexArray) {
      shader.Bind();
      shader.UploadUniformMat4("u_ViewProjection", s_viewProjectionMatrix);
      vertexArray.Bind();
      RenderCommand::DrawIndexed(vertexArray);
   }

}
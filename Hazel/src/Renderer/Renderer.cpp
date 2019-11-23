#include "hzpch.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "glm/glm.hpp"

namespace Hazel {

   static glm::mat4 s_viewProjectionMatrix;

   RendererAPI::API Renderer::GetRendererAPI() {
      return RendererAPI::GetAPI();
   }


   void Renderer::Init() {
      RenderCommand::Init();
   }


   void Renderer::BeginScene(const OrthographicCamera& camera) {
      s_viewProjectionMatrix = camera.GetViewProjectionMatrix();
   }


   void Renderer::EndScene() {}


   void Renderer::Submit(Shader& shader, const VertexArray& vertexArray, const glm::mat4& transform) {
      shader.Bind();
      dynamic_cast<OpenGLShader&>(shader).UploadUniformMat4("u_viewProjection", s_viewProjectionMatrix);
      dynamic_cast<OpenGLShader&>(shader).UploadUniformMat4("u_transform", transform);
      vertexArray.Bind();
      RenderCommand::DrawIndexed(vertexArray);
   }

   void Renderer::OnWindowResized(const uint32_t width, const uint32_t height) {
      RenderCommand::SetViewport(0, 0, width, height);
   }

}
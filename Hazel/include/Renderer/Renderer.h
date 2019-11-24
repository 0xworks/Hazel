#pragma once

#include "Renderer/OrthographicCamera.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Shader.h"

namespace Hazel {

   class Renderer {
   public:
      static RendererAPI::API GetRendererAPI();

      static void Init();
      static void ShutDown();

      static void BeginScene(const OrthographicCamera& camera);
      static void EndScene();

      static void Submit(Shader& shader, const VertexArray& vertexArray, const glm::mat4& transform);

      static void OnWindowResized(const uint32_t width, const uint32_t height);

   };

}
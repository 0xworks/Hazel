#pragma once

#include "../Renderer/OrthographicCamera.h"
#include "../Renderer/RenderCommand.h"
#include "../Renderer/Shader.h"
#include "../Renderer/Texture.h"

namespace Hazel {

   class Renderer2D {
   public:

      static void Init();
      static void ShutDown();

      static void BeginScene(const OrthographicCamera& camera);
      static void EndScene();

      static void Flush();

      static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const float rotationDegrees, const glm::vec4& color);
      static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const float rotationDegrees, const glm::vec4& color);
      static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const float rotationDegrees, const Texture& texture, const float tilingFactor = 1.0f, const glm::vec4& color = glm::vec4(1.0f));
      static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const float rotationDegrees, const Texture& texture, const float tilingFactor = 1.0f, const glm::vec4& color = glm::vec4(1.0f));

   };

}

#pragma once

#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "Shader.h"

namespace Hazel {

   class Renderer2D {
   public:

      static void Init();
      static void ShutDown();

      static void BeginScene(const OrthographicCamera& camera);
      static void EndScene();

      static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
      static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

   };

}

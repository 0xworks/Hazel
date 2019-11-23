#pragma once

#include "Renderer/RendererAPI.h"
#include "Renderer/VertexArray.h"

#include "glm/glm.hpp"

#include <memory>

namespace Hazel {

   class RenderCommand {
   public:

      static void Init();
      static void SetViewport(const uint32_t left, const uint32_t top, const uint32_t right, const uint32_t bottom);
      static void SetClearColor(const glm::vec4& color);
      static void Clear();
      static void DrawIndexed(const VertexArray& vertexArray);

   private:
      static std::unique_ptr<RendererAPI> sm_rendererAPI;

   };

}
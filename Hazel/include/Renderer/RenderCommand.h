#pragma once

#include "Renderer/RendererAPI.h"
#include "Renderer/VertexArray.h"

#include "glm/glm.hpp"

#include <memory>

namespace Hazel {

   class RenderCommand {
   public:

      static void Init();
      static void SetClearColor(glm::vec4 color);
      static void Clear();
      static void DrawIndexed(const VertexArray& vertexArray);

   private:
      static std::unique_ptr<RendererAPI> sm_rendererAPI;

   };

}
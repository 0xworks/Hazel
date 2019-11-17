#pragma once

#include "glm/glm.hpp"
#include "Renderer/VertexArray.h"

namespace Hazel {

   class RendererAPI {
   public:

      enum class API {
         None = 0,
         OpenGL
      };

   public:
      virtual void Init() = 0;

      virtual void SetClearColor(const glm::vec4& color) = 0;
      virtual void Clear() = 0;

      virtual void DrawIndexed(const VertexArray&) = 0;

      static API GetAPI();

   private:
      static API s_API;

   };
}
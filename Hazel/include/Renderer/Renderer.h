#pragma once

#include "RenderCommand.h"

namespace Hazel {

   class Renderer {
   public:
      static RendererAPI::API GetRendererAPI();

      static void BeginScene();
      static void EndScene();

      static void Submit(const VertexArray& vertexArray);


   };

}
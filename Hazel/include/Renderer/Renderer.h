#pragma once

#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "Shader.h"

namespace Hazel {

   class Renderer {
   public:
      static RendererAPI::API GetRendererAPI();

      static void BeginScene(const OrthographicCamera& camera);
      static void EndScene();

      static void Submit(const Shader& shader, const VertexArray& vertexArray);


   };

}
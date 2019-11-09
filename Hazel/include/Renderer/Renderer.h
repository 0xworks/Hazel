#pragma once

namespace Hazel {

   enum class RendererAPI {
      None = 0,
      OpenGL
   };


   class Renderer {
   public:

      static RendererAPI GetRendererAPI() { return sm_rendererAPI; }

   private:
      static RendererAPI sm_rendererAPI;
   };

}
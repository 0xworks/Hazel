#include "hzpch.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Hazel {

   void OpenGLRendererAPI::Init() {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_DEPTH_TEST);
   }


   void OpenGLRendererAPI::SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height) {
      glViewport(x, y, width, height);
   }


   void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
      glClearColor(color.r, color.g, color.b, color.a);
   }


   void OpenGLRendererAPI::Clear() {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   }


   void OpenGLRendererAPI::DrawIndexed(const VertexArray& vertexArray, const uint32_t indexCount) {
      glDrawElements(GL_TRIANGLES, indexCount? indexCount : vertexArray.GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
   }

}


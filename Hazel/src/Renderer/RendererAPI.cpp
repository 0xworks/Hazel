#include "hzpch.h"
#include "Renderer/RendererAPI.h"

namespace Hazel {

   RendererAPI::API RendererAPI::s_API = API::OpenGL;

   RendererAPI::API Hazel::RendererAPI::GetAPI() {
      return s_API;
   }


}

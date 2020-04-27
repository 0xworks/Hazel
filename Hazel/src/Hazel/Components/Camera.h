#pragma once

#include <glm/glm.hpp>

namespace Hazel {

   struct Camera {
      glm::mat4 ViewProjectionMatrix;

      static glm::mat4 MakeOrthographic(const float left, const float top, const float right, const float bottom);
   };

}

#pragma once

#include <glm/glm.hpp>

namespace Hazel {

   struct Camera {
      glm::mat4 ProjectionMatrix;
      glm::mat4 ViewMatrix;
      glm::mat4 ViewProjectionMatrix;
   };

}

#pragma once

#include <glm/glm.hpp>

namespace Hazel {

   struct Transform {
      glm::vec3 Position;
      glm::vec3 RotationRadians;
      glm::vec3 Scale;
   };

}

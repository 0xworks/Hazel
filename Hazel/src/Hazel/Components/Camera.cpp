#include "hzpch.h"
#include "Hazel/Components/Camera.h"

#include <glm/ext.hpp>

namespace Hazel {

   glm::mat4 Camera::MakeOrthographic(float left, float top, float right, float bottom) {
      return glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
   }

}

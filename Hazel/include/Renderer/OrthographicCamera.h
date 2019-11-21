#pragma once

#include "glm/glm.hpp"

namespace Hazel {

   class OrthographicCamera {
   public:

      OrthographicCamera(float left, float top, float right, float bottom);

      void SetProjection(float left, float top, float right, float bottom);

      const glm::vec3& GetPosition() const;
      void SetPosition(const glm::vec3& position);

      float GetRotation() const;
      void SetRotation(const float f);

      const glm::mat4& GetProjectionMatrix() const;

      const glm::mat4 GetViewMatrix() const;

      const glm::mat4& GetViewProjectionMatrix() const;

   private:
      void RecalculateViewMatrix();

   private:
      glm::mat4 m_projectionMatrix;
      glm::mat4 m_viewMatrix;
      glm::mat4 m_viewProjectionMatrix;

      glm::vec3 m_position;
      float m_rotation;

   };

}
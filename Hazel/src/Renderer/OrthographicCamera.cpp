#include "hzpch.h"
#include "Renderer/OrthographicCamera.h"

#include "glm/ext.hpp"

namespace Hazel {


   OrthographicCamera::OrthographicCamera(float left, float top, float right, float bottom)
   : m_projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
   , m_viewMatrix(glm::identity<glm::mat4>())
   , m_viewProjectionMatrix(m_projectionMatrix * m_viewMatrix)
   , m_position(glm::zero<glm::vec3>())
   , m_rotation(0)
   {
   }

   const glm::vec3& OrthographicCamera::GetPosition() const {
      return m_position;
   }

   void OrthographicCamera::SetPosition(const glm::vec3& position) {
      m_position = position;
      RecalculateViewMatrix();
   }

   float OrthographicCamera::GetRotation() const {
      return m_rotation;
   }

   void OrthographicCamera::SetRotation(const float f) {
      m_rotation = f;
      RecalculateViewMatrix();
   }

   const glm::mat4& OrthographicCamera::GetProjectionMatrix() const {
      return m_projectionMatrix;
   }

   const glm::mat4 OrthographicCamera::GetViewMatrix() const {
      return m_viewMatrix;
   }

   const glm::mat4& OrthographicCamera::GetViewProjectionMatrix() const {
      return m_viewProjectionMatrix;
   }

   void OrthographicCamera::RecalculateViewMatrix() {
      glm::mat4 transform = glm::translate(glm::identity<glm::mat4>(), m_position) * glm::rotate(glm::identity<glm::mat4>(), glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 0.1f));
      m_viewMatrix = glm::inverse(transform);
      m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
   }

}

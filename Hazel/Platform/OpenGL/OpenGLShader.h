#pragma once

#include "Renderer/Shader.h"
#include "glm/glm.hpp"

namespace Hazel {

   class OpenGLShader : public Shader {
   public:
      OpenGLShader(const std::string& path);
      OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
      virtual ~OpenGLShader();

      virtual void Bind() const override;
      virtual void Unbind() const override;

      void UploadUniformUInt(const std::string& name, const uint32_t ui) const;
      void UploadUniformMat4(const std::string& name, const glm::mat4& mat) const;
      void UploadUniformVec3(const std::string& name, const glm::vec3& vec) const;
      void UploadUniformVec4(const std::string& name, const glm::vec4& vec) const;

   private:
      uint32_t m_shaderId;
   };
}
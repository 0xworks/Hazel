#pragma once

#include "Renderer/Shader.h"
#include "glm/glm.hpp"

namespace Hazel {

   class OpenGLShader : public Shader {
   public:
      OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
      OpenGLShader(const std::string& path, const std::string& name = std::string());
      virtual ~OpenGLShader();

      virtual const std::string& GetName() const override;

      virtual void Bind() const override;
      virtual void Unbind() const override;

      void SetUInt32(const std::string& name, const uint32_t ui) override;
      void SetMat4(const std::string& name, const glm::mat4& mat4) override;
      void SetVec3(const std::string& name, const glm::vec3& vec3) override;
      void SetVec4(const std::string& name, const glm::vec4& vec4) override;

   private:
      std::string m_name;
      uint32_t m_shaderId;
   };
}
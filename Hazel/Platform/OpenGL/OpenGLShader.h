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

      // note: even though these functions don't modify any data in the Shader class itself
      //       conceptually they do modify the shader
      void UploadUniformUInt(const std::string& name, const uint32_t ui);
      void UploadUniformMat4(const std::string& name, const glm::mat4& mat);
      void UploadUniformVec3(const std::string& name, const glm::vec3& vec);
      void UploadUniformVec4(const std::string& name, const glm::vec4& vec);

   private:
      std::string m_name;
      uint32_t m_shaderId;
   };
}
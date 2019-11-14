#pragma once

#include "glm/glm.hpp"

namespace Hazel {

   class Shader {
   public:
      Shader(const std::string& vertexSource, const std::string& fragmentSource);
      virtual ~Shader();

      void Bind() const;
      void Unbind() const;

      void UploadUniformMat4(const std::string& name, const glm::mat4& uniform) const;

   private:
      uint32_t m_shaderId;
   };
}
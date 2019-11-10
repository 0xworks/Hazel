#pragma once

#include <string>

namespace Hazel {

   class Shader {
   public:
      Shader(const std::string& vertexSource, const std::string& fragmentSource);
      virtual ~Shader();

      void Bind() const;
      void Unbind() const;

   private:
      uint32_t m_shaderId;
   };
}
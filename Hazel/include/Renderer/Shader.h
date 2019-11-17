#pragma once

#include <memory>
#include <string>

namespace Hazel {

   class Shader {
   public:
      virtual ~Shader() = default;

      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;

   public:
      static std::unique_ptr<Shader> Create(const std::string& path);
      static std::unique_ptr<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);

   };
}
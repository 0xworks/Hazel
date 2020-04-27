#pragma once

#include <glm/glm.hpp>

#include <memory>
#include <string>

namespace Hazel {

   class Shader {
   public:
      virtual ~Shader() = default;

      virtual const std::string& GetName() const = 0;

      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;

      virtual void SetIntArray(const std::string& name, const int* data, const uint32_t count) = 0;
      virtual void SetUInt(const std::string& name, const uint32_t ui) = 0;
      virtual void SetUIntArray(const std::string& name, const uint32_t* data, const uint32_t count) = 0;
      virtual void SetMat4(const std::string& name, const glm::mat4& mat4) = 0;
      virtual void SetVec3(const std::string& name, const glm::vec3& vec3) = 0;
      virtual void SetVec4(const std::string& name, const glm::vec4& vec4) = 0;

   public:
      static std::unique_ptr<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
      static std::unique_ptr<Shader> Create(const std::string& path, const std::string& name = std::string());

   };
}
#include <hzpch.h>
#include "Renderer/ShaderLibrary.h"

namespace Hazel {

   void ShaderLibrary::Add(std::shared_ptr<Shader> shader) {
      const auto& name = shader->GetName();
      HZ_CORE_ASSERT(m_shaders.find(name) == m_shaders.end(), "Shader '{0}' already exists!", name);
      m_shaders[name] = std::move(shader);
   }


   std::shared_ptr<Shader> ShaderLibrary::LoadShader(const std::string& path, const std::string& name) {
      std::shared_ptr<Shader> shader = Shader::Create(path, name);
      Add(shader);
      return shader;
   }


   std::shared_ptr<Shader> ShaderLibrary::GetShader(const std::string& name) const {
      HZ_CORE_ASSERT(m_shaders.find(name) != m_shaders.end(), "Shader '{0}' does not exist!", name);
      return m_shaders.at(name);
   }

}
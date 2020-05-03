#pragma once

#include "Hazel/Renderer/Shader.h"

#include <string>
#include <unordered_map>

namespace Hazel {

	class ShaderLibrary {
	public:
		void Add(std::shared_ptr<Shader> shader);

		// Load shader from specified path, and store it with specified name.
		// If name is empty, then it will be set to the filename from path.
		// Eg. Load("Assets/Shaders/FlatShader.glsl")  --> name = "FlatShader"
		std::shared_ptr<Shader> LoadShader(const std::string& path, const std::string& name = std::string());

		std::shared_ptr<Shader> GetShader(const std::string& name) const;

	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
	};

}

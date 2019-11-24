#include "hzpch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"
#include "glm/ext.hpp"

#undef _HAS_CXX17
#define _HAS_CXX17 1
#include <filesystem>

#include <fstream>

namespace Hazel {

   // temporary
   static std::string ReadFile(const std::string& path) {
      std::string result;
      std::ifstream in(path, std::ios::in | std::ios::binary);
      if (in) {
         in.seekg(0, std::ios::end);
         size_t size = in.tellg();
         if (size != -1) {
            result.resize(size);
            in.seekg(0, std::ios::beg);
            in.read(&result[0], size);
            in.close();
         } else {
            HZ_CORE_ERROR("Could not read from file '{0}'", path);
         }
      } else {
         HZ_CORE_ERROR("Could not open file '{0}'", path);
      }
      return result;
   }


   static GLenum ShaderTypeFromString(const std::string& type) {
      if (type == "vertex")
         return GL_VERTEX_SHADER;
      if (type == "fragment" || type == "pixel")
         return GL_FRAGMENT_SHADER;

      HZ_CORE_ASSERT(false, "Unknown shader type!");
      return 0;
   }


   static std::string InjectPreprocessorDefinition(const std::string& source, const std::string& definition) {
      const char* versionToken = "#version";
      size_t versionTokenLength = strlen(versionToken);
      size_t pos = source.find(versionToken, 0);
      size_t nextLinePos = 0;
      if (pos != std::string::npos) {
         size_t eol = source.find_first_of("\r\n", pos);
         HZ_CORE_ASSERT(eol != std::string::npos, "Syntax error");

         nextLinePos = source.find_first_not_of("\r\n", eol);
         HZ_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
      }
      return source.substr(0, nextLinePos) + "#define " + definition + "\r\n" + source.substr(nextLinePos);
   }


   static GLuint Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {

      GLuint program = glCreateProgram();
      HZ_CORE_ASSERT((shaderSources.size() > 0) && (shaderSources.size() <= 2), "We only support 2 shaders for now");
      std::array<GLenum, 2> glShaderIDs;
      int glShaderIDIndex = 0;
      for (const auto& [type, source] : shaderSources) {

         GLuint shader = glCreateShader(type);

         const GLchar* sourceCStr = source.c_str();
         glShaderSource(shader, 1, &sourceCStr, 0);

         glCompileShader(shader);

         GLint isCompiled = 0;
         glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
         if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(shader);

            HZ_CORE_ERROR("{0}", infoLog.data());
            HZ_CORE_ASSERT(false, "Shader compilation failure!");
            break;
         }

         glAttachShader(program, shader);
         glShaderIDs[glShaderIDIndex++] = shader;
      }

      glLinkProgram(program);

      GLint isLinked = 0;
      glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
      if (isLinked == GL_FALSE) {
         GLint maxLength = 0;
         glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

         std::vector<GLchar> infoLog(maxLength);
         glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

         glDeleteProgram(program);

         for (auto id : glShaderIDs) {
            glDeleteShader(id);
         }

         HZ_CORE_ERROR("{0}", infoLog.data());
         HZ_CORE_ASSERT(false, "Shader link failure!");
         return program;
      }

      for (auto id : glShaderIDs) {
         glDetachShader(program, id);
         glDeleteShader(id);
      }

      return program;
   }


   OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
   : m_name(name)
   , m_shaderId(
      Compile({
         {GL_VERTEX_SHADER, vertexSrc},
         {GL_FRAGMENT_SHADER, fragmentSrc}
      })
   )
   {}


   OpenGLShader::OpenGLShader(const std::string& path, const std::string& name)
   : m_name(name.empty()? std::filesystem::path(path).filename().replace_extension().string() : name)
   , m_shaderId(0)
   {
      std::string source = ReadFile(path);
      m_shaderId = Compile({
         {GL_VERTEX_SHADER, InjectPreprocessorDefinition(source, "VERTEX_SHADER")},
         {GL_FRAGMENT_SHADER, InjectPreprocessorDefinition(source, "FRAGMENT_SHADER")}
      });
   }


   OpenGLShader::~OpenGLShader() {
      glDeleteProgram(m_shaderId);
   }


   const std::string& OpenGLShader::GetName() const {
      return m_name;
   }


   void OpenGLShader::Bind() const {
      glUseProgram(m_shaderId);
   }


   void OpenGLShader::Unbind() const {
      glUseProgram(0);
   }


   void OpenGLShader::SetUInt32(const std::string& name, const uint32_t ui) {
      GLint location = glGetUniformLocation(m_shaderId, name.c_str());
      glUniform1ui(location, (GLuint)ui);
   }


   void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& mat4) {
      GLint location = glGetUniformLocation(m_shaderId, name.c_str());
      glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat4));
   }


   void OpenGLShader::SetVec3(const std::string& name, const glm::vec3& vec3) {
      GLint location = glGetUniformLocation(m_shaderId, name.c_str());
      glUniform3fv(location, 1, glm::value_ptr(vec3));
   }

   void OpenGLShader::SetVec4(const std::string& name, const glm::vec4& vec4) {
      GLint location = glGetUniformLocation(m_shaderId, name.c_str());
      glUniform4fv(location, 1, glm::value_ptr(vec4));
   }

}
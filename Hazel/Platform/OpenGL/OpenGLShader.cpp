#include "hzpch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"
#include "glm/ext.hpp"

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


   static std::unordered_map<GLenum, std::string> PreProcess(const std::string& source) {
      std::unordered_map<GLenum, std::string> shaderSources;

      const char* typeToken = "#type";
      size_t typeTokenLength = strlen(typeToken);
      size_t pos = source.find(typeToken, 0);
      while (pos != std::string::npos) {
         size_t eol = source.find_first_of("\r\n", pos);
         HZ_CORE_ASSERT(eol != std::string::npos, "Syntax error");
         size_t begin = pos + typeTokenLength + 1;
         std::string type = source.substr(begin, eol - begin);
         HZ_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

         size_t nextLinePos = source.find_first_not_of("\r\n", eol);
         HZ_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
         pos = source.find(typeToken, nextLinePos);

         shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
      }

      return shaderSources;
   }


   static GLuint Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {

      GLuint program = glCreateProgram();
      HZ_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now");
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


   OpenGLShader::OpenGLShader(const std::string& path)
   : m_shaderId(0)
   {
      m_shaderId = Compile(PreProcess(ReadFile(path)));
   }


   OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
   : m_shaderId(
      Compile({
         {GL_VERTEX_SHADER, vertexSrc},
         {GL_FRAGMENT_SHADER, fragmentSrc}
      })
   )
   {}


   OpenGLShader::~OpenGLShader() {
      glDeleteProgram(m_shaderId);
   }


   void OpenGLShader::Bind() const {
      glUseProgram(m_shaderId);
   }


   void OpenGLShader::Unbind() const {
      glUseProgram(0);
   }


   void OpenGLShader::UploadUniformUInt(const std::string& name, const uint32_t ui) const {
      GLint location = glGetUniformLocation(m_shaderId, name.c_str());
      glUniform1ui(location, (GLuint)ui);
   }


   void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& mat) const {
      GLint location = glGetUniformLocation(m_shaderId, name.c_str());
      glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
   }


   void OpenGLShader::UploadUniformVec3(const std::string& name, const glm::vec3& vec) const {
      GLint location = glGetUniformLocation(m_shaderId, name.c_str());
      glUniform3fv(location, 1, glm::value_ptr(vec));
   }


   void OpenGLShader::UploadUniformVec4(const std::string& name, const glm::vec4& vec) const {
      GLint location = glGetUniformLocation(m_shaderId, name.c_str());
      glUniform4fv(location, 1, glm::value_ptr(vec));
   }

}
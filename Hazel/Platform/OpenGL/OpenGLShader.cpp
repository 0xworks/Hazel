#include "hzpch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"
#include "glm/ext.hpp"

namespace Hazel {

   OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
      : m_shaderId(0) {

      // Create an empty vertex OpenGLShader handle
      GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

      // Send the vertex OpenGLShader source code to GL
      // Note that std::string's .c_str is NULL character terminated.
      const GLchar* source = (const GLchar*)vertexSrc.c_str();
      glShaderSource(vertexShader, 1, &source, 0);

      // Compile the vertex OpenGLShader
      glCompileShader(vertexShader);

      GLint isCompiled = 0;
      glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
      if (isCompiled == GL_FALSE) {
         GLint maxLength = 0;
         glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

         // The maxLength includes the NULL character
         std::vector<GLchar> infoLog(maxLength);
         glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

         // We don't need the OpenGLShader anymore.
         glDeleteShader(vertexShader);

         HZ_CORE_ERROR("{0}", infoLog.data());
         HZ_CORE_ASSERT(false, "Vertex OpenGLShader compilation failed!");
         return;
      }

      // Create an empty fragment OpenGLShader handle
      GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

      // Send the fragment OpenGLShader source code to GL
      // Note that std::string's .c_str is NULL character terminated.
      source = (const GLchar*)fragmentSrc.c_str();
      glShaderSource(fragmentShader, 1, &source, 0);

      // Compile the fragment OpenGLShader
      glCompileShader(fragmentShader);

      glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
      if (isCompiled == GL_FALSE) {
         GLint maxLength = 0;
         glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

         // The maxLength includes the NULL character
         std::vector<GLchar> infoLog(maxLength);
         glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

         // We don't need the OpenGLShader anymore.
         glDeleteShader(fragmentShader);
         // Either of them. Don't leak shaders.
         glDeleteShader(vertexShader);

         HZ_CORE_ERROR("{0}", infoLog.data());
         HZ_CORE_ASSERT(false, "Fragment OpenGLShader compilation failed!");
         return;
      }

      // Vertex and fragment shaders are successfully compiled.
      // Now time to link them together into a program.
      // Get a program object.
      m_shaderId = glCreateProgram();

      // Attach our shaders to our program
      glAttachShader(m_shaderId, vertexShader);
      glAttachShader(m_shaderId, fragmentShader);

      // Link our program
      glLinkProgram(m_shaderId);

      // Note the different functions here: glGetProgram* instead of glGetShader*.
      GLint isLinked = 0;
      glGetProgramiv(m_shaderId, GL_LINK_STATUS, (int*)&isLinked);
      if (isLinked == GL_FALSE) {
         GLint maxLength = 0;
         glGetProgramiv(m_shaderId, GL_INFO_LOG_LENGTH, &maxLength);

         // The maxLength includes the NULL character
         std::vector<GLchar> infoLog(maxLength);
         glGetProgramInfoLog(m_shaderId, maxLength, &maxLength, &infoLog[0]);

         // We don't need the program anymore.
         glDeleteProgram(m_shaderId);
         // Don't leak shaders either.
         glDeleteShader(vertexShader);
         glDeleteShader(fragmentShader);

         HZ_CORE_ERROR("{0}", infoLog.data());
         HZ_CORE_ASSERT(false, "OpenGLShader linking failed!");
         return;
      }

      // Always detach shaders after a successful link.
      glDetachShader(m_shaderId, vertexShader);
      glDetachShader(m_shaderId, fragmentShader);
   }


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
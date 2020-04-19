#include "hzpch.h"
#include "OpenGLVertexArray.h"
#include "OpenGLVertexBuffer.h"

#include "glad/glad.h"

namespace Hazel {

   GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
      switch (type) {
         case ShaderDataType::Float:   return GL_FLOAT;
         case ShaderDataType::Float2:  return GL_FLOAT;
         case ShaderDataType::Float3:  return GL_FLOAT;
         case ShaderDataType::Float4:  return GL_FLOAT;
         case ShaderDataType::Mat3:    return GL_FLOAT;
         case ShaderDataType::Mat4:    return GL_FLOAT;
         case ShaderDataType::UInt:    return GL_UNSIGNED_INT;
         case ShaderDataType::UInt2:   return GL_UNSIGNED_INT;
         case ShaderDataType::UInt3:   return GL_UNSIGNED_INT;
         case ShaderDataType::UInt4:   return GL_UNSIGNED_INT;
         case ShaderDataType::Int:     return GL_INT;
         case ShaderDataType::Int2:    return GL_INT;
         case ShaderDataType::Int3:    return GL_INT;
         case ShaderDataType::Int4:    return GL_INT;
         case ShaderDataType::Bool:    return GL_BOOL;
      }
      HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
      return 0;
   }


   OpenGLVertexArray::OpenGLVertexArray() {
      glCreateVertexArrays(1, &m_vertexArrayId);
   }


   OpenGLVertexArray::~OpenGLVertexArray() {
      glDeleteVertexArrays(1, &m_vertexArrayId);
   }


   void Hazel::OpenGLVertexArray::Bind() const {
      glBindVertexArray(m_vertexArrayId);
   }


   void Hazel::OpenGLVertexArray::Unbind() const {
      glBindVertexArray(0);
   }


   void OpenGLVertexArray::SetIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer) {
      glBindVertexArray(m_vertexArrayId);
      indexBuffer->Bind();
      m_indexBuffer = std::move(indexBuffer);
   }


   void OpenGLVertexArray::SetVertexBuffer(std::unique_ptr<VertexBuffer> vertexBuffer) {
      HZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size() > 0, "VertexBuffer has no layout!");

      glBindVertexArray(m_vertexArrayId);
      vertexBuffer->Bind();
      uint32_t index = 0;
      const auto& layout = vertexBuffer->GetLayout();
      for (const auto& element : layout) {
         intptr_t offset = element.Offset;
         glEnableVertexAttribArray(index);
         glVertexAttribPointer(
            index,
            element.GetComponentCount(),
            ShaderDataTypeToOpenGLBaseType(element.Type),
            element.Normalized ? GL_TRUE : GL_FALSE,
            layout.GetStride(),
            (const void*)offset
         );
         ++index;
      }
      m_vertexBuffer = std::move(vertexBuffer);
   }


   VertexBuffer& OpenGLVertexArray::GetVertexBuffer() const {
      return *m_vertexBuffer.get();
   }


   const IndexBuffer& OpenGLVertexArray::GetIndexBuffer() const {
      return *m_indexBuffer.get();
   }

}

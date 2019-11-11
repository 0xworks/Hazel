#pragma once

#include "Renderer/VertexArray.h"

namespace Hazel {

   class OpenGLVertexArray : public VertexArray {
   public:
      OpenGLVertexArray();
      virtual ~OpenGLVertexArray();

      virtual void Bind() const override;
      virtual void Unbind() const override;

      virtual void SetIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer) override;
      virtual void AddVertexBuffer(std::unique_ptr<VertexBuffer> vertexBuffer) override;

      virtual const std::vector<std::unique_ptr<VertexBuffer>>& GetVertexBuffers() const override;
      virtual const IndexBuffer& GetIndexBuffer() const override;

   private:
      std::vector<std::unique_ptr<VertexBuffer>> m_vertexBuffers;
      std::unique_ptr<IndexBuffer> m_indexBuffer;
      uint32_t m_vertexArrayId;
   };

}
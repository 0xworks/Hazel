#pragma once

#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexBuffer.h"

namespace Hazel {

   class VertexArray {
   public:
      virtual ~VertexArray() {}

      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;

      virtual void SetIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer) = 0;
      virtual void AddVertexBuffer(std::unique_ptr<VertexBuffer> vertexBuffer) = 0;

      virtual const std::vector<std::unique_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
      virtual const IndexBuffer& GetIndexBuffer() const = 0;

      static std::unique_ptr<VertexArray> Create();

   };

}
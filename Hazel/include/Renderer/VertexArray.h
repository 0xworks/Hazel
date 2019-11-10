#pragma once

#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexBuffer.h"

namespace Hazel {

   class VertexArray {
   public:
      virtual ~VertexArray() {}

      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;

      virtual void AddIndexBuffer(const shared_ptr<IndexBuffer>& indexBuffer) = 0;
      virtual void AddVertexBuffer(const shared_ptr<VertexBuffer>& vertexBuffer) = 0;

      static std::unique_ptr<VertexArray> Create();

   };

}
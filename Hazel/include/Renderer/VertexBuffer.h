#pragma once

#include "Renderer/BufferLayout.h"

namespace Hazel {

   class VertexBuffer {
   public:
      virtual ~VertexBuffer() = default;

      virtual const BufferLayout& GetLayout() const = 0;
      virtual void SetLayout(const BufferLayout& layout) = 0;
      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;
      virtual uint32_t GetCount() const = 0;

   public:
      static std::unique_ptr<VertexBuffer> Create(const float* vertices, const uint32_t count);

   };

}
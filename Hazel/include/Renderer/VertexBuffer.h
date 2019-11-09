#pragma once

namespace Hazel {

   class VertexBuffer {
   public:
      virtual ~VertexBuffer() {}

      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;
      virtual size_t GetCount() const = 0;

      static VertexBuffer* Create(const float* vertices, const size_t count);

   };

}
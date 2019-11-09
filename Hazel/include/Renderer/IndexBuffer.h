#pragma once

namespace Hazel {

   class IndexBuffer {
   public:
      virtual ~IndexBuffer() {}

      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;

      virtual size_t GetCount() const = 0;

      static IndexBuffer* Create(const unsigned int* indices, const size_t count);

   };
}

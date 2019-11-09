#pragma once

#include "Renderer/IndexBuffer.h"

namespace Hazel {

   class OpenGLIndexBuffer : public IndexBuffer {
   public:
      OpenGLIndexBuffer(const unsigned int* indices, const size_t count);
      virtual ~OpenGLIndexBuffer();

      virtual void Bind() const override;
      virtual void Unbind() const override;

      virtual size_t GetCount() const override;

   private:
      unsigned int m_indexBufferId;
      size_t m_count;
   };

}
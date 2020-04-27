#pragma once

#include "Hazel/Renderer/IndexBuffer.h"

namespace Hazel {

   class OpenGLIndexBuffer : public IndexBuffer {
   public:
      OpenGLIndexBuffer(const uint32_t* indices, const uint32_t count);
      virtual ~OpenGLIndexBuffer();

      virtual void Bind() const override;
      virtual void Unbind() const override;

      virtual uint32_t GetCount() const override;

   private:
      uint32_t m_indexBufferId;
      uint32_t m_count;
   };

}
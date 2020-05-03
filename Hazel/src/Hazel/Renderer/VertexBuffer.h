#pragma once

#include "Hazel/Renderer/BufferLayout.h"

#include <memory>

namespace Hazel {

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual void SetData(const void* data, const uint32_t size) = 0;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

	public:
		static std::unique_ptr<VertexBuffer> Create(const uint32_t size);
		static std::unique_ptr<VertexBuffer> Create(const float* vertices, const uint32_t size);

	};

}

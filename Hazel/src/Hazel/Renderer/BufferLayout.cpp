#include "hzpch.h"
#include "BufferLayout.h"

namespace Hazel {

	uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Float:   return sizeof(float);
			case ShaderDataType::Float2:  return sizeof(float) * 2;
			case ShaderDataType::Float3:  return sizeof(float) * 3;
			case ShaderDataType::Float4:  return sizeof(float) * 4;
			case ShaderDataType::Mat3:    return sizeof(float) * 3 * 3;
			case ShaderDataType::Mat4:    return sizeof(float) * 4 * 4;
			case ShaderDataType::UInt:    return sizeof(uint32_t);
			case ShaderDataType::UInt2:   return sizeof(uint32_t) * 2;
			case ShaderDataType::UInt3:   return sizeof(uint32_t) * 3;
			case ShaderDataType::UInt4:   return sizeof(uint32_t) * 4;
			case ShaderDataType::Int:     return sizeof(int);
			case ShaderDataType::Int2:    return sizeof(int) * 2;
			case ShaderDataType::Int3:    return sizeof(int) * 3;
			case ShaderDataType::Int4:    return sizeof(int) * 4;
			case ShaderDataType::Bool:    return sizeof(bool);
		}
		HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}


	uint32_t ShaderDataTypeComponentCount(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3 * 3;
			case ShaderDataType::Mat4:    return 4 * 4;
			case ShaderDataType::UInt:    return 1;
			case ShaderDataType::UInt2:   return 2;
			case ShaderDataType::UInt3:   return 3;
			case ShaderDataType::UInt4:   return 4;
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::Bool:    return 1;
		}
		HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}


	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) : m_elements(elements), m_stride(0) {
		CalculateOffsetsAndStride();
	}


	void BufferLayout::CalculateOffsetsAndStride() {
		uint32_t offset = 0;
		for (auto& element : m_elements) {
			element.Offset = offset;
			offset += element.Size;
		}
		m_stride = offset;
	}
}

#include "hzpch.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace Hazel {

	OpenGLVertexBuffer::OpenGLVertexBuffer(const uint32_t size) {
		glCreateBuffers(1, &m_vertexBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}


	OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, const uint32_t size) {
		glCreateBuffers(1, &m_vertexBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}



	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &m_vertexBufferId);
	}


	const BufferLayout& OpenGLVertexBuffer::GetLayout() const {
		return m_layout;
	}


	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout) {
		m_layout = layout;
	}


	void OpenGLVertexBuffer::SetData(const void* data, const uint32_t size) {
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}


	void Hazel::OpenGLVertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	}


	void Hazel::OpenGLVertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}

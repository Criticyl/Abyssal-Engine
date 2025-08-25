#include "abyssalpch.h"

#include "OpenGLVertexBuffer.h"
#include <glad/glad.h>

namespace Abyssal {

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, std::uint32_t size)
    {
        glCreateBuffers(1, &m_BufferID);
        glNamedBufferData(m_BufferID, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_BufferID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::SetData(const void* data, std::uint32_t size)
    {
        glNamedBufferData(m_BufferID, size, data, GL_DYNAMIC_DRAW);
    }

}

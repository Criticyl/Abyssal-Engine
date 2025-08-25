#include "abyssalpch.h"

#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace Abyssal {

    OpenGLIndexBuffer::OpenGLIndexBuffer(std::uint32_t* indices, std::uint32_t count)
        : m_Count(count)
    {
        glCreateBuffers(1, &m_BufferID);
        glNamedBufferData(m_BufferID, count * sizeof(std::uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_BufferID);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void OpenGLIndexBuffer::SetData(const void* data, std::uint32_t count)
    {
        glNamedBufferData(m_BufferID, count * sizeof(std::uint32_t), data, GL_STATIC_DRAW);
    }

}

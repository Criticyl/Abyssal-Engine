#pragma once

#include "Abyssal/Renderer/VertexBuffer.h"

namespace Abyssal {

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, std::uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual void SetData(const void* data, std::uint32_t size) override;
        virtual void SetLayout(const BufferLayout& layout) { m_Layout = layout; };
        virtual const BufferLayout& GetLayout() const { return m_Layout; };
    private:
        std::uint32_t m_BufferID;
        BufferLayout m_Layout;
    };
}

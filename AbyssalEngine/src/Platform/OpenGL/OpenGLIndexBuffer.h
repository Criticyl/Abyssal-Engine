#pragma once

#include "Abyssal/Renderer/IndexBuffer.h"

namespace Abyssal {

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(std::uint32_t* indices, std::uint32_t count);
        virtual ~OpenGLIndexBuffer();

        void Bind() const override;
        void Unbind() const override;
        void SetData(const void* data, std::uint32_t count) override;

        virtual std::uint32_t GetCount() const { return m_Count; }
    private:
        std::uint32_t m_BufferID;
        std::uint32_t m_Count;
    };
}
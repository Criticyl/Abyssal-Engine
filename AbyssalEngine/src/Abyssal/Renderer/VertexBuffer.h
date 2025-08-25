#pragma once

#include <cstdint>

#include "BufferLayout.h"

namespace Abyssal {

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void SetData(const void* data, std::uint32_t size) = 0;
        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;

        static std::unique_ptr<VertexBuffer> Create(float* vertices, std::uint32_t size);
    };
}
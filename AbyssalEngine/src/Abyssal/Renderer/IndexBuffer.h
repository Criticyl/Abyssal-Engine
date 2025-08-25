#pragma once

#include <cstdint>

namespace Abyssal {

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void SetData(const void* data, std::uint32_t size) = 0;

        virtual std::uint32_t GetCount() const = 0;

        static std::unique_ptr<IndexBuffer> Create(std::uint32_t* indices, std::uint32_t size);
    };
}

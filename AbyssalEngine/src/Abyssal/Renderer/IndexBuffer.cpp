#include "abyssalpch.h"

#include "IndexBuffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Abyssal {

    std::unique_ptr<IndexBuffer> IndexBuffer::Create(std::uint32_t* indices, std::uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None: 
            ABYSSAL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::OpenGL: 
            return std::make_unique<OpenGLIndexBuffer>(indices, size);

        }

        ABYSSAL_CORE_ASSERT(false, "Unknown renderer API!");
        return nullptr;
    }
}
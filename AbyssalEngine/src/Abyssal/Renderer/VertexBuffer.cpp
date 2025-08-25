#include "abyssalpch.h"

#include "VertexBuffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Abyssal {

    std::unique_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, std::uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None: 
                ABYSSAL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::OpenGL: 
                return std::make_unique<OpenGLVertexBuffer>(vertices, size);

        }

        ABYSSAL_CORE_ASSERT(false, "Unknown renderer API!");
        return nullptr;
    }
}
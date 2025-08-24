#pragma once

namespace Abyssal {

    class RendererContext
    {
    public:
        virtual ~RendererContext() = default;
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    protected:
        RendererContext() = default;
    };
}

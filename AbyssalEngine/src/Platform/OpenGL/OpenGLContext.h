#pragma once

#include "Abyssal/Renderer/RendererContext.h"

struct GLFWwindow;

namespace Abyssal {

    class OpenGLContext : public RendererContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);
        
        virtual void Init() override;
        virtual void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };
}
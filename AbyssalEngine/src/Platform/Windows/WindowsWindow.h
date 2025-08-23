#pragma once

#include "Abyssal/Window.h"

#include <GLFW/glfw3.h>

namespace Abyssal {

    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowSettings& settings);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_WindowData.Width; }
        inline unsigned int GetHeight() const override { return m_WindowData.Height; };

        inline void SetEventCallback(const EventCallbackFunc& callback) override { m_WindowData.EventCallback = callback;  }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        inline virtual void* GetNativeWindow() const { return m_Window; }
    private:
        virtual void Init(const WindowSettings& settings);
        virtual void Shutdown();
    private:
        GLFWwindow* m_Window;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            EventCallbackFunc EventCallback;
        };

        WindowData m_WindowData;
    };
}

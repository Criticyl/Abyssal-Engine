#include "abyssalpch.h"
#include "WindowsWindow.h"

namespace Abyssal {

    static bool s_GLFWInitialized = false;

    Window* Window::Create(const WindowSettings& settings)
    {
        return new WindowsWindow(settings);
    }

    WindowsWindow::WindowsWindow(const WindowSettings& settings)
    {
        Init(settings);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::Init(const WindowSettings& settings)
    {
        m_WindowData.Title = settings.Title;
        m_WindowData.Width = settings.Width;
        m_WindowData.Height = settings.Height;

        ABYSSAL_CORE_INFO("Creating window {0}, {1}x{2}", m_WindowData.Title, m_WindowData.Width, m_WindowData.Height);

        if (!s_GLFWInitialized)
        {
            int success = glfwInit();
            ABYSSAL_CORE_ASSERT(success, "Could not initialize GLFW!")

            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)m_WindowData.Width, (int)m_WindowData.Height, m_WindowData.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_WindowData);
        SetVSync(true);
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_WindowData.VSync;
    }
}
#include "abyssalpch.h"
#include "Application.h"

#include "Abyssal/Log.h"

#include <GLFW/glfw3.h>

namespace Abyssal {

#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this , std::placeholders::_1)

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));
    }

    Application::~Application()
    {

    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClosed));

        ABYSSAL_CORE_TRACE("{0}", event.ToString());
    }

    void Application::Run() 
    {
        

        while (m_Running)
        {
            glClearColor(1.0, 0.0, 0.5, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClosed(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}
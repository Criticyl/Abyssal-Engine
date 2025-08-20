#include "abyssalpch.h"
#include "Application.h"

#include "Abyssal/Log.h"

#include <glad/glad.h>

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

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClosed));

        for (auto iter = m_LayerStack.end(); iter != m_LayerStack.begin(); )
        {
            (*--iter)->OnEvent(event);
            if (event.Handled())
                break;
        }
    }

    void Application::Run() 
    {
        

        while (m_Running)
        {
            glClearColor(1.0, 0.0, 0.5, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClosed(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}
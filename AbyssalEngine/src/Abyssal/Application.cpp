#include "abyssalpch.h"
#include "Application.h"

#include "Abyssal/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Abyssal {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        ABYSSAL_CORE_ASSERT(!s_Instance, "Application already exists!")
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(ABYSSAL_BIND_EVENT_FUNC(Application::OnEvent));
    }

    Application::~Application()
    {

    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(ABYSSAL_BIND_EVENT_FUNC(Application::OnWindowClosed));

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

            ABYSSAL_CORE_TRACE("{0}, {1}", Input::GetMouseX(), Input::GetMouseY());

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClosed(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}
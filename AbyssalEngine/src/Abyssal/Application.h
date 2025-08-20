#pragma once

#include "Core.h"
#include "Window.h"
#include "Abyssal/LayerStack.h"
#include "Abyssal/Events/Event.h"
#include "Abyssal/Events/ApplicationEvent.h"

namespace Abyssal {
    class ABYSSAL_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
    private:
        bool OnWindowClosed(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    };

    //Defined in client
    Application* CreateApplication();
}

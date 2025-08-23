#pragma once

#include "Core.h"
#include "Window.h"
#include "Abyssal/LayerStack.h"
#include "Abyssal/Events/Event.h"
#include "Abyssal/Events/ApplicationEvent.h"

#include "Abyssal/ImGui/ImGuiLayer.h"

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

        inline static Application& Get() {
            return *s_Instance;
        }

        inline Window& GetWindow() { return *m_Window; }
    private:
        bool OnWindowClosed(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;
    private:
        static Application* s_Instance;
    };

    //Defined in client
    Application* CreateApplication();
}

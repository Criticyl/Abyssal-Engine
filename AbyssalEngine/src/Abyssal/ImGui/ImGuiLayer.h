#pragma once

#include "Abyssal/Layer.h"
#include "Abyssal/Events/MouseEvent.h"
#include "Abyssal/Events/KeyEvent.h"
#include "Abyssal/Events/ApplicationEvent.h"

namespace Abyssal {

    class ABYSSAL_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();

    private:
        float m_Time = 0.0f;
    };
}
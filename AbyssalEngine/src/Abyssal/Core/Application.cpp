#include "abyssalpch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Abyssal/Input/Input.h"

namespace Abyssal {

    Application* Application::s_Instance = nullptr;

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:     return GL_FLOAT;
            case ShaderDataType::Float2:    return GL_FLOAT;
            case ShaderDataType::Float3:    return GL_FLOAT;
            case ShaderDataType::Float4:    return GL_FLOAT;
            case ShaderDataType::Mat3:      return GL_FLOAT;
            case ShaderDataType::Mat4:      return GL_FLOAT;
            case ShaderDataType::Int:       return GL_INT;
            case ShaderDataType::Int2:      return GL_INT;
            case ShaderDataType::Int3:      return GL_INT;
            case ShaderDataType::Int4:      return GL_INT;
            case ShaderDataType::Bool:      return GL_BOOL;
        }

        ABYSSAL_CORE_ASSERT(false, "Unknown Shader Data type!")
        return 0;
    }

    Application::Application()
    {
        ABYSSAL_CORE_ASSERT(!s_Instance, "Application already exists!")
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(ABYSSAL_BIND_EVENT_FUNC(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);
        
        float vertices[6 * 3] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        };

        std::uint32_t indices[3] = {
            0, 1, 2
        };

        m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        m_VertexBuffer->Bind();

        {
            BufferLayout layout = {
                {"a_Pos", ShaderDataType::Float3},
                {"a_Col", ShaderDataType::Float3}
            };

            m_VertexBuffer->SetLayout(layout);
        }

        std::uint32_t index = 0;
        const auto& layout = m_VertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized, layout.GetStride(), (const void*)element.Offset);
            index++;
        }

        m_IndexBuffer = IndexBuffer::Create(indices, 3);
        m_IndexBuffer->Bind();

        std::string vertexSource = R"(
            #version 330 core
            
            layout (location = 0) in vec3 a_Pos;
            layout (location = 1) in vec3 a_Col;
            out vec3 col;
            void main()
            {
                gl_Position = vec4(a_Pos, 1.0);
                col = a_Col;
            }
        )";

        std::string fragmentSource = R"(
            #version 330 core
            
            in vec3 col;
            out vec4 FragColor;
            void main()
            {
                FragColor = vec4(col, 1.0);
            }
        )";

        m_Shader.reset(new Shader(vertexSource, fragmentSource));
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
            glClearColor(0.09f, 0.09f, 0.11f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClosed(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}
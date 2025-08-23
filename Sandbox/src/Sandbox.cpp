#include <Abyssal.h>

class ExampleLayer : public Abyssal::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{ }

	void OnUpdate() override
	{
		ABYSSAL_INFO("ExampleLayer::Update");
		if (Abyssal::Input::IsKeyPressed(static_cast<int>(Abyssal::Key::TAB)))
		{
			ABYSSAL_INFO("TAB key is pressed!");
		}
	}

	void OnEvent(Abyssal::Event& event) override
	{
		ABYSSAL_TRACE("{0}", event.ToString());
	}

};

class Sandbox : public Abyssal::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Abyssal::ImGuiLayer());
	}

	~Sandbox()
	{

	}

};

Abyssal::Application* Abyssal::CreateApplication()
{
	return new Sandbox();
}
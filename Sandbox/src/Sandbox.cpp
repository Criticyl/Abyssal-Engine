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
	}

	~Sandbox()
	{

	}

};

Abyssal::Application* Abyssal::CreateApplication()
{
	return new Sandbox();
}
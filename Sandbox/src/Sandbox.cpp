#include <Abyssal.h>

#include "imgui/imgui.h"

class ExampleLayer : public Abyssal::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{ }

	void OnUpdate() override
	{
		if (Abyssal::Input::IsKeyPressed(static_cast<int>(Abyssal::Key::TAB)))
		{
			ABYSSAL_INFO("TAB key is pressed!");
		}
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Abyssal::Event& event) override
	{

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
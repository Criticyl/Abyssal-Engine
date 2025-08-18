#include <Abyssal.h>

class Sandbox : public Abyssal::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

Abyssal::Application* Abyssal::CreateApplication()
{
	return new Sandbox();
}
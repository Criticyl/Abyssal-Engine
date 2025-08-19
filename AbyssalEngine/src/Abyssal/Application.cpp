#include "Application.h"

#include "Abyssal/Events/ApplicationEvent.h"
#include "Abyssal/Log.h"

namespace Abyssal {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run() 
	{
		WindowResizeEvent e(1280, 720);
		ABYSSAL_TRACE(e.ToString());

		while (true);
	}
}
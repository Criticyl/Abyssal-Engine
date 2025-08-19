#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Abyssal {
	class ABYSSAL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	};

	//Defined in client
	Application* CreateApplication();
}

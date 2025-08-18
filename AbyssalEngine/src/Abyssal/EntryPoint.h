#pragma once

#ifdef ABYSSAL_PLATFORM_WINDOWS

extern Abyssal::Application* Abyssal::CreateApplication();
	
int main(int argc, char** argv)
{
	auto app = Abyssal::CreateApplication();
	app->Run();

	delete app;
}

#endif
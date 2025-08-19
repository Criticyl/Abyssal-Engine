#pragma once

#ifdef ABYSSAL_PLATFORM_WINDOWS
	#ifdef ABYSSAL_BUILD_DLL
		#define ABYSSAL_API __declspec(dllexport)
	#else
		#define ABYSSAL_API __declspec(dllimport)
	#endif
#else
	#error Abyssal Engine only supports Windows!
#endif

#define BIT(x) (1 << x)
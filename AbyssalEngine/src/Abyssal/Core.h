#pragma once

#ifdef ABYSSAL_PLATFORM_WINDOWS
#if ABYSSAL_DYNAMIC_LINK
    #ifdef ABYSSAL_BUILD_DLL
        #define ABYSSAL_API __declspec(dllexport)
    #else
        #define ABYSSAL_API __declspec(dllimport)
    #endif
#else
    #define ABYSSAL_API
#endif
#else
    #error Abyssal Engine only supports Windows!
#endif

#ifdef ABYSSAL_ENABLE_ASSERTS
    #define ABYSSAL_ASSERT(x, ...) { if(!x) { ABYSSAL_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define ABYSSAL_CORE_ASSERT(x, ...) { if(!x) { ABYSSAL_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define ABYSSAL_ASSERT(x, ...)
    #define ABYSSAL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define ABYSSAL_BIND_EVENT_FUNC(func) std::bind(&func, this, std::placeholders::_1)
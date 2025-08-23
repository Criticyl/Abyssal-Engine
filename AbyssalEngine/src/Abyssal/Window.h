#pragma once

#include "abyssalpch.h"

#include "Abyssal/Core.h"
#include "Abyssal/Events/Event.h"

namespace Abyssal {

    struct WindowSettings
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowSettings(const std::string& title = "Abyssal Engine", 
                       unsigned int width = 1280, 
                       unsigned int height = 720)
            : Title(title), Width(width), Height(height) { }
    };

    //Window Interface for desktop systems.
    class ABYSSAL_API Window
    {
    public:
        using EventCallbackFunc = std::function<void(Event&)>;

        virtual ~Window() {}

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFunc& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Window* Create(const WindowSettings& settings = WindowSettings());
    };
}
#pragma once

#include "Events/Event.hpp"

#include "ARcane/Core.hpp"
#include <glad/glad.h>  //! Must be included before GLFW
#include <GLFW/glfw3.h>

namespace ARcane {

// Window properties struct to be stored as user pointer in GLFW window
struct WindowUserStruct {
    using EventCallbackFn = std::function<void(Event&)>;

    uint32_t Width, Height;
    const char* Title;
    EventCallbackFn EventCallback = nullptr;

    WindowUserStruct(uint32_t width, uint32_t height, const char* title)
        : Width(width), Height(height), Title(title) {}
};

class Window {
   public:
    using EventCallbackFn = std::function<void(Event&)>;

    Window(uint32_t width, uint32_t height, const char* title);
    ~Window();

    void Update();

    inline uint32_t GetWidth() const { return m_UserStruct.Width; }
    inline uint32_t GetHeight() const { return m_UserStruct.Height; }

    inline void SetEventCallback(const EventCallbackFn& callback) {
        m_UserStruct.EventCallback = callback;
    }

    inline void* GetNativeWindow() const { return m_Window; }

   private:
    GLFWwindow* m_Window = nullptr;
    WindowUserStruct m_UserStruct;

    void SetEventCallbacks();
};

}  // namespace ARcane

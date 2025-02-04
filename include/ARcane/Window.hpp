#pragma once

#include "ARcane/Core.hpp"
#include <glad/glad.h>  //! Must be included before GLFW
#include <GLFW/glfw3.h>

namespace ARcane {

struct WindowProperties {
    uint32_t Width, Height;
    const char* Title;
};

class Window {
   public:
    Window(uint32_t width, uint32_t height, const char* title);
    ~Window();

    void Update();

   private:
    GLFWwindow* m_Window = nullptr;
    WindowProperties m_Props;

    void SetEventCallbacks();
};

}  // namespace ARcane

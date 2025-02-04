#pragma once

#include "ARcane/Core.hpp"
#include <glad/glad.h>  //! Must be included before GLFW
#include <GLFW/glfw3.h>

namespace ARcane {

class Window {
   public:
    Window(uint32_t width, uint32_t height, const char* title);
    ~Window();

    void Update();

   private:
    GLFWwindow* m_Window = nullptr;
    uint32_t m_Width, m_Height;
    const char* m_Title;
};

}  // namespace ARcane

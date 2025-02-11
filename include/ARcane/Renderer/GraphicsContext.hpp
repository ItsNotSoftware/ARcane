#pragma once

#include "ARcane/Core.hpp"

struct GLFWwindow;

namespace ARcane {

class GraphicsContext {
   public:
    GraphicsContext(GLFWwindow* windowHandle);

    void Init();
    void SwapBuffers();

   private:
    GLFWwindow* m_WindowHandle;
};

};  // namespace ARcane
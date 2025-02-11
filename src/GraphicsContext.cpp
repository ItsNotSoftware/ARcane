#include "ARcane/Renderer/GraphicsContext.hpp"

#include <glad/glad.h>  //! Include glad before GLFW
#include <GLFW/glfw3.h>

namespace ARcane {

GraphicsContext::GraphicsContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
    ARC_CORE_ASSERT(windowHandle, "Window handle is null!");
}

void GraphicsContext::Init() {
    glfwMakeContextCurrent(m_WindowHandle);

    ARC_CORE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress),
                    "Failed to initialize GLAD!");
}

void GraphicsContext::SwapBuffers() {
    glfwSwapBuffers(m_WindowHandle);

    // TODO: Move this to a renderer class
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

};  // namespace ARcane
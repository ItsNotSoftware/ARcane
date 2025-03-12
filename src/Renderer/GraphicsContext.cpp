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

    // Log openGL info
    ARC_CORE_INFO("OpenGL Info:");
    ARC_CORE_INFO("\tVendor: {0}", (const char*)glGetString(GL_VENDOR));
    ARC_CORE_INFO("\tRenderer: {0}", (const char*)glGetString(GL_RENDERER));
    ARC_CORE_INFO("\tVersion: {0}", (const char*)glGetString(GL_VERSION));
    std::cout << std::endl;
}

void GraphicsContext::SwapBuffers() { glfwSwapBuffers(m_WindowHandle); }

};  // namespace ARcane
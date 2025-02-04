#include "ARcane/Window.hpp"

namespace ARcane {

Window::Window(uint32_t width, uint32_t height, const char* title)
    : m_Width(width), m_Height(height), m_Title(title) {
    if (!glfwInit()) {
        ARC_CORE_ERROR("Failed to initialize GLFW!");
        std::terminate();
    }

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
    if (!m_Window) {
        ARC_CORE_ERROR("Failed to create window!");
        glfwTerminate();
        std::terminate();
    }

    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        ARC_CORE_ERROR("Failed to initialize GLAD!");
        glfwDestroyWindow(m_Window);
        glfwTerminate();
        std::terminate();
    }

    ARC_CORE_INFO("OpenGL Info:");
    ARC_CORE_INFO("\tVendor: {0}", (const char*)glGetString(GL_VENDOR));
    ARC_CORE_INFO("\tRenderer: {0}", (const char*)glGetString(GL_RENDERER));
    ARC_CORE_INFO("\tVersion: {0}", (const char*)glGetString(GL_VERSION));
    std::cout << std::endl;
}

Window::~Window() {
    if (m_Window) {
        glfwDestroyWindow(m_Window);
    }
    glfwTerminate();  //? Move this to Application destructor?
}

void Window::Update() {
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

}  // namespace ARcane

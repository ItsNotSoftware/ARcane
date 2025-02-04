#include "ARcane/Window.hpp"

namespace ARcane {

static void GLFWErrorCallback(int error, const char* description) {
    ARC_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

Window::Window(uint32_t width, uint32_t height, const char* title) {
    m_Props.Width = width;
    m_Props.Height = height;
    m_Props.Title = title;

    if (!glfwInit()) {
        ARC_CORE_ERROR("Failed to initialize GLFW!");
        std::terminate();
    }

    m_Window = glfwCreateWindow(m_Props.Width, m_Props.Height, m_Props.Title, nullptr, nullptr);
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

    glfwSetWindowUserPointer(m_Window, &m_Props);  // Set window user pointer
    SetEventCallbacks();
}

void Window::SetEventCallbacks() {
    // TODO: bind to user-defined callbacks

    glfwSetErrorCallback(GLFWErrorCallback);

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);
        props.Width = width;
        props.Height = height;
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow*) { ARC_CORE_INFO("Window close event"); });

    glfwSetKeyCallback(m_Window, [](GLFWwindow*, int key, int, int action, int) {
        switch (action) {
            case GLFW_PRESS:
                ARC_CORE_INFO("Key pressed: {0}", key);
                break;
            case GLFW_RELEASE:
                ARC_CORE_INFO("Key released: {0}", key);
                break;
            case GLFW_REPEAT:
                ARC_CORE_INFO("Key repeated: {0}", key);
                break;
        }
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow*, int button, int action, int) {
        switch (action) {
            case GLFW_PRESS:
                ARC_CORE_INFO("Mouse button pressed: {0}", button);
                break;
            case GLFW_RELEASE:
                ARC_CORE_INFO("Mouse button released: {0}", button);
                break;
        }
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow*, double xpos, double ypos) {
        ARC_CORE_INFO("Mouse position: ({0}, {1})", xpos, ypos);
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow*, double xoffset, double yoffset) {
        ARC_CORE_INFO("Mouse scroll: ({0}, {1})", xoffset, yoffset);
    });
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

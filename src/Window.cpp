#include "ARcane/Window.hpp"

#include "ARcane/Events/ApplicationEvent.hpp"
#include "ARcane/Events/KeyEvent.hpp"
#include "ARcane/Events/MouseEvent.hpp"

namespace ARcane {

static void GLFWErrorCallback(int error, const char* description) {
    ARC_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

Window::Window(uint32_t width, uint32_t height, const char* title)
    : m_UserStruct(width, height, title) {
    if (!glfwInit()) {
        ARC_CORE_ERROR("Failed to initialize GLFW!");
        std::terminate();
    }

    m_Window = glfwCreateWindow(m_UserStruct.Width, m_UserStruct.Height, m_UserStruct.Title,
                                nullptr, nullptr);
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

    glfwSetWindowUserPointer(m_Window, &m_UserStruct);  // Set window user pointer
    SetEventCallbacks();
}

void Window::SetEventCallbacks() {
    glfwSetErrorCallback(GLFWErrorCallback);

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        WindowUserStruct& usrStruct = *(WindowUserStruct*)glfwGetWindowUserPointer(window);
        usrStruct.Width = width;
        usrStruct.Height = height;

        WindowResizeEvent event(width, height);
        usrStruct.EventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        WindowUserStruct& usrStruct = *(WindowUserStruct*)glfwGetWindowUserPointer(window);

        WindowCloseEvent event;
        usrStruct.EventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int, int action, int) {
        WindowUserStruct& usrStruct = *(WindowUserStruct*)glfwGetWindowUserPointer(window);

        switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent event(key, 0);
                usrStruct.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent event(key);
                usrStruct.EventCallback(event);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent event(key, 1);
                usrStruct.EventCallback(event);
                break;
            }
        }
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int) {
        WindowUserStruct& usrStruct = *(WindowUserStruct*)glfwGetWindowUserPointer(window);

        switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(button);
                usrStruct.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(button);
                usrStruct.EventCallback(event);
                break;
            }
        }
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
        WindowUserStruct& usrStruct = *(WindowUserStruct*)glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float)xpos, (float)ypos);
        usrStruct.EventCallback(event);
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
        WindowUserStruct& usrStruct = *(WindowUserStruct*)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)xoffset, (float)yoffset);
        usrStruct.EventCallback(event);
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

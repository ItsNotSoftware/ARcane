#include "ARcane/Core/Window.hpp"

#include "ARcane/Core/Events/ApplicationEvent.hpp"
#include "ARcane/Core/Events/KeyEvent.hpp"
#include "ARcane/Core/Events/MouseEvent.hpp"

#include <GLFW/glfw3.h>

namespace ARcane {

static void GLFWErrorCallback(int error, const char* description) {
    ARC_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

Window::Window(uint32_t width, uint32_t height, const char* title)
    : m_UserStruct(width, height, title) {
    // Initialize GLFW
    int glfwInitialized = glfwInit();
    ARC_CORE_ASSERT(glfwInitialized, "Failed to initialize GLFW!");

    // Create the window
    m_Window = glfwCreateWindow(m_UserStruct.Width, m_UserStruct.Height, m_UserStruct.Title,
                                nullptr, nullptr);

    // Disable vsync
    // glfwSwapInterval(0);

    m_Context = new GraphicsContext(m_Window);
    m_Context->Init();  //? Maybe move to constructor?

    glfwSetWindowUserPointer(m_Window, &m_UserStruct);  // Set window user pointer
    SetEventCallbacks();
}

void Window::SetEventCallbacks() {
    glfwSetErrorCallback(GLFWErrorCallback);  // Set error callback

    // Window resize callback
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        WindowUserStruct& usrStruct = *(WindowUserStruct*)glfwGetWindowUserPointer(window);
        usrStruct.Width = width;
        usrStruct.Height = height;

        WindowResizeEvent event(width, height);
        usrStruct.EventCallback(event);
    });

    // Window close callback
    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        WindowUserStruct& usrStruct = *(WindowUserStruct*)glfwGetWindowUserPointer(window);

        WindowCloseEvent event;
        usrStruct.EventCallback(event);
    });

    // Key press callback
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

    glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
        WindowUserStruct& usrStruct = *(WindowUserStruct*)glfwGetWindowUserPointer(window);

        KeyTypedEvent event(keycode);
        usrStruct.EventCallback(event);
    });

    // Mouse button press callback
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

    // Mouse move callback
    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
        WindowUserStruct& usrStruct = *(WindowUserStruct*)glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float)xpos, (float)ypos);
        usrStruct.EventCallback(event);
    });

    // Mouse scroll callback
    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
        WindowUserStruct& usrStruct = *(WindowUserStruct*)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)xoffset, (float)yoffset);
        usrStruct.EventCallback(event);
    });
}

Window::~Window() {
    // Destroy the window and terminate GLFW
    if (m_Window) {
        glfwDestroyWindow(m_Window);
    }
}

void Window::Update() {
    glfwPollEvents();
    m_Context->SwapBuffers();
}

}  // namespace ARcane

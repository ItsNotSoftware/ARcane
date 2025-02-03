#include "ARcane/window.hpp"

namespace ARcane {

Window::Window(uint32_t width, uint32_t height) : window(nullptr), width(width), height(height) {
    if (!glfwInit()) {
        std::cerr << "[ARcane Error]: Failed to initialize GLFW\n";
        std::terminate();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, "ARcane", nullptr, nullptr);
    if (!window) {
        std::cerr << "[ARcane Error]: Failed to create GLFW window\n";
        glfwTerminate();
        std::terminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    glfwSetKeyCallback(window, keyCallback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "[ARcane Error]: Failed to initialize GLAD\n";
        glfwTerminate();
        std::terminate();
    }

    glEnable(GL_DEPTH_TEST);
}

void Window::setBackgroundColor(float r, float g, float b, float a) {
    background[0] = r;
    background[1] = g;
    background[2] = b;
    background[3] = a;

    // check values range and producce warning if out of range
    if (r < 0.0f || r > 1.0f || g < 0.0f || g > 1.0f || b < 0.0f || b > 1.0f || a < 0.0f ||
        a > 1.0f) {
        std::cerr
            << "[ARcane Warning]: Background color values should be in the range [0.0, 1.0]\n";
    }
}

Window::~Window() { glfwTerminate(); }

bool Window::active() const { return !glfwWindowShouldClose(window); }

void Window::renderFrame() {
    // Set a red clear color.
    glClearColor(background[0], background[1], background[2], background[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Swap the buffers and poll events.
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::keyCallback(GLFWwindow* window, int key, int /*scancode*/, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
}

}  // namespace ARcane

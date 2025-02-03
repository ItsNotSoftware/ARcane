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

Window::~Window() { glfwTerminate(); }

bool Window::active() const { return !glfwWindowShouldClose(window); }

void Window::renderFrame() {
    // Set a red clear color.
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Swap the buffers and poll events.
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::framebufferResizeCallback(GLFWwindow* /*window*/, int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::keyCallback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
}

}  // namespace ARcane

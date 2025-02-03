#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>

namespace ARcane {

/**
 * GLFW window with an OpenGL context.
 */
class Window {
   public:
    /**
     * Constructs a window with given dimensions.
     *
     * @param width Window width.
     * @param height Window height.
     */
    Window(uint32_t width, uint32_t height);

    /**
     * Destructs the window and cleans up resources.
     */
    ~Window();

    /**
     * Checks if the window is still active.
     *
     * @return true if the window is active, false otherwise.
     */
    bool active() const;

    /**
     * Renders a frame: clears the screen, swaps buffers, and polls events.
     */
    void renderFrame();

    /**
     * Sets the background color.
     *
     * @param r Red component in [0.0, 1.0].
     * @param g Green component in [0.0, 1.0].
     * @param b Blue component in [0.0, 1.0].
     * @param a Alpha component in [0.0, 1.0].
     */
    void setBackgroundColor(float r, float g, float b, float a);

   private:
    /**
     * Adjusts the viewport when the framebuffer is resized.
     *
     * @param window Pointer to the GLFW window.
     * @param width New width.
     * @param height New height.
     */
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    /**
     * Handles key events (e.g., closes window on Escape key press).
     *
     * @param window Pointer to the GLFW window.
     * @param key The key code.
     * @param scancode The system-specific scancode.
     * @param action The action (press, release, repeat).
     * @param mods Modifier keys.
     */
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    GLFWwindow* window;                          // Pointer to the GLFW window.
    uint32_t width;                              // Window width.
    uint32_t height;                             // Window height.
    float background[4] = {0.5, 0.5, 0.5, 1.0};  // Clear color red component.
};

}  // namespace ARcane

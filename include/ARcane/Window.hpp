#pragma once

#include "Events/Event.hpp"

#include "ARcane/Core.hpp"
#include <glad/glad.h>  //! Must be included before GLFW
#include <GLFW/glfw3.h>

namespace ARcane {

/**
 * @struct WindowUserStruct
 * @brief Stores window properties and an event callback.
 *
 * This struct is used as the user pointer in GLFW to hold window-related data.
 * Note: Not to be used outside of the Window class.
 */
struct WindowUserStruct {
    using EventCallbackFn = std::function<void(Event&)>;

    uint32_t Width, Height;
    const char* Title;
    EventCallbackFn EventCallback = nullptr;

    WindowUserStruct(uint32_t width, uint32_t height, const char* title)
        : Width(width), Height(height), Title(title) {}
};

/**
 * @class Window
 * @brief Internal class for window management.
 *
 * This class should **not** be instantiated by users.
 * The `App` class handles window creation and management.
 */
class Window {
   public:
    using EventCallbackFn = std::function<void(Event&)>;

    /**
     * @brief Creates a window with the specified dimensions and title.
     * @param width Window width in pixels.
     * @param height Window height in pixels.
     * @param title Window title.
     */
    Window(uint32_t width, uint32_t height, const char* title);

    /**
     * @brief Destroys the window and cleans up resources.
     */
    ~Window();

    /**
     * @brief Updates the window (polls events, swaps buffers).
     */
    void Update();

    /**
     * @brief Gets the window width.
     * @return The width in pixels.
     */
    inline uint32_t GetWidth() const { return m_UserStruct.Width; }

    /**
     * @brief Gets the window height.
     * @return The height in pixels.
     */
    inline uint32_t GetHeight() const { return m_UserStruct.Height; }

    /**
     * @brief Sets the event callback function for handling window events.
     * @param callback Function to be called when an event occurs.
     */
    inline void SetEventCallback(const EventCallbackFn& callback) {
        m_UserStruct.EventCallback = callback;
    }

    /**
     * @brief Retrieves the native GLFW window handle.
     * @return A pointer to the native GLFWwindow object.
     */
    inline void* GetNativeWindow() const { return m_Window; }

   private:
    GLFWwindow* m_Window = nullptr;  // Native window handle
    WindowUserStruct m_UserStruct;   // Stores window properties and callbacks

    /**
     * @brief Sets GLFW event callbacks for handling input and window events.
     */
    void SetEventCallbacks();
};

}  // namespace ARcane

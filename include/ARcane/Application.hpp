#pragma once

#include "Window.hpp"
#include "ARcane/Core.hpp"
#include "ARcane/Window.hpp"
#include "ARcane/Input.hpp"
#include "ARcane/Events/Event.hpp"
#include "ARcane/Events/ApplicationEvent.hpp"
#include "ARcane/Events/KeyEvent.hpp"
#include "ARcane/Layers/LayerStack.hpp"
#include "ARcane/Layers/Layer.hpp"
#include "ARcane/Layers/ImGuiLayer.hpp"

namespace ARcane {

/**
 * @class Application (Singleton)
 * @brief Manages the core runtime of the engine.
 *
 * This class is responsible for initializing and running the engine, handling events,
 * and managing layers. It should be inherited by the client application.
 */
class Application {
   public:
    /**
     * @brief Constructs the application.
     */
    Application();

    /**
     * @brief Destroys the application and cleans up resources.
     */
    virtual ~Application();

    /**
     * @brief Starts the main application loop.
     *
     * Runs until a close event is received.
     */
    void Run();

    /**
     * @brief Handles incoming events.
     * @param e The event to process.
     */
    void OnEvent(Event& e);

    /**
     * @brief Pushes a new layer onto the application.
     * @param layer Pointer to the layer to be added.
     */
    void PushLayer(Layer* layer);

    /**
     * @brief Pushes an overlay onto the application.
     * @param overlay Pointer to the overlay to be added.
     */
    void PushOverlay(Layer* overlay);

    /**
     * @brief Gets the reference to application instance.
     * @return Reference to the application instance.
     */
    inline static Application& Get() { return *s_Instance; }

    /**
     * @brief Gets the reference application window.
     * @return Reference to the application window.
     */
    inline Window& GetWindow() { return *m_Window; }

   private:
    /**
     * @brief Handles window close events.
     * @param e The window close event.
     * @return True if the event is handled, false otherwise.
     */
    bool OnWindowClose(WindowCloseEvent& e);

    std::unique_ptr<Window> m_Window;    // Application window instance.
    ImGuiLayer* m_ImGuiLayer = nullptr;  // ImGui layer instance.
    bool m_Running = true;               // Indicates if the application is running.
    LayerStack m_LayerStack;             // Manages layers within the application.

    static Application* s_Instance;  // Pointer to the application instance (singleton).
};

/**
 * @brief Creates an instance of the application.
 *
 * This function must be defined in the client application.
 * @return A pointer to the created application instance.
 */
Application* CreateApplication();

}  // namespace ARcane

/*
    ============================
    *Example Usage:
    ============================

    class ExampleLayer : public ARcane::Layer {
    public:
        ...  // See Layer.hpp for more details
    };

    class Sandbox : public ARcane::Application {
    public:
        Sandbox() { PushLayer(new ExampleLayer()); }
        ~Sandbox() {}
    };

    ARcane::Application* ARcane::CreateApplication() { return new Sandbox(); }

*/
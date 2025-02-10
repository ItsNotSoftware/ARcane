#include "ARcane/Application.hpp"

namespace ARcane {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application::Application() {
    // Create the application window
    m_Window = std::make_unique<Window>(1280, 720, "ARcane Engine");

    // Bind event handling to this application instance
    m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
}

Application::~Application() {}

void Application::PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }

void Application::PushOverlay(Layer* overlay) { m_LayerStack.PushOverlay(overlay); }

void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);

    // Handle window close events
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

    // Pass the event to layers from top to bottom
    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
        (*--it)->OnEvent(e);
        if (e.Handled) {
            break;
        }
    }
}

void Application::Run() {
    while (m_Running) {
        // Clear the screen with a dark gray color
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Update all active layers
        for (auto layer : m_LayerStack) {
            layer->OnUpdate();
        }

        // Update the window (handle input, buffer swaps, etc.)
        m_Window->Update();
    }
}

bool Application::OnWindowClose(WindowCloseEvent&) {
    m_Running = false;  // Stop the application loop
    return true;
}

}  // namespace ARcane

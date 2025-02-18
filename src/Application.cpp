#include "ARcane/Application.hpp"

#include <GLFW/glfw3.h>

namespace ARcane {

Application* Application::s_Instance = nullptr;

Application::Application() {
    ARC_CORE_ASSERT(
        !s_Instance,
        "Creating multiple Application instances is not allowed. Use Application::Get() instead.");
    s_Instance = this;

    // Create the application window
    m_Window = std::make_unique<Window>(1800, 1200, "ARcane Engine");

    // Bind event handling to this application instance
    m_Window->SetEventCallback(ARC_BIND_EVENT_FN(Application::OnEvent));

    // Initialize ImGui
    m_ImGuiLayer = new ImGuiLayer;
    PushOverlay(m_ImGuiLayer);
}

Application::~Application() {}

void Application::PushLayer(Layer* layer) {
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer* overlay) {
    m_LayerStack.PushOverlay(overlay);
    overlay->OnAttach();
}

void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);

    // Handle window close events
    dispatcher.Dispatch<WindowCloseEvent>(ARC_BIND_EVENT_FN(Application::OnWindowClose));

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
        float time = static_cast<float>(glfwGetTime());
        Timestep timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;

        // Update all active layers
        for (auto layer : m_LayerStack) {
            layer->OnUpdate(timestep);
        }

        // Render ImGui elements
        m_ImGuiLayer->Begin();
        for (auto layer : m_LayerStack) {
            layer->OnImGuiRender();
        }
        m_ImGuiLayer->End();

        m_Window->Update();
    }
}

bool Application::OnWindowClose(WindowCloseEvent&) {
    m_Running = false;  // Stop the application loop
    return true;
}

}  // namespace ARcane

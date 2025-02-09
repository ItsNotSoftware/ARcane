#include "ARcane/Application.hpp"

namespace ARcane {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application::Application() {
    m_Window = std::make_unique<Window>(1280, 720, "ARcane Engine");
    m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
}

Application::~Application() {}

void Application::PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }

void Application::PushOverlay(Layer* overlay) { m_LayerStack.PushOverlay(overlay); }

void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

    // Iterate through layers from top to bottom and pass the event to each layer until handled
    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
        (*--it)->OnEvent(e);
        if (e.Handled) {
            break;
        }
    }
}

void Application::Run() {
    while (m_Running) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto layer : m_LayerStack) {
            layer->OnUpdate();
        }

        m_Window->Update();
    }
}

bool Application::OnWindowClose(WindowCloseEvent&) {
    m_Running = false;
    return true;
}

}  // namespace ARcane
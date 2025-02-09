#include "ARcane/Application.hpp"

namespace ARcane {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application::Application() {
    m_Window = std::make_unique<Window>(1280, 720, "ARcane Engine");
    m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
}

Application::~Application() {}

void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

    ARC_CORE_TRACE("{0}", e.ToString());
}

void Application::Run() {
    while (m_Running) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        m_Window->Update();
    }
}

bool Application::OnWindowClose(WindowCloseEvent&) {
    m_Running = false;
    return true;
}

}  // namespace ARcane
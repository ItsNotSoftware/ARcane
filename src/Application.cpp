#include "ARcane/Application.hpp"

namespace ARcane {

Application::Application() { m_Window = std::make_unique<Window>(1280, 720, "ARcane Engine"); }

Application::~Application() {}

void Application::Run() {
    while (m_Running) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        m_Window->Update();
    }
}

}  // namespace ARcane
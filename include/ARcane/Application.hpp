#pragma once

#include "Window.hpp"
#include "Events/Event.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"

namespace ARcane {

class Application {
   public:
    Application();
    virtual ~Application();

    void Run();
    void OnEvent(Event& e);

   private:
    std::unique_ptr<Window> m_Window;
    bool m_Running = true;

    bool OnWindowClose(WindowCloseEvent&);
};

Application* CreateApplication();

}  // namespace ARcane

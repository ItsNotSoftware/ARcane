#pragma once
#include "Window.hpp"

#include "Events/Event.hpp"

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
};

Application* CreateApplication();

}  // namespace ARcane

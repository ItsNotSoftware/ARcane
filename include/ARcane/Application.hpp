#pragma once
#include "Window.hpp"

namespace ARcane {

class Application {
   public:
    Application();
    virtual ~Application();

    void Run();

   private:
    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
};

Application* CreateApplication();

}  // namespace ARcane

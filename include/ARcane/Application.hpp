#pragma once

#include "Window.hpp"
#include "Events/Event.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "ARcane/LayerStack.hpp"

namespace ARcane {

class Application {
   public:
    Application();
    virtual ~Application();

    void Run();
    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);

   private:
    bool OnWindowClose(WindowCloseEvent&);

    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
    LayerStack m_LayerStack;
};

Application* CreateApplication();

}  // namespace ARcane

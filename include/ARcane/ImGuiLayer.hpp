#pragma once

#include "ARcane/Layer.hpp"
#include "ARcane/Events/Event.hpp"
#include "ARcane/Events/MouseEvent.hpp"
#include "ARcane/Events/KeyEvent.hpp"
#include "ARcane/Events/ApplicationEvent.hpp"

namespace ARcane {

class ImGuiLayer : public Layer {
   public:
    ImGuiLayer();
    ~ImGuiLayer();

    void OnAttach();
    void OnDetach();
    void OnUpdate();
    void OnEvent(Event& event);

   private:
    bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
    bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
    bool OnMouseMovedEvent(MouseMovedEvent& event);
    bool OnMouseScrolledEvent(MouseScrolledEvent& event);
    bool OnKeyPressedEvent(KeyPressedEvent& event);
    bool OnKeyReleasedEvent(KeyReleasedEvent& event);
    // void OnKeyTypedEvent(KeyTypedEvent& event);
    bool OnWindowResizeEvent(WindowResizeEvent& event);

    float m_Time = 0.0f;  // Time of the last frame
};

}  // namespace ARcane
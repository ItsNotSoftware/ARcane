#pragma once

#include "ARcane/Layers/Layer.hpp"
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
    void OnEvent(Event&);

   private:
    float m_Time = 0.0f;  // Time of the last frame
};

}  // namespace ARcane
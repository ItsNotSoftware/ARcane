#pragma once

#include "ARcane/Layer.hpp"

namespace ARcane {

class ImGuiLayer : public Layer {
   public:
    ImGuiLayer();
    ~ImGuiLayer();

    void OnAttach();
    void OnDetach();
    void OnUpdate();
    void OnEvent(Event& event);
};

}  // namespace ARcane
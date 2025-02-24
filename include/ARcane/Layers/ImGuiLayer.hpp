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

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnEvent(Event&) override;

    void Begin();
    void End();
};

}  // namespace ARcane
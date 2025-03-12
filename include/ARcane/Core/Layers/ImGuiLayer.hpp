#pragma once

#include "ARcane/Core/Layers/Layer.hpp"
#include "ARcane/Core/Events/Event.hpp"
#include "ARcane/Core/Events/MouseEvent.hpp"
#include "ARcane/Core/Events/KeyEvent.hpp"
#include "ARcane/Core/Events/ApplicationEvent.hpp"

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
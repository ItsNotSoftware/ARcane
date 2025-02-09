#pragma once

#include "ARcane/Core.hpp"
#include "ARcane/Events/Event.hpp"

namespace ARcane {

// Intended to be used as a base class for application layers
class Layer {
   public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate() {}
    virtual void OnEvent(Event& /*event*/) {}

    inline const std::string& GetName() const { return m_DebugName; }

   protected:
    std::string m_DebugName;
};

}  // namespace ARcane
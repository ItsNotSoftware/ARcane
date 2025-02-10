#pragma once

#include "ARcane/Core.hpp"
#include "ARcane/Events/Event.hpp"

namespace ARcane {

/**
 * @class Layer
 * @brief Base class for application layers.
 *
 * This class is intended to be used as a base class for creating application layers.
 * It provides virtual methods that can be overridden by derived classes to handle
 * attachment, detachment, updates, and events. Manage layers using the LayerStack class.
 */
class Layer {
   public:
    /**
     * @brief Constructs a Layer with an optional name.
     * @param name The name of the layer. Defaults to "Layer".
     */
    Layer(const std::string& name = "Layer");

    /**
     * @brief Virtual destructor.
     */
    virtual ~Layer();

    /**
     * @brief Called when the layer is attached.
     *
     * This method can be overridden by derived classes to perform actions when the layer is
     * attached.
     */
    virtual void OnAttach() {}

    /**
     * @brief Called when the layer is detached.
     *
     * This method can be overridden by derived classes to perform actions when the layer is
     * detached.
     */
    virtual void OnDetach() {}

    /**
     * @brief Called to update the layer.
     *
     * This method can be overridden by derived classes to perform actions during the update phase.
     */
    virtual void OnUpdate() {}

    /**
     * @brief Called when an event is received.
     * @param event The event to handle.
     *
     * This method can be overridden by derived classes to handle events.
     */
    virtual void OnEvent(Event& /*event*/) {}

    /**
     * @brief Gets the name of the layer.
     * @return The name of the layer.
     */
    inline const std::string& GetName() const { return m_DebugName; }

   protected:
    std::string m_DebugName;  // The name of the layer. DEBUG only!
};

}  // namespace ARcane

/*
    ============================
    Example Usage:
    ============================

    class ExampleLayer : public ARcane::Layer {
        public:
        ExampleLayer() : Layer("Example") {}
        ~ExampleLayer() {}

        void OnUpdate() override { ARC_INFO("ExampleLayer::Update"); }

        void OnEvent(ARcane::Event& event) override { ARC_TRACE("{0}", event.ToString()); }
    };
*/
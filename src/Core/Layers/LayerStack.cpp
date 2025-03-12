#include "ARcane/Core/Layers/LayerStack.hpp"

namespace ARcane {

LayerStack::LayerStack() {}

LayerStack::~LayerStack() {
    // Delete all layers to prevent memory leaks
    for (Layer* layer : m_Layers) {
        delete layer;
    }
}

void LayerStack::PushLayer(Layer* layer) {
    // Insert layer before overlays
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
    m_LayerInsertIndex++;
}

void LayerStack::PushOverlay(Layer* overlay) {
    // Overlays are always added at the end
    m_Layers.emplace_back(overlay);
}

void LayerStack::PopLayer(Layer* layer) {
    // Find and remove the layer from the stack
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end()) {
        m_Layers.erase(it);
        m_LayerInsertIndex--;  // Adjust the insert position
    }
}

void LayerStack::PopOverlay(Layer* overlay) {
    // Find and remove the overlay from the stack
    auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
    if (it != m_Layers.end()) {
        m_Layers.erase(it);
    }
}

}  // namespace ARcane

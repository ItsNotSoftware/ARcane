#include "ARcane/LayerStack.hpp"

namespace ARcane {

LayerStack::LayerStack() {
    m_LayerInsert = m_Layers.begin();  // Initialize layer insert position
}

LayerStack::~LayerStack() {
    // Delete all layers to prevent memory leaks
    for (Layer* layer : m_Layers) {
        delete layer;
    }
}

void LayerStack::PushLayer(Layer* layer) {
    // Insert layer before overlays
    m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
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
        m_LayerInsert--;  // Adjust the insert position
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

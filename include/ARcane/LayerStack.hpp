#pragma once

#include "ARcane/Core.hpp"
#include "ARcane/Layer.hpp"

namespace ARcane {

class LayerStack {
   public:
    LayerStack();
    ~LayerStack();

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    void PopLayer(Layer* layer);
    void PopOverlay(Layer* overlay);

    std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
    std::vector<Layer*>::iterator end() { return m_Layers.end(); }

   private:
    // Overlays are pushed to the back of the vector and layers are pushed in front of overlays
    // so that layers are rendered first
    std::vector<Layer*> m_Layers;
    std::vector<Layer*>::iterator m_LayerInsert;
};

}  // namespace ARcane

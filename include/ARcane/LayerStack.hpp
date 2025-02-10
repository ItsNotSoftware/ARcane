#pragma once

#include "ARcane/Core.hpp"
#include "ARcane/Layer.hpp"

namespace ARcane {

/**
 * @class LayerStack
 * @brief Manages the ordering and lifecycle of layers in the engine (see: Layer.hpp).
 *
 * Layers are stored in a vector where regular layers are inserted firts and then overlays.
 * Overlays are always drawn on top of other layers.
 */
class LayerStack {
   public:
    /**
     * @brief Constructs an empty LayerStack.
     */
    LayerStack();

    /**
     * @brief Destroys the LayerStack and properly cleans up layers.
     */
    ~LayerStack();

    /**
     * @brief Pushes a new layer onto the stack.
     *
     * Layers are inserted before overlays in the stack.
     *
     * @param layer A pointer to the Layer object to be added.
     */
    void PushLayer(Layer* layer);

    /**
     * @brief Pushes an overlay onto the stack.
     *
     * Overlays are inserted at the end of the stack and will always be drawn last.
     *
     * @param overlay A pointer to the Layer object to be added as an overlay.
     */
    void PushOverlay(Layer* overlay);

    /**
     * @brief Removes a layer from the stack.
     *
     * @param layer A pointer to the Layer object to be removed.
     */
    void PopLayer(Layer* layer);

    /**
     * @brief Removes an overlay from the stack.
     *
     * @param overlay A pointer to the Layer object to be removed.
     */
    void PopOverlay(Layer* overlay);

    /**
     * @brief Returns an iterator to the beginning of the layer stack.
     *
     * @return Iterator pointing to the first layer.
     */
    std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }

    /**
     * @brief Returns an iterator to the end of the layer stack.
     *
     * @return Iterator pointing past the last layer.
     */
    std::vector<Layer*>::iterator end() { return m_Layers.end(); }

   private:
    std::vector<Layer*> m_Layers;                 // Layers are stored in a vector
    std::vector<Layer*>::iterator m_LayerInsert;  // Iterator to the first overlay
};

}  // namespace ARcane

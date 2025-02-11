#pragma once

#include "ARcane/Layer.hpp"
#include "ARcane/Events/Event.hpp"
#include "ARcane/Events/MouseEvent.hpp"
#include "ARcane/Events/KeyEvent.hpp"
#include "ARcane/Events/ApplicationEvent.hpp"

namespace ARcane {

<<<<<<< HEAD
/**
 * @class ImGuiLayer
 * @brief A layer for integrating ImGui into the application.
 *
 * This class is responsible for setting up and managing the ImGui context
 * within the application. It provides methods for attaching, detaching,
 * updating, and handling events for the ImGui layer.
 */
class ImGuiLayer : public Layer {
   public:
    /**
     * @brief Constructs an ImGuiLayer object.
     */
    ImGuiLayer();

    /**
     * @brief Destructs the ImGuiLayer object.
     */
    ~ImGuiLayer();

    /**
     * @brief Attaches the ImGui layer to the application.
     *
     * This method is called when the layer is first attached to the application.
     * It sets up the necessary ImGui context and resources.
     */
    void OnAttach();

    /**
     * @brief Detaches the ImGui layer from the application.
     *
     * This method is called when the layer is detached from the application.
     * It cleans up the ImGui context and resources.
     */
    void OnDetach();

    /**
     * @brief Updates the ImGui layer.
     *
     * This method is called every frame to update the ImGui layer.
     * It handles rendering and updating ImGui elements.
     */
    void OnUpdate();

    /**
     * @brief Handles events for the ImGui layer.
     *
     * @param event The event to be handled.
     *
     * This method processes events and forwards them to ImGui for handling.
     */
    void OnEvent(Event& event);
=======
class ImGuiLayer : public Layer {
   public:
    ImGuiLayer();
    ~ImGuiLayer();

    void OnAttach();
    void OnDetach();
    void OnUpdate();
    void OnEvent(Event&);
>>>>>>> 4ca001afdc0a19a36da49aef12fc4fbc3ba23c36

   private:
    float m_Time = 0.0f;  // Time of the last frame
};

}  // namespace ARcane
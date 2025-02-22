#pragma once

#include "ARcane/Renderer/OrthographicCamera.hpp"
#include "ARcane/Timestep.hpp"

#include "ARcane/Events/ApplicationEvent.hpp"
#include "ARcane/Events/MouseEvent.hpp"

namespace ARcane {

class OrthographicCameraController {
   public:
    OrthographicCameraController(float aspectRatio, bool rotation = false);

    void OnUpdate(Timestep ts);
    void OnEvent(Event& e);

    inline OrthographicCamera& GetCamera() { return m_Camera; }
    inline const OrthographicCamera& GetCamera() const { return m_Camera; }

    inline float GetZoomLevel() const { return m_ZoomLevel; }
    inline void SetZoomLevel(float level) { m_ZoomLevel = level; }

   private:
    bool OnMouseScrolled(MouseScrolledEvent& e);
    bool OnWindowResized(WindowResizeEvent& e);

   private:
    float m_AspectRatio;
    float m_ZoomLevel = 1.0f;
    OrthographicCamera m_Camera;

    bool m_Rotation;

    glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
    float m_CameraRotation = 0.0f;  // In degrees, in the anti-clockwise direction
    float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
};

}  // namespace ARcane
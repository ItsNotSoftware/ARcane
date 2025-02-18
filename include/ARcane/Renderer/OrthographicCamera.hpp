#pragma once

#include "ARcane/Core.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ARcane {

class OrthographicCamera {
   public:
    OrthographicCamera(float left, float right, float bottom, float top);

    inline void SetPosition(const glm::vec3& position) {
        m_Position = position;
        RecalculateViewMatrix();
    }
    inline void SetRotation(float rotation) {
        m_Rotation = rotation;
        RecalculateViewMatrix();
    }
    inline void SetProjection(float left, float right, float bottom, float top) {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    inline float GetRotation() { return m_Rotation; }
    inline const glm::vec3& GetPosition() const { return m_Position; }
    inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
    inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
    inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

   private:
    void RecalculateViewMatrix();

    glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
    glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
    glm::mat4 m_ViewProjectionMatrix = glm::mat4(1.0f);

    glm::vec3 m_Position = glm::vec3(0.0f);
    float m_Rotation = 0.0f;
};

}  // namespace ARcane

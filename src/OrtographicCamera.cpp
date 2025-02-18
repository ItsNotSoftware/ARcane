#include "ARcane/Renderer/OrtographicCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace ARcane {

OrtographicCamera::OrtographicCamera(float left, float right, float bottom, float top)
    : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f) {
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrtographicCamera::RecalculateViewMatrix() {
    const auto I = glm::mat4(1.0f);
    glm::mat4 transform = glm::translate(I, m_Position) *
                          glm::rotate(I, glm::radians(m_Rotation), glm::vec3(0, 0, 1));

    m_ViewMatrix = glm::inverse(transform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

}  // namespace ARcane
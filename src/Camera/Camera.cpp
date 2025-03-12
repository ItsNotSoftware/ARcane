#include "ARcane/Camera/Camera.hpp"

namespace ARcane {

Camera::Camera(const glm::mat4& projection) : m_ProjectionMatrix(projection) {}

Camera::Camera(const float degFov, const float width, const float height, const float nearP,
               const float farP)
    : m_ProjectionMatrix(glm::perspectiveFov(glm::radians(degFov), width, height, farP, nearP)) {}

}  // namespace ARcane
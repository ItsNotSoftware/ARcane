#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace ARcane {

class Camera {
   public:
    Camera() = default;
    Camera(const glm::mat4& projection);
    Camera(const float degFov, const float width, const float height, const float nearP,
           const float farP);
    virtual ~Camera() = default;

    inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

    inline void SetProjectionMatrix(const glm::mat4 projection) { m_ProjectionMatrix = projection; }

    inline void SetPerspectiveProjectionMatrix(const float radFov, const float width,
                                               const float height, const float nearP,
                                               const float farP) {
        m_ProjectionMatrix = glm::perspectiveFov(radFov, width, height, farP, nearP);
    }

    inline void SetOrthoProjectionMatrix(const float width, const float height, const float nearP,
                                         const float farP) {
        m_ProjectionMatrix =
            glm::ortho(-width * 0.5f, width * 0.5f, -height * 0.5f, height * 0.5f, farP, nearP);
    }

    inline float GetExposure() const { return m_Exposure; }
    inline float& GetExposure() { return m_Exposure; }

   protected:
    float m_Exposure = 0.8f;

   private:
    glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
};

}  // namespace ARcane
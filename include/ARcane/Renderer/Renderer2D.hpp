#pragma once

#include "ARcane/Camera/Camera.hpp"
#include "ARcane/Renderer/Texture.hpp"
#include <opencv2/opencv.hpp>

namespace ARcane {

class Renderer2D {
    friend class Application;

   public:
    static void BeginScene(const Camera& camera);
    static void EndScene();
    static void Flush();

    static void DrawCVMat(const cv::Mat& frame, const glm::vec3& position, const glm::vec2& size);

    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
    static void DrawQuad(const glm::vec2& position, const glm::vec2& size,
                         const Ref<Texture2D>& texture, float tilingFactor = 1.0f,
                         const glm::vec4 tintColor = glm::vec4(1.0f));
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size,
                         const Ref<Texture2D>& texture, float tilingFactor = 1.0f,
                         const glm::vec4 tintColor = glm::vec4(1.0f));

    static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
                                const glm::vec4& color);
    static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
                                const glm::vec4& color);
    static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
                                const Ref<Texture2D>& texture, float tilingFactor = 1.0f,
                                const glm::vec4& tintColor = glm::vec4(1.0f));
    static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
                                const Ref<Texture2D>& texture, float tilingFactor = 1.0f,
                                const glm::vec4& tintColor = glm::vec4(1.0f));

   private:
    static void Init();
    static void Shutdown();

    static void FlushAndReset();
};

}  // namespace ARcane
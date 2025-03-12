#pragma once

#include "ARcane/Core/Core.hpp"
#include "ARcane/Renderer/VertexArray.hpp"
#include "ARcane/Camera/Camera.hpp"
#include "ARcane/Renderer/Shader.hpp"

#include <glm/glm.hpp>

namespace ARcane {

class Renderer {
    friend class Application;
    friend class Renderer2D;

   public:
    static void BeginScene(const Camera& camera);
    static void EndScene();
    static void Flush();

    static void SetClearColor(const glm::vec4& color);
    static void Clear();

    static void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
    static void DrawRotatedCube(const glm::vec3& position, const glm::vec3& size,
                                const glm::mat4& rotationMatrix, const glm::vec4& color);

   private:
    static void Init();
    static void Shutdown();
    static void OnWindowResize(uint32_t width, uint32_t height);

    static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0);
};

}  // namespace ARcane

#pragma once

#include "ARcane/Core/Core.hpp"
#include "ARcane/Renderer/VertexArray.hpp"
#include "ARcane/Camera/Camera.hpp"
#include "ARcane/Renderer/Shader.hpp"

#include <glm/glm.hpp>

namespace ARcane {

class Renderer {
   public:
    static void Init();
    static void OnWindowResize(uint32_t width, uint32_t height);

    static void BeginScene(Camera& camera);
    static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray,
                       const glm::mat4& transform = glm::mat4(1.0f));
    static void EndScene();

    static void SetClearColor(const glm::vec4& color);
    static void Clear();

    static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0);

   private:
    struct SceneData {
        glm::mat4 ViewProjectionMatrix;
    };

    static SceneData* s_SceneData;
};

}  // namespace ARcane

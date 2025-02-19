#pragma once

#include "ARcane/Core.hpp"
#include "ARcane/Renderer/VertexArray.hpp"
#include "ARcane/Renderer/OrthographicCamera.hpp"
#include "ARcane/Renderer/Shader.hpp"

#include <glm/glm.hpp>

namespace ARcane {

class Renderer {
   public:
    static void BeginScene(OrthographicCamera& camera);
    static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray,
                       const glm::mat4& transform = glm::mat4(1.0f));
    static void EndScene();

    static void SetClearColor(const glm::vec4& color);
    static void Clear();

   private:
    struct SceneData {
        glm::mat4 ViewProjectionMatrix;
    };

    static SceneData* s_SceneData;
};

}  // namespace ARcane

#pragma once

#include "ARcane/Core.hpp"
#include "ARcane/Renderer/VertexArray.hpp"
#include "ARcane/Renderer/OrtographicCamera.hpp"
#include "ARcane/Renderer/Shader.hpp"

#include <glm/glm.hpp>

namespace ARcane {

class Renderer {
   public:
    static void BeginScene(OrtographicCamera& camera);
    static void Submit(const std::shared_ptr<Shader>& shader,
                       const std::shared_ptr<VertexArray>& vertexArray);
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

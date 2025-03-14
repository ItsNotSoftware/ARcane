#include "ARcane/Renderer/Renderer.hpp"

#include <glad/glad.h>

namespace ARcane {

Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

void Renderer::OnWindowResize(uint32_t width, uint32_t height) { glViewport(0, 0, width, height); }

void Renderer::Init() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::BeginScene(Camera& camera) {
    s_SceneData->ViewProjectionMatrix = camera.GetProjectionMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray,
                      const glm::mat4& transform) {
    shader->Bind();
    shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
    shader->SetMat4("u_Transform", transform);

    vertexArray->Bind();
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT,
                   nullptr);
}

void Renderer::SetClearColor(const glm::vec4& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void Renderer::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) {
    uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

};  // namespace ARcane
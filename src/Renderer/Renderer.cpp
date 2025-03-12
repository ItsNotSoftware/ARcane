#include "ARcane/Renderer/Renderer.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace ARcane {

struct CubeVertex {
    glm::vec3 Position;
    glm::vec4 Color;
};

struct RendererData {
    Ref<VertexArray> CubeVertexArray;
    Ref<VertexBuffer> CubeVertexBuffer;
    Ref<IndexBuffer> CubeIndexBuffer;
    Ref<Shader> ColorShader;
    uint32_t CubeIndexCount = 0;
    CubeVertex* CubeVertexBufferBase = nullptr;
    CubeVertex* CubeVertexBufferPtr = nullptr;
};

static RendererData s_Data;

void Renderer::OnWindowResize(uint32_t width, uint32_t height) { glViewport(0, 0, width, height); }

void Renderer::Init() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    s_Data.CubeVertexArray = CreateRef<VertexArray>();
    s_Data.CubeVertexBuffer = CreateRef<VertexBuffer>(36 * sizeof(CubeVertex));
    s_Data.CubeVertexBuffer->SetLayout(
        {{ShaderDataType::Float3, "a_Position"}, {ShaderDataType::Float4, "a_Color"}});
    s_Data.CubeVertexArray->AddVertexBuffer(s_Data.CubeVertexBuffer);

    uint32_t cubeIndices[] = {
        0, 1, 2, 2, 3, 0,  // Front face
        4, 5, 6, 6, 7, 4,  // Back face
        0, 3, 7, 7, 4, 0,  // Left face
        1, 5, 6, 6, 2, 1,  // Right face
        3, 2, 6, 6, 7, 3,  // Top face
        0, 1, 5, 5, 4, 0   // Bottom face
    };
    s_Data.CubeIndexBuffer =
        CreateRef<IndexBuffer>(cubeIndices, sizeof(cubeIndices) / sizeof(uint32_t));
    s_Data.CubeVertexArray->SetIndexBuffer(s_Data.CubeIndexBuffer);

    s_Data.ColorShader = CreateRef<Shader>(ARC_ASSET_PATH("shaders/Texture3D.glsl"));
}

void Renderer::Shutdown() { delete[] s_Data.CubeVertexBufferBase; }

void Renderer::BeginScene(const Camera& camera) {}

void Renderer::EndScene() {
    uint32_t dataSize =
        (uint32_t)((uint8_t*)s_Data.CubeVertexBufferPtr - (uint8_t*)s_Data.CubeVertexBufferBase);
    s_Data.CubeVertexBuffer->SetData(s_Data.CubeVertexBufferBase, dataSize);
    Flush();
}

void Renderer::DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color) {
    glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), size);
    for (int i = 0; i < 36; i++) {
        s_Data.CubeVertexBufferPtr->Position =
            transform * glm::vec4(s_Data.CubeVertexBufferBase[i].Position, 1.0f);
        s_Data.CubeVertexBufferPtr->Color = color;
        s_Data.CubeVertexBufferPtr++;
    }
    s_Data.CubeIndexCount += 36;
}

void Renderer::DrawRotatedCube(const glm::vec3& position, const glm::vec3& size,
                               const glm::mat4& rotationMatrix, const glm::vec4& color) {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * rotationMatrix *
                          glm::scale(glm::mat4(1.0f), size);
    for (int i = 0; i < 36; i++) {
        s_Data.CubeVertexBufferPtr->Position =
            transform * glm::vec4(s_Data.CubeVertexBufferBase[i].Position, 1.0f);
        s_Data.CubeVertexBufferPtr->Color = color;
        s_Data.CubeVertexBufferPtr++;
    }
    s_Data.CubeIndexCount += 36;
}

void Renderer::Flush() { Renderer::DrawIndexed(s_Data.CubeVertexArray, s_Data.CubeIndexCount); }

void Renderer::SetClearColor(const glm::vec4& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void Renderer::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) {
    uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

};  // namespace ARcane
#include "ARcane/Renderer/Renderer2D.hpp"

#include "ARcane/Renderer/VertexArray.hpp"
#include "ARcane/Renderer/Shader.hpp"

namespace ARcane {

struct Renderer2DStorage {
    Ref<VertexArray> QuadVertexArray;
    Ref<Shader> FlatColorShader;
};

static Renderer2DStorage* s_Data;

void Renderer2D::Init() {
    s_Data = new Renderer2DStorage();
    s_Data->QuadVertexArray = std::make_shared<VertexArray>();

    float vertices[4 * 5] = {
        -0.5f, -0.5f, 0.0f,  //
        0.5f,  -0.5f, 0.0f,  //
        0.5f,  0.5f,  0.0f,  //
        -0.5f, 0.5f,  0.0f,  //
    };

    Ref<VertexBuffer> squareVB = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    squareVB->SetLayout({
        {ShaderDataType::Float3, "a_Position"},
    });
    s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

    uint32_t indices[6] = {0, 1, 2, 2, 3, 0};

    Ref<IndexBuffer> squareIB =
        std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));

    s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

    s_Data->FlatColorShader = std::make_shared<Shader>("../assets/shaders/FlatColor.glsl");
}

void Renderer2D::Shutdown() { delete s_Data; }

void Renderer2D::BeginScene(const OrthographicCamera& camera) {
    s_Data->FlatColorShader->Bind();
    s_Data->FlatColorShader->UploadUniformMat4("u_ViewProjection",
                                               camera.GetViewProjectionMatrix());
}

void Renderer2D::EndScene() {}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size,
                          const glm::vec4& color) {
    s_Data->FlatColorShader->Bind();
    s_Data->FlatColorShader->UploadUniformFloat4("u_Color", color);

    s_Data->QuadVertexArray->Bind();
    glDrawElements(GL_TRIANGLES, s_Data->QuadVertexArray->GetIndexBuffer()->GetCount(),
                   GL_UNSIGNED_INT, nullptr);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size,
                          const glm::vec4& color) {
    DrawQuad({position.x, position.y}, size, color);
}

}  // namespace ARcane
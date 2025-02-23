#include "ARcane/Renderer/Renderer2D.hpp"

#include "ARcane/Renderer/VertexArray.hpp"
#include "ARcane/Renderer/Shader.hpp"
#include "ARcane/Renderer/Renderer.hpp"

namespace ARcane {

struct Renderer2DStorage {
    Ref<VertexArray> QuadVertexArray;
    Ref<Shader> TextureShader;
    Ref<Texture2D> WhiteTexture;
};

static Renderer2DStorage* s_Data;

void Renderer2D::Init() {
    s_Data = new Renderer2DStorage();
    s_Data->QuadVertexArray = CreateRef<VertexArray>();

    float vertices[] = {
        -0.5f, 0.5f,  0.0f, 0.0f, 0.0f,  //
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  //
        0.5f,  -0.5f, 0.0f, 1.0f, 1.0f,  //
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  //
    };

    Ref<VertexBuffer> squareVB = CreateRef<VertexBuffer>(vertices, sizeof(vertices));
    squareVB->SetLayout({
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float2, "a_TexCoord"},
    });
    s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

    uint32_t indices[6] = {0, 1, 2, 2, 3, 0};

    Ref<IndexBuffer> squareIB = CreateRef<IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));
    s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

    // Create white texture
    s_Data->WhiteTexture = CreateRef<Texture2D>(1, 1);
    uint32_t whiteTextureData = 0xffffffff;
    s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

    s_Data->TextureShader = CreateRef<Shader>("../assets/shaders/Texture.glsl");
    s_Data->TextureShader->Bind();
    s_Data->TextureShader->SetInt("u_Texture", 0);
}

void Renderer2D::Shutdown() { delete s_Data; }

void Renderer2D::BeginScene(const OrthographicCamera& camera) {
    s_Data->TextureShader->Bind();
    s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
}

void Renderer2D::EndScene() {}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size,
                          const glm::vec4& color) {
    DrawQuad({position.x, position.y, 0.0f}, size, color);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size,
                          const Ref<Texture2D>& texture) {
    DrawQuad({position.x, position.y, 0.0f}, size, texture);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size,
                          const glm::vec4& color) {
    s_Data->TextureShader->SetFloat4("u_Color", color);
    s_Data->WhiteTexture->Bind();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                          glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
    s_Data->TextureShader->SetMat4("u_Transform", transform);

    // FIX: Bind the vertex array before drawing
    s_Data->QuadVertexArray->Bind();
    Renderer::DrawIndexed(s_Data->QuadVertexArray);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size,
                          const Ref<Texture2D>& texture) {
    s_Data->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
    texture->Bind();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                          glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
    s_Data->TextureShader->SetMat4("u_Transform", transform);

    s_Data->QuadVertexArray->Bind();
    Renderer::DrawIndexed(s_Data->QuadVertexArray);
}
}  // namespace ARcane
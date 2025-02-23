#include "ARcane.hpp"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public ARcane::Layer {
   public:
    ExampleLayer()
        : Layer("Example"),
          m_Camera(-1.6f, 1.6f, -1.2f, 1.2f),
          m_CameraPosition(0.0f),
          m_SquarePosition(0.0f) {
        m_VertexArray = std::make_shared<ARcane::VertexArray>();

        // Define vertices for a triangle
        float verticies[] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,  //
            0.5f,  -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,  //
            0.0f,  0.5f,  0.0f, 0.2f, 0.2f, 0.8f, 0.0f,  //
        };
        auto m_VertexBuffer = std::make_shared<ARcane::VertexBuffer>(verticies, sizeof(verticies));

        ARcane::BufferLayout layout = {
            {ARcane::ShaderDataType::Float3, "a_Position"},
            {ARcane::ShaderDataType::Float4, "a_Color"},
        };
        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        uint32_t indices[3] = {0, 1, 2};
        auto indexBuffer =
            std::make_shared<ARcane::IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        float squareVerticies[] = {
            -0.5f, -0.5f, 0.0f,  //
            0.5f,  -0.5f, 0.0f,  //
            0.5f,  0.5f,  0.0f,  //
            -0.5f, 0.5f,  0.0f,  //
        };

        m_SquareVA = std::make_shared<ARcane::VertexArray>();
        auto squareVB =
            std::make_shared<ARcane::VertexBuffer>(squareVerticies, sizeof(squareVerticies));

        ARcane::BufferLayout squareLayout = {
            {ARcane::ShaderDataType::Float3, "a_Position"},
        };
        squareVB->SetLayout(squareLayout);
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        auto squareIB = std::make_shared<ARcane::IndexBuffer>(
            squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
        m_SquareVA->SetIndexBuffer(squareIB);

        std::string vertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;

        out vec3 v_Position;
        out vec4 v_Color;

        void main() {
            v_Position = a_Position;
            v_Color = a_Color;
            gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
        }
    )";

        std::string fragmentSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_Position;
        in vec4 v_Color;

        void main() {
            color = v_Color; 
        }
    )";

        std::string flatColorShaderVertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;

        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;

        out vec3 v_Position;

        void main() {
            v_Position = a_Position;
            gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
        }
    )";

        std::string flatColorFragmentVertexSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_Position;

        uniform vec4 u_Color;

        void main() {
            color = u_Color; 
        }
    )";

        m_Shader = std::make_shared<ARcane::Shader>(vertexSrc, fragmentSrc);
        m_flatColorShader =
            std::make_shared<ARcane::Shader>(flatColorShaderVertexSrc, flatColorFragmentVertexSrc);
    }
    ~ExampleLayer() {}

    void OnUpdate(ARcane::Timestep ts) override {
        if (ARcane::Input::IsKeyPressed(ARcane::Key::Left)) {
            m_CameraPosition.x -= m_CameraMoveSpeed * ts;
        } else if (ARcane::Input::IsKeyPressed(ARcane::Key::Right)) {
            m_CameraPosition.x += m_CameraMoveSpeed * ts;
        } else if (ARcane::Input::IsKeyPressed(ARcane::Key::Up)) {
            m_CameraPosition.y += m_CameraMoveSpeed * ts;
        } else if (ARcane::Input::IsKeyPressed(ARcane::Key::Down)) {
            m_CameraPosition.y -= m_CameraMoveSpeed * ts;
        } else if (ARcane::Input::IsKeyPressed(ARcane::Key::A)) {
            m_CameraRotation += m_CameraRotationSpeed * ts;
        } else if (ARcane::Input::IsKeyPressed(ARcane::Key::D)) {
            m_CameraRotation -= m_CameraRotationSpeed * ts;
        }

        if (ARcane::Input::IsKeyPressed(ARcane::Key::J)) {
            m_SquarePosition.x -= m_SquareMoveSpeed * ts;
        } else if (ARcane::Input::IsKeyPressed(ARcane::Key::L)) {
            m_SquarePosition.x += m_SquareMoveSpeed * ts;
        } else if (ARcane::Input::IsKeyPressed(ARcane::Key::I)) {
            m_SquarePosition.y += m_SquareMoveSpeed * ts;
        } else if (ARcane::Input::IsKeyPressed(ARcane::Key::K)) {
            m_SquarePosition.y -= m_SquareMoveSpeed * ts;
        }

        ARcane::Renderer::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        ARcane::Renderer::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        ARcane::Renderer::BeginScene(m_Camera);

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
        glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

                m_flatColorShader->SetVec4("u_Color", m_SquareColor);

                ARcane::Renderer::Submit(m_flatColorShader, m_SquareVA, transform);
            }
        }

        ARcane::Renderer::EndScene();
    }

    void OnImGuiRender() override {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void OnEvent(ARcane::Event& event) override {}

   private:
    std::shared_ptr<ARcane::Shader> m_Shader;  // Shader instance.
    std::shared_ptr<ARcane::VertexArray> m_VertexArray;

    std::shared_ptr<ARcane::Shader> m_flatColorShader;
    std::shared_ptr<ARcane::VertexArray> m_SquareVA;

    ARcane::OrthographicCamera m_Camera;

    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 5.0f;
    float m_SquareMoveSpeed = 1.0f;

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 180.0f;

    glm::vec3 m_SquarePosition;
    glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};

class Sandbox : public ARcane::Application {
   public:
    Sandbox() { PushLayer(new ExampleLayer()); }
    ~Sandbox() {}
};

ARcane::Application* ARcane::CreateApplication() { return new Sandbox(); }
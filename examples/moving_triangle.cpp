#include "ARcane.hpp"
#include "imgui.h"

class ExampleLayer : public ARcane::Layer {
   public:
    ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -1.2f, 1.2f), m_CameraPosition(0.0f) {
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
            -0.75f, -0.75f, 0.0f,  //
            0.75f,  -0.75f, 0.0f,  //
            0.75f,  0.75f,  0.0f,  //
            -0.75f, 0.75f,  0.0f,  //
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

        out vec3 v_Position;
        out vec4 v_Color;

        void main() {
            v_Position = a_Position;
            v_Color = a_Color;
            gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

        std::string blueShaderVertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;

        uniform mat4 u_ViewProjection;

        out vec3 v_Position;

        void main() {
            v_Position = a_Position;
            gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
        }
    )";

        std::string blueFragmentVertexSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_Position;

        void main() {
            color = vec4(0.04, 0.04, 0.2, 1.0); 
        }
    )";

        m_Shader = std::make_shared<ARcane::Shader>(vertexSrc, fragmentSrc);
        m_BlueShader = std::make_shared<ARcane::Shader>(blueShaderVertexSrc, blueFragmentVertexSrc);
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

        ARcane::Renderer::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        ARcane::Renderer::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        ARcane::Renderer::BeginScene(m_Camera);

        ARcane::Renderer::Submit(m_BlueShader, m_SquareVA);
        ARcane::Renderer::Submit(m_Shader, m_VertexArray);

        ARcane::Renderer::EndScene();
    }

    void OnImGuiRender() override {}

    void OnEvent(ARcane::Event& event) override {}

   private:
    std::shared_ptr<ARcane::Shader> m_Shader;  // Shader instance.
    std::shared_ptr<ARcane::VertexArray> m_VertexArray;

    std::shared_ptr<ARcane::Shader> m_BlueShader;
    std::shared_ptr<ARcane::VertexArray> m_SquareVA;

    ARcane::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 5.0f;
    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 180.0f;
};

class Sandbox : public ARcane::Application {
   public:
    Sandbox() { PushLayer(new ExampleLayer()); }
    ~Sandbox() {}
};

ARcane::Application* ARcane::CreateApplication() { return new Sandbox(); }
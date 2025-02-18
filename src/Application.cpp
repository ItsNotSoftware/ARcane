#include "ARcane/Application.hpp"

namespace ARcane {

Application* Application::s_Instance = nullptr;

Application::Application() : m_Camera(-1.6f, 1.6f, -1.2f, 1.2f) {
    ARC_CORE_ASSERT(
        !s_Instance,
        "Creating multiple Application instances is not allowed. Use Application::Get() instead.");
    s_Instance = this;

    // Create the application window
    m_Window = std::make_unique<Window>(1800, 1200, "ARcane Engine");

    // Bind event handling to this application instance
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

    // Initialize ImGui
    m_ImGuiLayer = new ImGuiLayer;
    PushOverlay(m_ImGuiLayer);

    m_VertexArray = std::make_shared<VertexArray>();

    // Define vertices for a triangle
    float verticies[] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,  //
        0.5f,  -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,  //
        0.0f,  0.5f,  0.0f, 0.2f, 0.2f, 0.8f, 0.0f,  //
    };
    auto m_VertexBuffer = std::make_shared<VertexBuffer>(verticies, sizeof(verticies));

    BufferLayout layout = {
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float4, "a_Color"},
    };
    m_VertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);

    uint32_t indices[3] = {0, 1, 2};
    auto indexBuffer = std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    float squareVerticies[] = {
        -0.75f, -0.75f, 0.0f,  //
        0.75f,  -0.75f, 0.0f,  //
        0.75f,  0.75f,  0.0f,  //
        -0.75f, 0.75f,  0.0f,  //
    };

    m_SquareVA = std::make_shared<VertexArray>();
    auto squareVB = std::make_shared<VertexBuffer>(squareVerticies, sizeof(squareVerticies));

    BufferLayout squareLayout = {
        {ShaderDataType::Float3, "a_Position"},
    };
    squareVB->SetLayout(squareLayout);
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    auto squareIB =
        std::make_shared<IndexBuffer>(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
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

    m_Shader = std::make_shared<Shader>(vertexSrc, fragmentSrc);
    m_BlueShader = std::make_shared<Shader>(blueShaderVertexSrc, blueFragmentVertexSrc);
}

Application::~Application() {}

void Application::PushLayer(Layer* layer) {
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer* overlay) {
    m_LayerStack.PushOverlay(overlay);
    overlay->OnAttach();
}

void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);

    // Handle window close events
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

    // Pass the event to layers from top to bottom
    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
        (*--it)->OnEvent(e);
        if (e.Handled) {
            break;
        }
    }
}

void Application::Run() {
    while (m_Running) {
        Renderer::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Renderer::Clear();

        Renderer::BeginScene(m_Camera);

        Renderer::Submit(m_BlueShader, m_SquareVA);
        Renderer::Submit(m_Shader, m_VertexArray);

        Renderer::EndScene();

        // Update all active layers
        for (auto layer : m_LayerStack) {
            layer->OnUpdate();
        }

        // Render ImGui elements
        m_ImGuiLayer->Begin();
        for (auto layer : m_LayerStack) {
            layer->OnImGuiRender();
        }
        m_ImGuiLayer->End();

        // Update the window (handle input, buffer swaps, etc.)
        m_Window->Update();
    }
}

bool Application::OnWindowClose(WindowCloseEvent&) {
    m_Running = false;  // Stop the application loop
    return true;
}

}  // namespace ARcane

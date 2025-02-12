#include "ARcane/Application.hpp"

#include <glad/glad.h>

namespace ARcane {

Application* Application::s_Instance = nullptr;

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
    switch (type) {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4:
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4:
            return GL_FLOAT;
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4:
            return GL_INT;
        case ShaderDataType::Bool:
            return GL_BOOL;
        default:
            ARC_CORE_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
    }
}

Application::Application() {
    ARC_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    // Create the application window
    m_Window = std::make_unique<Window>(1800, 1200, "ARcane Engine");

    // Bind event handling to this application instance
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

    // Initialize ImGui
    m_ImGuiLayer = new ImGuiLayer;
    PushOverlay(m_ImGuiLayer);

    // Initialize OpenGL vertex array and buffer
    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    // Define vertices for a triangle
    float verticies[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  //
        0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,  //
        0.0f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,  //
    };
    m_VertexBuffer = std::make_unique<VertexBuffer>(verticies, sizeof(verticies));

    {
        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
        };
        m_VertexBuffer->SetLayout(layout);
    }

    uint32_t index = 0;
    for (const auto& element : m_VertexBuffer->GetLayout()) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, element.GetComponentCount(),
                              ShaderDataTypeToOpenGLBaseType(element.Type),
                              element.Normalized ? GL_TRUE : GL_FALSE,
                              m_VertexBuffer->GetLayout().GetStride(), (const void*)element.Offset);
        index++;
    }

    uint32_t indices[3] = {0, 1, 2};
    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));

    std::string vertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        out vec3 v_Position;
        out vec4 v_Color;

        void main() {
            v_Position = a_Position;
            v_Color = a_Color;
            gl_Position = vec4(a_Position, 1.0);
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

    m_Shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
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
        glClearColor(0.1f, 0.1f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Shader->Bind();
        glBindVertexArray(m_VertexArray);
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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

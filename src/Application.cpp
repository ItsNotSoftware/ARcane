#include "ARcane/Application.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ARcane {

Application* Application::s_Instance = nullptr;

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
    glGenBuffers(1, &m_VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

    // Define vertices for a triangle
    float verticies[3 * 3] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

    // Upload vertex data to the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    // Enable the first vertex attribute
    glEnableVertexAttribArray(0);

    // Specify the layout of the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    // Create an index buffer
    glGenBuffers(1, &m_IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

    unsigned int indices[3] = {0, 1, 2};
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    std::string vertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;
        out vec3 v_Position;

        void main() {
            v_Position = a_Position;
            gl_Position = vec4(a_Position, 1.0);
        }
    )";

    std::string fragmentSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_Position;

        void main() {
            color = vec4(v_Position * 0.5 + 0.5, 1.0);
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
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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

#include "ARcane/ImGuiLayer.hpp"

#include "ARcane/Core.hpp"
#include "ARcane/Application.hpp"
#include "glad/glad.h"  //! glad must be included before glfw3.h
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace ARcane {

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::OnAttach() {
    ImGui::CreateContext();

    Application& app = Application::Get();
    GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void ImGuiLayer::OnDetach() {}

void ImGuiLayer::OnUpdate() {
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

    float time = static_cast<float>(glfwGetTime());
    io.DeltaTime = m_Time > 0.0f ? time - m_Time : 1.0f / 60.0f;
    m_Time = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(Event& event) {
    // Dispatch events to this event handlers
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseButtonPressedEvent>(
        BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(
        BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
    dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
    dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
    dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
    dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
}

bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[event.GetButton()] = true;

    return false;  // Mark event as unhandled (propagate to other layers)
}

bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[event.GetButton()] = false;

    return false;  // Mark event as unhandled (propagate to other layers)
}

bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& event) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += event.GetXOffset();
    io.MouseWheel += event.GetYOffset();

    return false;  // Mark event as unhandled (propagate to other layers)
}

bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& event) {
    return false;  // Mark event as unhandled (propagate to other layers)
}

bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& event) {
    return false;  // Mark event as unhandled (propagate to other layers)
}

bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& event) {
    return false;  // Mark event as unhandled (propagate to other layers)
}

bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& event) {
    return false;  // Mark event as unhandled (propagate to other layers)
}

};  // namespace ARcane
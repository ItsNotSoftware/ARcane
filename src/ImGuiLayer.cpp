#include "ARcane/ImGuiLayer.hpp"

#include "ARcane/Core.hpp"
#include "ARcane/Application.hpp"
<<<<<<< HEAD
#include <glad/glad.h>  //! glad must be included before glfw3.h
=======
#include "glad/glad.h"  //! glad must be included before glfw3.h
>>>>>>> 4ca001afdc0a19a36da49aef12fc4fbc3ba23c36
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

    // Initialize platform/renderer bindings
    // Set to false to disable GLFW callbacks, and bind them manually in OnEvent() func
    // If set to true, disable OnEvent() in ImGuiLayer and GLFW callbacks will be used
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

void ImGuiLayer::OnEvent(Event&) {}

};  // namespace ARcane
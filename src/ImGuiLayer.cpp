#include "ARcane/ImGuiLayer.hpp"

#include "ARcane/Core.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace ARcane {

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::OnAttach() {}

void ImGuiLayer::OnDetach() {}

void ImGuiLayer::OnUpdate() {}

void ImGuiLayer::OnEvent(Event& event) {}

};  // namespace ARcane
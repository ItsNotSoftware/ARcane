#pragma once

extern ARcane::Application* ARcane::CreateApplication();

int main(int argc, char** argv) {
    ARcane::Log::Init();
    ARC_CORE_WARN("Initialized Log!");
    ARC_INFO("Hello!");

    auto app = ARcane::CreateApplication();
    app->Run();
    delete app;

    return 0;
}
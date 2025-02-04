#pragma once

extern ARcane::Application* ARcane::CreateApplication();

int main() {
    ARcane::Log::Init();

    auto app = ARcane::CreateApplication();
    app->Run();
    delete app;

    return 0;
}
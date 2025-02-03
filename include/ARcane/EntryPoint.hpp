#pragma once

extern ARcane::Application* ARcane::CreateApplication();

int main(int argc, char** argv) {
    ARcane::Log::Init();
    ARcane::Log::GetCoreLogger()->info("Initialized Log!");

    auto app = ARcane::CreateApplication();
    app->Run();
    delete app;

    return 0;
}
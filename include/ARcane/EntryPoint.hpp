#pragma once

extern ARcane::Application* ARcane::CreateApplication();

int main() {
    ARcane::Log::Init();

    ARC_PROFILE_BEGIN_SESSION("Startup", "ARcaneProfile-Startup.json");
    auto app = ARcane::CreateApplication();
    ARC_PROFILE_END_SESSION();

    ARC_PROFILE_BEGIN_SESSION("Runtime", "ARcaneProfile-Runtime.json");
    app->Run();
    ARC_PROFILE_END_SESSION();

    ARC_PROFILE_BEGIN_SESSION("Shutdown", "ARcaneProfile-Shutdown.json");
    delete app;
    ARC_PROFILE_END_SESSION();

    return 0;
}
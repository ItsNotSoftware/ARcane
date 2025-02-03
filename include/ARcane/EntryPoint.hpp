#pragma once

extern ARcane::Application* ARcane::CreateApplication();

int main(int argc, char** argv) {
    auto app = ARcane::CreateApplication();
    app->Run();
    delete app;

    return 0;
}
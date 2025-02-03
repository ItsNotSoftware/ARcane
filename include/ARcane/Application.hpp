#pragma once

namespace ARcane {

class Application {
   public:
    Application();
    virtual ~Application();

    void Run();
};

Application* CreateApplication();

}  // namespace ARcane

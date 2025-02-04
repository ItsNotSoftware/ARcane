# ARcane

**ARcane** is an augmented reality engine written in C++ with OpenGL, built specifically for robot teleoperation. It streamlines the integration of live camera feeds, dynamic virtual object rendering, and intuitive UI overlays to help you build immersive AR applications for remote robot control.

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/your-repo/ARcane)  
[![License](https://img.shields.io/badge/license-MIT-blue)](LICENSE)

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
    - [Option 1: Git Submodule](#option-1-git-submodule)
    - [Option 2: Install as a Library](#option-2-install-as-a-library)
- [Integration into Your Project](#integration-into-your-project)
- [Usage Example](#usage-example)
- [License](#license)
- [Contributing](#contributing)
- [Contact](#contact)

## Features

- **Robot Teleoperation:**  
  Designed for remote control applications, ARcane seamlessly combines real-time camera feeds with interactive overlays to enhance teleoperation.

- **Live Camera Streaming:**  
  Capture and display live video streams from robot-mounted cameras for accurate remote monitoring.

- **Dynamic Virtual Object Rendering:**  
  Render virtual objects in real time, augmenting the environment to improve situational awareness.

- **Intuitive UI Overlays:**  
  Integrate customizable user interface elements—such as buttons, menus, and alerts—to facilitate control and monitoring.

- **Modular Architecture:**  
  Whether you’re using ARcane as a standalone application or integrating it into a larger system, its modular design makes it easy to extend and adapt.

## Getting Started

### Prerequisites

Ensure your development environment meets the following requirements:

- **Compiler:** A C++17 (or newer) compliant compiler
- **Build System:** [CMake](https://cmake.org/) (version 3.10 or higher recommended)
- **Graphics:** [OpenGL 3.3](https://www.opengl.org/) (or newer)
- **Windowing:** [GLFW 3.3](https://www.glfw.org/) (or newer)

### Installation

Choose one of the following options to integrate ARcane into your project:

#### Option 1: Git Submodule

1. **Add ARcane as a Submodule:**

   Navigate to your project's root directory and add ARcane as a submodule (for example, under `external/`):

   ```bash
   git submodule add https://github.com/ItsNotSoftware/ARcane.git external/ARcane
   git submodule update --init --recursive
   ```

2. **Modify Your CMake Configuration:**

   Update your `CMakeLists.txt` to include and link ARcane:

   ```cmake
   add_subdirectory(external/ARcane)
   target_link_libraries(YourProject ARcane)
   ```

#### Option 2: Install as a Library

1. **Clone the Repository:**

   Clone the ARcane repository to your local machine:

   ```bash
   git clone https://github.com/ItsNotSoftware/ARcane.git
   cd ARcane
   git submodule update --init --recursive
   ```

2. **Compile the Library:**

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Install the Library:**

   ```bash
   sudo make install
   ```

4. **Link ARcane in Your Project:**

   Update your `CMakeLists.txt`:

   ```cmake
   find_package(ARcane REQUIRED)
   target_link_libraries(YourProject ARcane::ARcane)
   ```

## Integration into Your Project

ARcane provides a standalone application with its own `main()` function. To embed ARcane within your own project, derive from the `ARcane::Application` class and override the `Run()` method with your custom logic.

```cpp
#include "ARcane.hpp" // If ARcane is used as a submodule
#include <ARcane.hpp> // If ARcane is installed as a library

class YourAppMainClass : public ARcane::Application {
public:
    YourAppMainClass() {
        // Initialize your application here.
    };

    void Run() override {
        // Your custom application logic here.
    }

    ~YourAppMainClass() {
        // Clean up your application here.
    };
};

// This function is called by ARcane to create your application instance.
ARcane::Application* ARcane::CreateApplication() {
    return new YourAppMainClass();
}
```

## Usage Example

Once integrated, build and run your project. ARcane handles window initialization, camera streaming, and rendering, allowing you to focus on developing your application logic within the overridden `Run()` method.

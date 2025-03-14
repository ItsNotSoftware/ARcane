# ARcane

**ARcane** is an augmented reality engine written in C++ with OpenGL, built specifically for robot teleoperation. It streamlines the integration of live camera feeds, dynamic virtual object rendering, and intuitive UI overlays to help you build immersive AR applications for remote robot control.

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/your-repo/ARcane)  
[![License](https://img.shields.io/badge/license-MIT-blue)](LICENSE)

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installing Dependencies](#installing-dependencies)
  - [Project Integration](#project-integration)
    - [Option 1: Git Submodule](#option-1-git-submodule)
    - [Option 2: Install as a Library](#option-2-install-as-a-library)
- [Usage](#Usage)

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

---

## Getting Started

### **Prerequisites**

Ensure your development environment meets the following requirements:

- **Compiler:** A C++17 (or newer) compliant compiler
- **Build System:** [CMake](https://cmake.org/) (version 3.15 or higher recommended)
- **Graphics:** [OpenGL 3.3](https://www.opengl.org/) (or newer)
- **OpenCV:** [OpenCV](https://opencv.org/)
- **ZMQ:** [ZeroMQ](https://zeromq.org/)

---

## Installing Dependencies

Before building ARcane, install the required system libraries and tools.

### **Ubuntu/Debian**

```sh
sudo apt update
sudo apt install cmake g++ libxkbcommon-dev libgl1-mesa-dev libglu1-mesa-dev libwayland-dev \
libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev libx11-dev
```

### **Arch Linux**

```sh
sudo pacman -S cmake gcc xorg-xrandr xorg-xinput xorg-xwayland libxkbcommon wayland
```

### **Fedora**

```sh
sudo dnf install cmake gcc-c++ mesa-libGL-devel mesa-libGLU-devel libX11-devel \
libXcursor-devel libXi-devel libXrandr-devel libxkbcommon-devel wayland-devel
```

### **macOS (Homebrew)**

```sh
brew install cmake glfw
```

---

## Project Integration

Choose one of the following options to integrate ARcane into your project.

### **Option 1: Git Submodule**

1. **Add ARcane as a Submodule:**

   Navigate to your project's root directory and add ARcane as a submodule (for example, under `external/`):

   ```sh
   git submodule add https://github.com/ItsNotSoftware/ARcane.git external/ARcane
   git submodule update --init --recursive
   ```

2. **Modify Your CMake Configuration:**

   Update your `CMakeLists.txt` to include and link ARcane:

   ```cmake
   add_subdirectory(external/ARcane)
   target_link_libraries(YourProject ARcane)
   ```

---

### **Option 2: Install as a Library**

1. **Clone the Repository:**

   ```sh
   git clone https://github.com/ItsNotSoftware/ARcane.git
   cd ARcane
   git submodule update --init --recursive
   ```

2. **Compile the Library:**

   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Install the Library:**

   ```sh
   sudo make install
   ```

4. **Link ARcane in Your Project:**

   ```cmake
   find_package(ARcane REQUIRED)
   target_link_libraries(YourProject ARcane::ARcane)
   ```

---

## Usage

ARcane provides a standalone application with its own `main()` function. To embed ARcane within your own project, derive from the `ARcane::Application` class.

```cpp
#include "ARcane.hpp" // If ARcane is used as a submodule
#include <ARcane.hpp> // If ARcane is installed as a library

class ExampleLayer : public ARcane::Layer {
   public:
    ExampleLayer() : Layer("Example") {}
    ~ExampleLayer() {}

    void OnUpdate() override { ARC_INFO("ExampleLayer::Update"); }

    void OnEvent(ARcane::Event& event) override { ARC_TRACE("{0}", event.ToString()); }
};

class MyApp : public ARcane::Application {
   public:
    MyApp() { PushLayer(new ExampleLayer()); }
    ~MyApp() {}
};

ARcane::Application* ARcane::CreateApplication() { return new MyApp(); }
```

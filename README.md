# ARcane

ARcane is an augmented reality engine written in C++ with OpenGL for robot teleoperation. ARcane streamlines the process of integrating live camera streams, dynamic virtual object rendering, and UI overlays into your AR applications.

## Key Features

- **Robot Teleoperation:**  
  Specially designed for robot teleoperation, ARcane facilitates remote operation by seamlessly integrating real-time camera feeds with interactive control overlays.

- **Live Camera Streaming:**  
  Capture and display live video streams from robot-mounted cameras for accurate remote monitoring.

- **Dynamic Virtual Object Rendering:**  
  Render virtual objects dynamically to enhance situational awareness and assist in robot control.

- **Intuitive UI Overlays:**  
  Easily integrate customizable UI elements (buttons, menus, and alerts) to control and monitor robot operations.

- **Modular Architecture:**  
  Designed to be integrated as a submodule, ARcane can be easily incorporated into larger teleoperation systems or robotics projects.

## Getting Started

### Prerequisites

- C++17 (or newer) compiler
- CMake (version 3.10 or higher recommended)
- OpenGL 3.3 (or newer)
- Additional libraries (e.g., GLFW, GLEW) as required

### Clone the Repository

```bash
git clone https://github.com/yourusername/ARcane.git
```

### Build Instructions

1. Create a build directory:
   ```bash
   mkdir build && cd build
   ```~
2. Run CMake:
   ```bash
   cmake ..
   ```~
3. Build the project:
   ```bash
   make
   ```~

### Integration

To use ARcane as a submodule in your teleoperation project, add it to your project's directory (e.g., under `external/`) and modify your CMake configuration as follows:

```cmake
add_subdirectory(external/ARcane)
target_link_libraries(YourProject ARcane)
```
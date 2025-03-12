cmake_minimum_required(VERSION 3.15)
project(ARcane LANGUAGES C CXX)

# Set C++ standard and compile options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall)

# Submodule initialization check
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "Submodules missing! Run:\n\tgit submodule update --init --recursive")
endif()

# Find required external libraries
find_library(ZMQ_LIB zmq REQUIRED)
if(NOT ZMQ_LIB)
    message(FATAL_ERROR "ZeroMQ library not found!")
endif()

find_package(OpenGL REQUIRED)
find_package(OpenCV REQUIRED)

# Add subdirectories for submodules
add_subdirectory(external/spdlog)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

# Collect all source files from the src directory
file(GLOB_RECURSE ARCANE_SOURCES "src/**/*.cpp" "src/**/*.c")

# Define the ARcane static library target
add_library(ARcane STATIC ${ARCANE_SOURCES})

# Include directories for ARcane
target_include_directories(ARcane PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../stb
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui # Core ImGui headers (e.g., imgui.h)
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/backends # Backend headers (e.g., imgui_impl_glfw.h)
    ${OpenCV_INCLUDE_DIRS} # OpenCV headers
)

# Add ImGui source files
set(IMGUI_CORE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui_widgets.cpp
)
set(IMGUI_BACKEND_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/backends/imgui_impl_opengl3.cpp
)
set(IMGUI_STDLIB_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/misc/cpp/imgui_stdlib.cpp
)
target_sources(ARcane PRIVATE
    ${IMGUI_CORE_SOURCES}
    ${IMGUI_BACKEND_SOURCES}
    ${IMGUI_STDLIB_SOURCES}
)

# Link external libraries
target_link_libraries(ARcane PUBLIC
    glfw
    glm
    OpenGL::GL
    spdlog::spdlog
    ${OpenCV_LIBS}
    ${ZMQ_LIB}
)

# Set target version properties
set_target_properties(ARcane PROPERTIES VERSION 1.0 SOVERSION 1)

# Installation rules
install(
    TARGETS ARcane
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ARcane
    DESTINATION include
)

# Define assets directory as a compile definition
target_compile_definitions(ARcane PUBLIC ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

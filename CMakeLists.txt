cmake_minimum_required(VERSION 3.15)
project(ARcane LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")


# Submodule initialization check
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "Submodules missing! Run:\n\tgit submodule update --init --recursive")
endif()

# Submodules
add_subdirectory(external/spdlog)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

find_package(OpenGL REQUIRED)

# Gather your own project sources (e.g. your code and glad.c)
file(GLOB ARCANE_SOURCES "src/*.cpp" "src/*.c")

# Define your main target (library or executable)
add_library(ARcane STATIC ${ARCANE_SOURCES})

# Add ImGui core source files.
set(IMGUI_CORE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui_widgets.cpp
)

# Add the backend sources that match your project (GLFW + OpenGL3)
set(IMGUI_BACKEND_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/backends/imgui_impl_opengl3.cpp
)

# Add std::string support if needed:
set(IMGUI_STDLIB_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/misc/cpp/imgui_stdlib.cpp
)

# Add all ImGui sources to your ARcane target.
target_sources(ARcane PRIVATE
    ${IMGUI_CORE_SOURCES}
    ${IMGUI_BACKEND_SOURCES}
    ${IMGUI_STDLIB_SOURCES}
)

# Set up include directories so that your code can find headers.
target_include_directories(ARcane PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui # For core ImGui headers (e.g., imgui.h)
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/backends # For backend headers (e.g., imgui_impl_glfw.h)
    ${CMAKE_CURRENT_SOURCE_DIR}/external/stb # For stb_image.h
)

# Link with other libraries
target_link_libraries(ARcane PUBLIC
    glfw
    glm
    OpenGL::GL
    spdlog::spdlog
)

set_target_properties(ARcane PROPERTIES VERSION 1.0 SOVERSION 1)

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

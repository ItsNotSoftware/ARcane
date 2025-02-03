cmake_minimum_required(VERSION 3.15)
project(ARcane LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Include Glad headers and source
file(GLOB ARCANE_SOURCES "src/*.cpp" "src/*.c") # Should include glad.c

# Define a shared library
add_library(ARcane SHARED ${ARCANE_SOURCES})


target_include_directories(ARcane PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../glad/include
)

target_link_libraries(ARcane PUBLIC glfw OpenGL::GL)

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

cmake_minimum_required(VERSION 3.15)
project(ARcane LANGUAGES C CXX) # Enable C and C++

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE STRING "C compiler" FORCE)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE STRING "C++ compiler" FORCE)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Include Glad headers and source
file(GLOB ARCANE_SOURCES "src/*.cpp" "src/*.c") # Should include glad.c

add_library(ARcane STATIC ${ARCANE_SOURCES})

target_include_directories(ARcane PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../glad/include
)

target_link_libraries(ARcane PUBLIC glfw OpenGL::GL)
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

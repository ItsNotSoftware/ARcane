cmake_minimum_required(VERSION 3.15)
project(ARcane LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE STRING "C++ compiler" FORCE)
set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE STRING "C compiler" FORCE)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

file(GLOB ARCANE_SOURCES "src/*.cpp")

add_library(ARcane STATIC ${ARCANE_SOURCES})

target_include_directories(ARcane PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(ARcane PUBLIC OpenGL::GL glm)

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

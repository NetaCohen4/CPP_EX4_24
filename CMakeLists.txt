cmake_minimum_required(VERSION 3.10)
project(TreeVisualization)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Add executable
add_executable(TreeVisualization main.cpp)

# Link SFML libraries
target_link_libraries(TreeVisualization sfml-system sfml-window sfml-graphics)

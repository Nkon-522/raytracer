cmake_minimum_required(VERSION 3.26)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(raytracer)

add_subdirectory(${CMAKE_SOURCE_DIR}/ext)
add_subdirectory(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL2main SDL2-static ImGui-static)


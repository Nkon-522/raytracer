file(GLOB IMGUI_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/ImGui/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ImGui/backends/imgui_impl_sdl2.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ImGui/backends/imgui_impl_sdlrenderer2.cpp
)
add_library(ImGui-static STATIC ${IMGUI_SOURCES})

target_include_directories(ImGui-static PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ImGui
        ${CMAKE_CURRENT_SOURCE_DIR}/ImGui/backends
)

target_link_libraries(ImGui-static SDL2main SDL2-static)

#ifndef RAYTRACER_APP_H
#define RAYTRACER_APP_H

#define SDL_MAIN_HANDLED

#include <SDL.h>

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include <iostream>
#include <memory>

#include "image/image.h"
#include "utilities/timer.h"

class App {
private:
    // VARIABLES

    // Window to be rendered
    SDL_Window* window = nullptr;

    // Window variables
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    const std::string TITLE = "Raytracer";
    const SDL_WindowFlags WINDOW_FLAGS = static_cast<SDL_WindowFlags>(
            SDL_WINDOW_RESIZABLE |
            SDL_WINDOW_ALLOW_HIGHDPI
            );

    // Renderer contained by window
    SDL_Renderer* renderer = nullptr;
    const SDL_RendererFlags  RENDERER_FLAGS = static_cast<SDL_RendererFlags>(
            SDL_RENDERER_PRESENTVSYNC |
            SDL_RENDERER_ACCELERATED
            );

    // Texture
    SDL_Texture* texture = nullptr;

    // ImGui variables
    ImGuiIO* io = nullptr;
    const ImGuiConfigFlags ImGui_FLAGS = static_cast<ImGuiConfigFlags>(
            ImGuiConfigFlags_NavEnableKeyboard |    // Enable Keyboard Controls
            ImGuiConfigFlags_NavEnableGamepad       // Enable Gamepad Controls
    );

    // App variables
    bool run{true};
    Timer timer{};
    SDL_Event event{};
    ImVec4 clear_color{0.45f, 0.55f, 0.60f, 1.00f};

    // Raytracer variables
    Image image{};
    // Destination rectangle for image
    SDL_Rect dstRect{0, 0, Image::IMAGE_WIDTH, Image::IMAGE_HEIGHT};


    // INITIALIZATION
    void init_sdl();
    void init_ImGui();
    void init();

    // EXECUTION
    void handle_events();
    void update();
    void set_render_ImGui();
    void render();

    // TERMINATION
    static void terminate_ImGui();
    void terminate_sdl() const;
    void terminate() const;

public:
    App() { this->init(); }

    void execute() {
        // Main loop
        while (run) {
            handle_events();
            update();
            render();
        }
    }

    ~App() { terminate(); }
};

#endif //RAYTRACER_APP_H

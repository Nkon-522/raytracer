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

#include "utilities/timer.h"
#include "raytracer/raytracer.h"

class App {
private:
    // VARIABLES

    // Window to be rendered
    SDL_Window* window;

    // Window variables
    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;
    const std::string TITLE;
    const SDL_WindowFlags WINDOW_FLAGS;

    // Renderer contained by window
    SDL_Renderer* renderer;
    const SDL_RendererFlags  RENDERER_FLAGS;

    // Texture
    SDL_Texture* texture;

    // ImGui variables
    ImGuiIO* io;
    const ImGuiConfigFlags ImGui_FLAGS;

    // App variables
    bool run;
    Timer timer;
    SDL_Event event;
    ImVec4 clear_color;

    // Raytracer variables
    Raytracer raytracer;
    // Destination rectangle for image
    SDL_Rect dstRect;

    // INITIALIZATION
    void init_sdl();
    void init_ImGui();
    void init();

    // EXECUTION
    void handle_events();
    void update() const;
    void raytrace();
    void set_render_ImGui();
    void render();

    // TERMINATION
    static void terminate_ImGui();
    void terminate_sdl() const;
    void terminate() const;

public:
    App();
    void execute();
    ~App();
};

#endif //RAYTRACER_APP_H

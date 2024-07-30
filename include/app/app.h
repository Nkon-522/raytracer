#ifndef RAYTRACER_APP_H
#define RAYTRACER_APP_H

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include <iostream>

#include <image/image.h>
#include <memory>

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

class App {
private:
    // Window to be rendered
    SDL_Window* window = nullptr;

    // Window parameters
    const int WINDOW_HEIGHT = 480;
    const int WINDOW_WIDTH = 640;
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

    // ImGui parameters
    ImGuiIO* io = nullptr;
    const ImGuiConfigFlags ImGui_FLAGS = static_cast<ImGuiConfigFlags>(
            ImGuiConfigFlags_NavEnableKeyboard |    // Enable Keyboard Controls
            ImGuiConfigFlags_NavEnableGamepad       // Enable Gamepad Controls
    );

    // Raytracer parameters
    Image image;

    void init_sdl() {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
            throw std::runtime_error(SDL_GetError());
        }

        // From 2.0.18: Enable native IME.
        #ifdef SDL_HINT_IME_SHOW_UI
            SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
        #endif

        // Create window with SDL_Renderer graphics context
        window = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS);
        if (window == nullptr) {
            throw std::runtime_error("Error: SDL_CreateWindow(): " + std::string(SDL_GetError())+"\n");
        }

        renderer = SDL_CreateRenderer(window, -1, RENDERER_FLAGS);
        if (renderer == nullptr) {
            throw std::runtime_error("Error creating SDL_Renderer!");
        }

        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, Image::IMAGE_WIDTH, Image::IMAGE_HEIGHT);
    }

    void init_ImGui() {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext(); (void) io;
        io = &ImGui::GetIO();
        io->ConfigFlags = ImGui_FLAGS;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
        ImGui_ImplSDLRenderer2_Init(renderer);

    }

    static void close_ImGui() {
        // Cleanup
        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void close_sdl() const {
        if (texture != nullptr)
            SDL_DestroyTexture(texture);
        if (renderer != nullptr)
            SDL_DestroyRenderer(renderer);
        if (window != nullptr)
            SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void close() const {
        // Cleanup
        close_ImGui();
        close_sdl();
    }

    void render_ImGui(ImVec4& clear_color) {
        // Start Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
            ImGui::End();
        }

        ImGui::Render();
    }


public:
    void init() {
        // Initialize libraries
        init_sdl();
        init_ImGui();
    }

    void run() {
        SDL_Event event;
        // Our state
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        // Main loop
        bool done = false;
        while (!done) {
            // Handle events
            while (SDL_PollEvent(&event)) {
                ImGui_ImplSDL2_ProcessEvent(&event);
                if (event.type == SDL_QUIT)
                    done = true;
                if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                    done = true;
            }

            // Procedures per loop
            image.render();
            if (SDL_UpdateTexture(texture, nullptr, image.getImg().data(), Image::IMAGE_WIDTH * sizeof(std::uint32_t)) != 0) {
                throw std::runtime_error("Error: SDL_UpdateTexture(): " + std::string(SDL_GetError())+"\n");
            }

            // Setup Render
            render_ImGui(clear_color);
            SDL_RenderSetScale(renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
            SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));

            // Clear Render
            SDL_RenderClear(renderer);

            // Show Render
            SDL_RenderCopy( renderer, texture, NULL, NULL );
            ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
            SDL_RenderPresent(renderer);
        }
    }

    ~App() {
        close();
    }
};

#endif //RAYTRACER_APP_H

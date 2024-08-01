#include "app/app.h"

// INITIALIZATION
void App::init_sdl() {
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

void App::init_ImGui() {
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

void App::init() {
    // Initialize libraries
    init_sdl();
    init_ImGui();
}

// TERMINATION
void App::terminate_ImGui() {
    // Clean up ImGui Context
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void App::terminate_sdl() const {
    // Clean up Texture, Renderer and Window used
    if (texture != nullptr)
        SDL_DestroyTexture(texture);
    if (renderer != nullptr)
        SDL_DestroyRenderer(renderer);
    if (window != nullptr)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

void App::terminate() const {
    // Cleanup
    terminate_ImGui();
    terminate_sdl();
}

// EXECUTION
void App::handle_events() {
    // Handle events
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            run = false;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
            run = false;
    }
}

void App::update() {
    // Update image
    timer.start();
    image.render();
    timer.stop();

    // Update texture
    if (SDL_UpdateTexture(texture, nullptr, image.getImg().data(), Image::IMAGE_WIDTH * sizeof(std::uint32_t)) != 0) {
        throw std::runtime_error("Error: SDL_UpdateTexture(): " + std::string(SDL_GetError())+"\n");
    }
}

void App::set_render_ImGui() {
    // Start Dear ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    {
        ImGui::Begin("Raytracer parameters");

        ImGui::ColorEdit3("clear color", (float*)&clear_color);

        if (ImGui::Button("Render")) {
            update();
        }

        ImGui::Text("Time to preview render %.3f ms", timer.elapsedMilliseconds());
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
        ImGui::End();
    }

    ImGui::Render();
}

void App::render() {
    // Setup Render
    set_render_ImGui();
    SDL_RenderSetScale(renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));

    // Clear Render
    SDL_RenderClear(renderer);

    // Show Render
    SDL_RenderCopy( renderer, texture, nullptr, &dstRect);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

    // Update Screen with Render
    SDL_RenderPresent(renderer);
}



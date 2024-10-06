#include "app/app.h"

//CONSTRUCTOR
App::App():
    window{nullptr},
    WINDOW_WIDTH{1080},
    WINDOW_HEIGHT{620},
    TITLE{"Raytracer"},
    WINDOW_FLAGS{ static_cast<SDL_WindowFlags>(
            SDL_WINDOW_RESIZABLE |
            SDL_WINDOW_ALLOW_HIGHDPI
        )
    },
    renderer{nullptr},
    RENDERER_FLAGS{ static_cast<SDL_RendererFlags>(
            SDL_RENDERER_PRESENTVSYNC |
            SDL_RENDERER_ACCELERATED
        )
    },
    texture{nullptr},
    io{nullptr},
    ImGui_FLAGS{ static_cast<ImGuiConfigFlags>(
             ImGuiConfigFlags_NavEnableKeyboard |    // Enable Keyboard Controls
             ImGuiConfigFlags_NavEnableGamepad       // Enable Gamepad Controls
         )
    },
    run{true},
    timer{},
    event{},
    clear_color{0.45f, 0.55f, 0.60f, 1.00f},
    raytracer{},
    dstRect{0, 0, Image::getImageWidth(), Image::getImageHeight()}
{
    this->init();
}

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

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, Image::getImageWidth(), Image::getImageHeight());
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

// DESTRUCTOR
App::~App() {
    terminate();
}

// EXECUTION
void App::execute() {
    // Main loop
    while (run) {
        handle_events();
        update();
        render();
    }
}

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

void App::raytrace() {
    // Update image
    timer.start();
    raytracer.render_preview();
    timer.stop();

}


void App::update() const {
    // Update texture
    if (SDL_UpdateTexture(texture, nullptr, raytracer.getPreviewImage().data(), static_cast<int>((Image::getImageWidth()) * sizeof(std::uint32_t))) != 0) {
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

        ImGui::ColorEdit3("clear color", reinterpret_cast<float *>(&clear_color));

        ImGui::Text("IMAGE PARAMETERS");
        ImGui::Text("Image width: %d", Image::getImageWidth());
        ImGui::Text("Image height: %d", Image::getImageHeight());

        ImGui::Text(""); ImGui::Text("CAMERA PARAMETERS");
        ImGui::Text("Focus Distance: %.3f", Camera::getFocusDist());
        ImGui::Text("Camera Center: point3(%.3f, %.3f, %.3f)",
                    Camera::getCameraCenter().x(),
                    Camera::getCameraCenter().y(),
                    Camera::getCameraCenter().z());

        ImGui::Text(""); ImGui::Text("VIEWPORT PARAMETERS");
        ImGui::Text("Viewport height: %.3f", Viewport::getViewportHeight());
        ImGui::Text("Viewport width: %.3f", Viewport::getViewportWidth());
        ImGui::Text("Viewport U: vec3(%.3f, %.3f, %.3f)",
                    Viewport::getViewportU().x(),
                    Viewport::getViewportU().y(),
                    Viewport::getViewportU().z());
        ImGui::Text("Viewport V: vec3(%.3f, %.3f, %.3f)",
                    Viewport::getViewportV().x(),
                    Viewport::getViewportV().y(),
                    Viewport::getViewportV().z());
        ImGui::Text("Pixel Delta U: vec3(%.3f, %.3f, %.3f)",
                    Viewport::getPixelDeltaU().x(),
                    Viewport::getPixelDeltaU().y(),
                    Viewport::getPixelDeltaU().z());
        ImGui::Text("Pixel Delta V: vec3(%.3f, %.3f, %.3f)",
                    Viewport::getPixelDeltaV().x(),
                    Viewport::getPixelDeltaV().y(),
                    Viewport::getPixelDeltaV().z());
        ImGui::Text("Viewport Upper Left: point3(%.3f, %.3f, %.3f)",
                    Viewport::getViewportUpperLeft().x(),
                    Viewport::getViewportUpperLeft().y(),
                    Viewport::getViewportUpperLeft().z());
        ImGui::Text("Viewport Pixel 00 Location: point3(%.3f, %.3f, %.3f)",
                    Viewport::getPixel00Location().x(),
                    Viewport::getPixel00Location().y(),
                    Viewport::getPixel00Location().z());

        if (ImGui::Button("Render")) {
            raytrace();
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
    SDL_SetRenderDrawColor(renderer,
        static_cast<Uint8>(clear_color.x * 255),
        static_cast<Uint8>(clear_color.y * 255),
        static_cast<Uint8>(clear_color.z * 255),
        static_cast<Uint8>(clear_color.w * 255)
        );

    // Clear Render
    SDL_RenderClear(renderer);

    // Show Render
    SDL_RenderCopy( renderer, texture, nullptr, &dstRect);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

    // Update Screen with Render
    SDL_RenderPresent(renderer);
}









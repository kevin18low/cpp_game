#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>

// Window to render to
SDL_Window* gWindow{ nullptr };

// Surface contained by the window
SDL_Surface* gScreenSurface{ nullptr };

// Image we will render
SDL_Surface* gHelloWorld{ nullptr };

constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };

// Start SDL and create window
bool init();

// Load media
bool loadMedia();

// Free media and shut down SDL
void close();

int main(int, char*[]) {
    // Final exit code
    int exitCode{ 0 };

    // Initialize
    if(!init()) {
        SDL_Log("Unable to initialize program\n");
        exitCode = 1;
    } else {
        // Load media
        if(!loadMedia()) {
            SDL_Log("Unable to load media\n");
            exitCode = 2;
        } else {
            // Quit flag
            bool quit{false};

            // Event data
            SDL_Event e;
            SDL_zero(e);

            while(quit == false) {
                while(SDL_PollEvent(&e) == true) {
                    if(e.type == SDL_EVENT_QUIT) {
                        quit = true;
                    }
                }

                // Fill the surface white
                SDL_FillSurfaceRect(gScreenSurface, nullptr, SDL_MapSurfaceRGB(gScreenSurface, 0xFF, 0xFF, 0xFF));
            
                // Render image on screen
                SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);

                // Update the surface
                SDL_UpdateWindowSurface(gWindow);
            } 
        }
    }

    close();

    return exitCode;
}

bool init() {
    // Initialization flag
    bool success{ true };

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        success = false;
    } else {
        if (gWindow = SDL_CreateWindow("SDL3 Tutorial: Hello SDL3", kScreenWidth, kScreenHeight, 0); gWindow == nullptr) {
            SDL_Log("Window could not be created: %s", SDL_GetError());
            success = false;
        } else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool loadMedia() {
    // File loading flag
    bool success{true};

    //Load splash image
    std::string imagePath{"media/hello-sdl3.bmp"};
    if(gHelloWorld = SDL_LoadBMP(imagePath.c_str() ); gHelloWorld == nullptr) {
        SDL_Log("Unable to load image: %s", SDL_GetError());
        success = false;
    }

    return success;
}

void close() {
    // Clean up surface
    SDL_DestroySurface(gHelloWorld);
    gHelloWorld = nullptr;
    
    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gScreenSurface = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

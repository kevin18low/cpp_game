#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>


class LTexture {
    public:
        // initializes texture variables
        LTexture();

        // clean up texture variables
        ~LTexture();

        // load texture from disk
        bool loadFromFile(std::string path);

        // clean up texture
        void destroy();

        // draw texture
        void render(float x, float y);

        int getWidth();
        int getHeight();
        bool isLoaded();

    private:
        // texture data
        SDL_Texture* mTexture;

        // texture dimensions
        int mWidth;
        int mHeight;
};

// Window to render to
SDL_Window* gWindow{ nullptr };

// Renderer used to draw to the window
SDL_Renderer* gRenderer{nullptr};

LTexture gPngTexture;

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
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                // render image
                gPngTexture.render(0.f, 0.f);

                // update screen
                SDL_RenderPresent(gRenderer);
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
        if (SDL_CreateWindowAndRenderer("SDL3 Texture Rendering", kScreenWidth, kScreenHeight, 0, &gWindow, &gRenderer) == false) {
            SDL_Log("Window could not be created: %s", SDL_GetError());
            success = false;
        }
    }

    return success;
}

bool loadMedia() {
    // File loading flag
    bool success{true};

    //Load splash image
    std::string imagePath{"media/boat-on-foggy-lake.png"};
    if(gPngTexture.loadFromFile(imagePath) == false) {
        SDL_Log("Unable to load image: %s", SDL_GetError());
        success = false;
    }

    return success;
}

void close() {
    // Clean up surface
    gPngTexture.destroy();
    
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

LTexture::LTexture():
    mTexture{nullptr},
    mWidth{0},
    mHeight{0}
{

}

LTexture::~LTexture() {
    destroy();
}

bool LTexture::loadFromFile(std::string path) {
    destroy();

    if (SDL_Surface* loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr) {
        SDL_Log("Unable to load image %s. SDL_image error: %s\n", path.c_str(), SDL_GetError());
    } else {
        if (mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface); mTexture == nullptr) {
            SDL_Log("Unable to create texture from loaded surface. SDL error: %s\n", SDL_GetError());
        } else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        
        SDL_DestroySurface(loadedSurface);
    }

    return mTexture != nullptr;    
}

void LTexture::destroy() {
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}
void LTexture::render(float x, float y) {
    SDL_FRect dstRect{x, y, static_cast<float>(mWidth), static_cast<float>(mHeight)};

    SDL_RenderTexture(gRenderer, mTexture, nullptr, &dstRect);
}

int LTexture::getWidth() {
    return mWidth;
}

int LTexture::getHeight() {
    return mHeight;
}

bool LTexture::isLoaded() {
    return mTexture != nullptr;
}
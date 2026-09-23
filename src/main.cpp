#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int, char*[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    SDL_Log("SDL initialized!");

    SDL_Quit();
    return 0;
}
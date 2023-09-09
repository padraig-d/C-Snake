#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600
#define DELAY 3000

int main(int argc, char **argv) {

    SDL_Window* window = NULL;

    window = SDL_CreateWindow("Hellowo World",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            WIDTH,
                            HEIGHT,
                            0);

    if (window == NULL) {
        fprintf(stderr, "U suck lol");
        return 1;
    }

    SDL_Delay(DELAY);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;


}
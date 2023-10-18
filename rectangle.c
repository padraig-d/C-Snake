#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600
#define DELAY 3000



int main(int argc, char **argv) {

    int initalised = SDL_Init(SDL_INIT_EVERYTHING);

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

    
    
    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );


    SDL_Rect rectangle = {
        rectangle.x = 10,
        rectangle.y = 10,
        rectangle.w = 32,
        rectangle.h = 32,
    };
    
    SDL_Rect* ptr = &rectangle;
    
    int complete = SDL_RenderDrawRect(renderer, ptr);

    SDL_RenderPresent(renderer);

    SDL_Delay(DELAY);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;


}
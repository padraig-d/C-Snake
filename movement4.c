#include <stdio.h>
#include <SDL2/SDL.h>
#include "functions.h"
#include "macros.h"

int main(int argc, char **argv) {

    int initalised = SDL_Init(SDL_INIT_VIDEO);

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

    prepare(renderer);
    SDL_RenderPresent(renderer);

    SDL_Rect rectangle = {
        .x = 40,
        .y = 40,
        .w = SIZE,
        .h = SIZE,
    };

    SDL_Rect pickup = {
        .x = 200,
        .y = 200,
        .w = SIZE,
        .h = SIZE,
    };
    
    draw(renderer, &rectangle);

    while (1) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            
            int checker = 0;
            if (event.type == SDL_QUIT) { SDL_Quit(); return 0; }
            
            if (event.type == SDL_KEYDOWN) {
                SDL_Keycode current = event.key.keysym.sym;          
            
                while (checker == 0) {
                    moveRectangle(&rectangle, current, window, &checker);
                    checkDirectionChange(&checker); 

                    if (checker == 2) { SDL_Quit(); return 0; }
                    

                    prepare(renderer);
                    draw(renderer, &rectangle);
                    
                    SDL_Delay(DELAY);

                } 
            }

        }

    }

}
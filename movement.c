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
    
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); 
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(DELAY / 4);

    SDL_Rect rectangle = {
        .x = 50,
        .y = 50,
        .w = 50,
        .h = 50,
    };
    
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 0xFF );
    SDL_RenderFillRect( renderer, &rectangle );
    SDL_RenderPresent(renderer);

    SDL_Delay(DELAY / 4);

   
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); 
    SDL_RenderClear(renderer); 

    // ^ those lines prepare the scene to be rerendered, L50 = background colour

    rectangle.x = 100;

    // ^ make changes
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF); // we draw the rectangle
    SDL_RenderFillRect(renderer, &rectangle); // we do rectangle things
    SDL_RenderPresent(renderer);

    // ^ present our changes

    SDL_Delay(DELAY);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;


}
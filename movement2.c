#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600
#define DELAY 3000

void prepare(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); 
    // ^ fills the next line of code with what needs to be rendered.
    SDL_RenderClear(renderer);
    // ^ fills the background with grey, since line 9
}

void draw(SDL_Renderer* renderer, SDL_Rect rect) {
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 0xFF );
    SDL_RenderFillRect( renderer, &rect);
    SDL_RenderPresent(renderer);
}

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

    prepare(renderer);
    SDL_RenderPresent(renderer);

    

    SDL_Delay(DELAY / 4);

    SDL_Rect rectangle = {
        .x = 50,
        .y = 50,
        .w = 32,
        .h = 32,
    };
    
    draw(renderer, rectangle);

    SDL_Delay(DELAY / 4);

    prepare(renderer);


    rectangle.x = 100;
    rectangle.y = 100;

    
    draw(renderer, rectangle);


    // ^ present our changes

    SDL_Delay(DELAY);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;


}
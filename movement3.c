#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600
#define DELAY 3000
#define SIZE 50
#define SPEED 30

void prepare(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); 
    // ^ fills the next line of code with what needs to be rendered.
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    // ^ fills the background with grey, since line 9

}

void draw(SDL_Renderer* renderer, SDL_Rect* rect) {
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 0xFF );
    SDL_RenderFillRect( renderer, rect);
    SDL_RenderPresent(renderer);
}

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
        .x = 50,
        .y = 50,
        .w = SIZE,
        .h = SIZE,
    };
    
    draw(renderer, &rectangle);
    
    while (1) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            
            int checker = 0;
            if (event.type == SDL_QUIT) { SDL_Quit(); break; }
            
            if (event.type == SDL_KEYDOWN) {
                SDL_Keycode current = event.key.keysym.sym;          
            
                while (checker == 0) {
                    
                    SDL_Delay(100);            
                    switch (current) {                      
                        case SDLK_q: SDL_DestroyWindow(window); SDL_Quit(); return 0;
                        case SDLK_RIGHT: rectangle.x += SPEED; break;
                        case SDLK_LEFT: rectangle.x -= SPEED; break;
                        case SDLK_UP: rectangle.y -= SPEED; break;
                        case SDLK_DOWN: rectangle.y += SPEED; break;
                    }
                    
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_KEYDOWN) { // TODO: Only change checker if direction key
                            SDL_Log("Direction Change");
                            SDL_PushEvent(&event); 
                            checker = 1;
                        }
                    }

                    prepare(renderer);
                    draw(renderer, &rectangle);

                } 
            }

        }

    }

}
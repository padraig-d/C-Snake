#include <stdio.h>
#include <SDL2/SDL.h>
#include "macros.h"

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

void moveRectangle(SDL_Rect* rectangle, SDL_KeyCode current, SDL_Window* window) {
     
    switch (current) {                      
        case SDLK_q: SDL_DestroyWindow(window); SDL_Quit();
        case SDLK_RIGHT: rectangle->x += SPEED; break;
        case SDLK_LEFT: rectangle->x -= SPEED; break;
        case SDLK_UP: rectangle->y -= SPEED; break;
        case SDLK_DOWN: rectangle->y += SPEED; break;
    }
}

int checkDirectionChange(int* checker) {
    
    SDL_Event func_event;
    while(SDL_PollEvent(&func_event)) {
        
        //if (func_event.type == SDL_QUIT) { SDL_Quit(); break; }
        if (func_event.type == SDL_KEYDOWN) {
            SDL_PushEvent(&func_event);
            *checker = 1;
        }
        else {
            *checker = 0;
        }
    }
}
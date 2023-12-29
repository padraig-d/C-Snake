#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "functions.h"
#include "macros.h"

int main(int argc, char **argv) {

    int initalised = SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = NULL;
    window = SDL_CreateWindow("Python",
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

    Global global = {
        .check = 0,
        .quit = 0,
    };

    SDL_Rect startRect = {
        .x = 40,
        .y = 40,
        .w = SIZE,
        .h = SIZE,
    };

    Snake snakeHead = {
        .snake = startRect,
        .prev = NULL,
    };

    SDL_Rect pickup = {
        .x = -60,
        .y = -60,
        .w = SIZE,
        .h = SIZE,
    };

    while (!global.quit) {

        SDL_Event event;
        while(SDL_PollEvent(&event)) { 

            if (event.type == SDL_QUIT) { global.quit = 1; }
            if (event.key.keysym.sym == SDLK_q) { global.quit = 1; }
            
            global.check = 0;

            if (event.type == SDL_KEYDOWN) {
                SDL_Keycode current = event.key.keysym.sym;          
                
                while (!global.check && global.quit == 0) {
                    // movement code
                    moveSnake(&snakeHead, current, window, &global);
                    checkDirectionChange(&global); 

                    // game logic
                    Spawner(&pickup, &snakeHead);
                    Eat(&pickup, &snakeHead);
                    BorderCheck(&snakeHead, &global);
                    CollisonCheck(&snakeHead, &global);

                    // rendering code
                    prepare(renderer);
                    draw(renderer, &snakeHead, &pickup);
                    SDL_Delay(DELAY);
                    
                } 
            }
        }
    }

    // quitting logic

    if (global.check == 1 && global.quit == 1) {
        SDL_Delay(1000);
        SDL_Quit();
        return 0;
    }
    else if (global.quit == 1) {
        SDL_Quit();
        return 0;
    }

}
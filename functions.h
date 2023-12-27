#include <stdio.h>
#include <SDL2/SDL.h>
#include "macros.h"

typedef struct Snake Snake;

struct Snake {
    SDL_Rect* snake;
    Snake* prev;
};

void addPiece(Snake* head) {

    Snake* p = head;
    
    while (p->prev != NULL) {
        p = p->prev;
    }

    p->prev = (Snake*)calloc(1, sizeof(Snake));
    p = p->prev;

    SDL_Rect newRect = {
        .x = 100,
        .y = 100,
        .w = SIZE,
        .h = SIZE,
    };

    p->prev = NULL;
    p->snake = &newRect;

    // p = head;           
    // while (p->prev != NULL) {            DEBUG CODE
    //     p = p->prev;                     THIS CODE WORKS 100 PERCENT.
    //     SDL_Log("Success!");             IT WILL OUTPUT 1 SUCCESS AND PRINT 100.

    // }                                    IT ALSO WORKS IN MAIN. IT WILL OUTPUT 100. DOESNT WORK IN MAIN LOOP.

    // printf("%d", p->snake->x);

}


void prepare(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); 
    // ^ fills the next line of code with what needs to be rendered.
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    // ^ fills the background with grey, since line 9

}

void draw(SDL_Renderer* renderer, Snake* head, SDL_Rect* pickup) {
    
    Snake* p = head;
    //SDL_Log("%d", p->snake->x);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 0xFF );
    SDL_RenderFillRect( renderer, p->snake);
    p = p->prev;
    //SDL_Log("%d", p->snake->x);
    SDL_RenderFillRect( renderer, p->snake);
    SDL_RenderPresent(renderer);


    
    SDL_RenderFillRect( renderer, pickup);
    
}

int moveSnake(Snake* head, SDL_KeyCode current, SDL_Window* window, int* checker) {
     
    Snake* p = head;
    int currentX = head->snake->x;
    int currentY = head->snake->y;
    int tempX, tempY;

    switch (current) {                      
        case SDLK_q: SDL_DestroyWindow(window); *checker = 2; break;
        case SDLK_RIGHT: head->snake->x += SPEED; break;
        case SDLK_LEFT: head->snake->x -= SPEED; break;
        case SDLK_UP: head->snake->y -= SPEED; break;
        case SDLK_DOWN: head->snake->y += SPEED; break;
    }

    
    // if (head->prev != NULL) {
    //     Snake* p = head->prev;
    //     while(p != NULL) {
    //         tempX = p->snake->x;
    //         tempY = p->snake->y;

    //         p->snake->x = currentX;
    //         p->snake->y = currentY;

    //         tempX = currentX;
    //         tempY = currentY;

    //         p = p->prev;

    //     }
    // }
    
}

void checkDirectionChange(int* checker) { // might be something to do with this function...
    
    SDL_Event func_event;
    while(SDL_PollEvent(&func_event)) {
        
        if (func_event.type == SDL_QUIT) { *checker = 2; break; }
        
        if (func_event.type == SDL_KEYDOWN) {
            
            SDL_Keycode current = func_event.key.keysym.sym;
            
            if (current == SDLK_q) { *checker = 2; break; }
            else if (current == SDLK_RIGHT || current == SDLK_LEFT ||  current == SDLK_UP || current == SDLK_DOWN)  {
                SDL_PushEvent(&func_event);
                *checker = 1;
                break;
            }
        }
    }
}

void tester(Snake* head) {

    Snake* p = head;
    while (p != NULL) {
        SDL_Log("%d", p->snake->x);
        p = p->prev;
    }
}




// BUG-FIXES
// 1. get the functions to return 0 when SDL_Quit()
//    --- do it nicer than the hack job of checking for checker = 2 lol

//

// if (current == SDLK_RIGHT || current == SDLK_LEFT ||  current == SDLK_UP || current == SDLK_DOWN) 

// TODO
// 1. Snake linked list.
// 2. Pickup and collision.
// 3. Border checking. 


// SITREP 8AM 27/DEC
// p->prev X Y goes apeshit within the SDL_PollEvent() while loop...
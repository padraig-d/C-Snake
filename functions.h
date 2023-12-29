#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "macros.h"

typedef struct Snake Snake;

struct Snake {
    SDL_Rect snake;
    Snake* prev;
};

void addPiece(Snake* snakeHead) {

    Snake* p = snakeHead;
    
    while (p->prev != NULL) {
        p = p->prev;
    }

    p->prev = (Snake*)calloc(1, sizeof(Snake));
    p = p->prev;

    SDL_Rect newRect = {
        .x = -100,
        .y = -100,
        .w = SIZE,
        .h = SIZE,
    };

    p->prev = NULL;
    p->snake = newRect;

}


void prepare(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); 
    // ^ fills the next line of code with what needs to be rendered.
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    // ^ fills the background with grey

}

void draw(SDL_Renderer* renderer, Snake* head, SDL_Rect* pickup) {
    
    Snake* p = head;
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 0xFF );
    
    while (p != NULL) {
        SDL_RenderFillRect( renderer, &(p->snake));
        p = p->prev;
    }
    
    SDL_RenderFillRect(renderer, pickup);
    SDL_RenderPresent(renderer);
    
}

int moveSnake(Snake* head, SDL_KeyCode current, SDL_Window* window, int* checker) {
     
    Snake* p = head;
    int currentX, currentY;
    int tempX, tempY;
    
    currentX= head->snake.x;
    currentY = head->snake.y;


    switch (current) {                      
        case SDLK_q: SDL_DestroyWindow(window); *checker = 2; break;
        case SDLK_RIGHT: head->snake.x += SPEED; break;
        case SDLK_LEFT: head->snake.x -= SPEED; break;
        case SDLK_UP: head->snake.y -= SPEED; break;
        case SDLK_DOWN: head->snake.y += SPEED; break;
    }

    p = head->prev;
    
    while(p != NULL) {
        tempX = p->snake.x;
        tempY = p->snake.y;

        p->snake.x = currentX;
        p->snake.y = currentY;

        currentX = tempX;
        currentY = tempY;

        p = p->prev;

    }
    
    
}

void checkDirectionChange(int* checker) { 
    SDL_Event func_event;
    while(SDL_PollEvent(&func_event)) {
        
        if (func_event.type == SDL_QUIT) { *checker = 2; break; }
        
        if (func_event.type == SDL_KEYDOWN && func_event.key.repeat == 0) {
            
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

void Spawner(SDL_Rect* pickup, Snake* snakeHead) {

    time_t t;
    srand((unsigned) time(&t));
    while (pickup->x == -60) {
        int x = (rand() % ((WIDTH / 20)));
        x = x * SIZE;
        int y = (rand() % ((HEIGHT / 20)));
        y = y * SIZE;

        if ((x != snakeHead->snake.x) && (y != snakeHead->snake.y)) {
            pickup->x = x;
            pickup->y = y;
        }
    }

}

void Eat(SDL_Rect* pickup, Snake* snakeHead) {

    if ((pickup->x == snakeHead->snake.x) && (pickup->y == snakeHead->snake.y)) {
        addPiece(snakeHead);
        pickup->x = -60;
        pickup->y = -60;
    }

}

void CollisonCheck(Snake* snakeHead, int* checker) {
    Snake* p = snakeHead->prev;
    int x = snakeHead->snake.x;
    int y = snakeHead->snake.y;

    while (p != NULL) { 
        
        if ((p->snake.x == x) && (p->snake.y == y)) {
            SDL_Log("Ate yourself!");
            *checker = 2;
            break; 
        }

        p = p->prev;
        
    }

}

void BorderCheck(Snake* snakeHead, int* checker) {
    if (snakeHead->snake.x == WIDTH || snakeHead->snake.y == HEIGHT || snakeHead->snake.x == -20 || snakeHead->snake.y == -20 ) {
        SDL_Log("Ran into wall!");
        *checker = 2;
    }
}

void Tester(Snake* head) {
    
    int i = 0;
    Snake* p = head;
    while (p != NULL) {
        SDL_Log("%d", i);
        SDL_Log("%d", p->snake.y);
        p = p->prev;
        i += 1;
    }
}

int Quitter() {
    // another day
}




// BUG-FIXES
// 1. get the functions to return 0 when SDL_Quit()
//    --- do it nicer than the hack job of checking for checker = 2 lol

// TODO
// 2. Pickup and collision.
// 3. Border checking. 
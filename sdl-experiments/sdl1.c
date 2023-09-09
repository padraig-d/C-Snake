#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not be initialized %c",
        *SDL_GetError());
    }
    else {
        printf("SDL is working");
    }
}

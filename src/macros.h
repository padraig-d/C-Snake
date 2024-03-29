#define WIDTH 800
#define HEIGHT 600
#define DELAY 50
#define SIZE 20
#define SPEED 20

typedef struct Snake Snake;

struct Snake {      // Snake stored as a linked list.
    SDL_Rect snake;
    Snake* prev;
};

typedef struct Global Global;

struct Global {   // Global flags
    int check;
    int quit;
};


// FUNCTIONS

void addPiece(Snake* snakeHead);
void prepare(SDL_Renderer* renderer);
void draw(SDL_Renderer* renderer, Snake* head, SDL_Rect* pickup);
int moveSnake(Snake* head, SDL_KeyCode current, SDL_Window* window, Global* global);
void checkDirectionChange(Global* global);
void Spawner(SDL_Rect* pickup, Snake* snakeHead);
void Eat(SDL_Rect* pickup, Snake* snakeHead);
void CollisonCheck(Snake* snakeHead, Global* global);
void BorderCheck(Snake* snakeHead, Global* global);
void Tester(Snake* head);






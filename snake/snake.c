#include <SDL2/SDL.h>
#include <time.h>

static SDL_Window* window;
static SDL_Renderer* renderer;

static unsigned int SCORE;

typedef enum {
    NORTH, EAST, SOUTH, WEST
}DIRS;

typedef struct{
    char x, y;
}snake_seg_t;

typedef struct{
    unsigned short growth;
    DIRS current_dir;
    snake_seg_t segs[255];
}snake_t;

//bone apple teeth
typedef struct{
    char x, y;
}apple_t;

int main(int argc, char *argv[]){
    srand(time(NULL));
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        fprintf(stderr, "Could not initialize SDL2!\n%s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if(window == NULL){
        fprintf(stderr, "Could not initialize SDL2's window!\n%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL){
        fprintf(stderr, "Could not initialize SDL2's renderer!\n%s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_RenderSetLogicalSize(renderer, 40, 30);

    int run_switch = 0;
    SDL_Event e;

    snake_t snake;
    snake.current_dir = WEST;
    snake.growth = 3;
    snake.segs[0] = (snake_seg_t){20, 15};

    apple_t appel;
    appel.x = (rand() % (39 - 1 + 1)) + 1; 
    appel.y = (rand() % (29 - 1 + 1)) + 1; 

    while(!run_switch){
        while(SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT) {
			   run_switch = 1;
		    }
            else if (e.type == SDL_KEYDOWN) {
			    switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    run_switch = 1;
                    break;
                case SDLK_UP:
                    if(snake.current_dir != SOUTH)
                        snake.current_dir = NORTH;
                    break;
                case SDLK_DOWN:
                    if(snake.current_dir != NORTH)
                        snake.current_dir = SOUTH;
                    break;
                case SDLK_LEFT:
                    if(snake.current_dir != EAST)
                        snake.current_dir = WEST;
                    break;
                case SDLK_RIGHT:
                    if(snake.current_dir != WEST)
                        snake.current_dir = EAST;
                    break;
                default:
                    break;
                }
		    }
        }

        for(unsigned char snek = snake.growth; snek > 0; snek--){
            snake.segs[snek].x = snake.segs[snek - 1].x;
            snake.segs[snek].y = snake.segs[snek - 1].y;
        }

        switch(snake.current_dir){
            case NORTH:
                snake.segs[0].y -= 1;
                break;
            case SOUTH:
                snake.segs[0].y += 1;
                break;
            case WEST:
                snake.segs[0].x -= 1;
                break;
            case EAST:
                snake.segs[0].x += 1;
                break;
            default:
                break;
        }

        if(snake.segs[0].x == appel.x && snake.segs[0].y == appel.y){
            snake.growth++;
            appel.x = (rand() % (39 - 1 + 1)) + 1; 
            appel.y = (rand() % (29 - 1 + 1)) + 1; 
        }
        
        if(snake.segs[0].x > 40)
            snake.segs[0].x = 0;
        if(snake.segs[0].y > 30)
            snake.segs[0].y = 0;
        if(snake.segs[0].x < 0)
            snake.segs[0].x = 40;
        if(snake.segs[0].y < 0)
            snake.segs[0].y = 30;

        for(unsigned char n = 1; n < snake.growth; n++){
            if(snake.segs[0].x == snake.segs[n].x && snake.segs[0].y == snake.segs[n].y)
                snake.growth = n;
        }

        SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
        SDL_Rect rect = {0, 0, 40, 30};
        SDL_RenderDrawRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, 64, 128, 64, 255);
        
        SDL_Rect snake_rect; 

        for(unsigned int grow = 0; grow < snake.growth; grow++){
            snake_rect.x = snake.segs[grow].x;
            snake_rect.y = snake.segs[grow].y;
            snake_rect.w = snake_rect.h = 1;
            SDL_RenderFillRect(renderer, &snake_rect);
        }

        SDL_SetRenderDrawColor(renderer, 128, 64, 64, 255);
        rect = (SDL_Rect){appel.x, appel.y, 1, 1};
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
        SDL_Delay(120 - ((snake.growth % 5) * 2));
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
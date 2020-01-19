#include <SDL2/SDL.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static SDL_Window* window;
static SDL_Renderer* renderer;

static SDL_Texture* disc_rep;
static SDL_Rect disc_rect = {0, 0, 16, 16};

typedef enum{NONE, PLY1, PLY2}STATE;

typedef struct{
    Uint8 pos_x, pos_y;
    STATE st;
}piece_t;

typedef struct{
    piece_t table[6][7];
    SDL_Color player1_col, player2_col;
    STATE game_end;
}game_t;

int main(int argc, char** argv){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        fprintf(stderr, "Error starting SDL2!\n%s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Connect 4 - Connect 'em all!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if(window == NULL){
        fprintf(stderr,"Error starting SDL2's window!\n%s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL){
        fprintf(stderr, "Error starting SDL2's renderer!\n%s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_RenderSetLogicalSize(renderer, 160, 120);

    SDL_Event e;
    Uint8 switcherer = 0;

    //The game, the legend.
    game_t the_game;
    the_game.player1_col = (SDL_Color){255, 255, 0, 255};
    the_game.player2_col = (SDL_Color){255, 0, 0, 255};
    the_game.game_end = NONE;

    int disc_w, disc_h;
    Uint8* disc_data = stbi_load("coin.png", &disc_w, &disc_h, NULL, 4);
    SDL_Surface* temp_surf = SDL_CreateRGBSurfaceFrom((void*)disc_data, disc_w, disc_h, 32, 4 * disc_w, 
                                                            0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    if (temp_surf == NULL) {
            SDL_Log("Creating surface failed: %s", SDL_GetError());
            return 0;
    }
    else{
        disc_rep = SDL_CreateTextureFromSurface(renderer, temp_surf);
        if (disc_rep == NULL) {
            SDL_Log("Creating texture failed: %s", SDL_GetError());
            SDL_FreeSurface(temp_surf);
            return 0;
        }
        SDL_FreeSurface(temp_surf);
    }

    stbi_image_free(disc_data);

    while(!switcherer){
        while(SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT) {
			   switcherer = 1;
		    }
            else if (e.type == SDL_KEYDOWN) {
			    switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    switcherer = 1;
                    break;
                default:
                    break;
                }
		    }
        }
        SDL_SetRenderDrawColor(renderer, 64, 64, 96, 255);
        SDL_RenderClear(renderer);

        SDL_SetTextureColorMod(disc_rep, the_game.player1_col.r, the_game.player1_col.g, the_game.player1_col.b);
        SDL_RenderCopy(renderer, disc_rep, NULL, &disc_rect);

        SDL_Rect other_disc = {0, 16, 16, 16};

        SDL_SetTextureColorMod(disc_rep, the_game.player2_col.r, the_game.player2_col.g, the_game.player2_col.b);
        SDL_RenderCopy(renderer, disc_rep, NULL, &other_disc);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
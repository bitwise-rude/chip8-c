#include "graphics.h"

void initialize_window(Screen *screen){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        screen->win = NULL;
        return;
    }

    screen->win = SDL_CreateWindow(TITLE,
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    WIDTH,HEIGHT,
                                    SDL_WINDOW_SHOWN);

    if(!screen->win){
        screen->win=NULL;
        SDL_Quit();
         return;
    }
    
    screen->ren =SDL_CreateRenderer(screen->win, -1, SDL_RENDERER_ACCELERATED);

    if(!screen->ren){
        screen->win=NULL; 
        SDL_DestroyWindow(screen->win);
        SDL_Quit();
        return;
    }
}
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
        SDL_Quit();
        screen->win=NULL;
         return;
    }
    
    screen->ren =SDL_CreateRenderer(screen->win, -1, SDL_RENDERER_ACCELERATED);

    if(!screen->ren){
        SDL_DestroyWindow(screen->win);
        SDL_Quit();
        screen->win=NULL; 
        return;
    }
}

// TODO: FIX THIS LATER
void delete_everything(Screen *scr){
    SDL_DestroyRenderer(scr->ren);
    SDL_DestroyWindow(scr->win);
    SDL_Quit();
}

int step_graphics(Screen *scr){
    SDL_SetRenderDrawColor(scr->ren, 0, 100, 255, 255);
    if(SDL_PollEvent(&scr->e)){
        if(scr->e.type == SDL_QUIT){
                delete_everything(scr);
                return -1;
        }
    }
    SDL_RenderClear(scr->ren);
    SDL_RenderPresent(scr->ren);
    return 1;
}


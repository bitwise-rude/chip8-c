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

int draw_byte(Screen *scr, u8 byte_to_draw, int x, int y) {
    int collision = 0;
    for (int bit = 0; bit < 8; bit++) {
        int px = (x + bit) % 64;
        int py = (y) % 32;

        uint8_t pixel = (byte_to_draw & (0x80 >> bit)) != 0;

        if (pixel) {
            if (scr->display_grid[px][py] == 1)
                collision = 1;

            scr->display_grid[px][py] ^= 1;
        }
    }
    return collision;
}

void clear_matrix(Screen *scr){
    for (int i = 0; i < D_HEIGHT; i++) {
        for (int j = 0; j < D_WIDTH; j++) {
            scr->display_grid[i][j] = 0;
        }
    draw_matrix(scr);
}

}

void draw_matrix(Screen *scr)
{
    // SDL_SetRenderDrawColor(scr->ren, 0, 0, 0, 255); 
    // SDL_RenderClear(scr->ren);

    SDL_SetRenderDrawColor(scr->ren, 0, 255, 0, 255); 

    for (int y = 0; y < D_HEIGHT; y++) {
            for (int x = 0; x < D_WIDTH; x++) {
                if (scr->display_grid[x][y]==1) {
                    SDL_Rect rect = { x * ENLARGEMENT, y * ENLARGEMENT, ENLARGEMENT, ENLARGEMENT };
                    SDL_RenderFillRect(scr->ren, &rect);
                }
            }
        }
        SDL_RenderPresent(scr->ren);  
}

int step_graphics(Screen *scr){
    if(SDL_PollEvent(&scr->e)){
        if(scr->e.type == SDL_QUIT){
                return -1;
        }
    }

    return 1;
}


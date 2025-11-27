#include <SDL2/SDL.h>

#define TITLE "CHIP8"

#define ENLARGEMENT 2
#define WIDTH (64*ENLARGEMENT)
#define HEIGHT (32 * ENLARGEMENT)


typedef struct Screen{
    SDL_Window *win;
    SDL_Renderer *ren;

}Screen;

void initialize_window(Screen *screen);
#include <SDL2/SDL.h>
#include <stdint.h>

#define TITLE "CHIP8"

#define ENLARGEMENT 15

#define D_WIDTH 64
#define D_HEIGHT 32

#define WIDTH (D_WIDTH*ENLARGEMENT)
#define HEIGHT (D_HEIGHT * ENLARGEMENT)

typedef uint8_t u8;


typedef struct Screen{
    SDL_Window *win;
    SDL_Renderer *ren;
    SDL_Event e;

    u8 display_grid[D_WIDTH][D_HEIGHT];

}Screen;

void initialize_window(Screen *screen);
int step_graphics(Screen *screen);
void draw_matrix(Screen *screen);
int draw_byte(Screen *scr, u8 byte_to_draw,int x,int y);
void delete_everything(Screen *scr);
void clear_matrix(Screen *scr);
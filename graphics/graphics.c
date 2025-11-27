#include "graphics.h"

SDL_Keycode chip8_keymap[16] = {
    SDLK_x,   //0
    SDLK_1,  // 1
    SDLK_2,  // 2
    SDLK_3,  // 3
    SDLK_q,  // 4
    SDLK_w,  // 5
    SDLK_e,  // 6
    SDLK_a,  // 7
    SDLK_s,  // 8
    SDLK_d,  // 9
    SDLK_z,  // A
    SDLK_c,  // B
    SDLK_4,  // C
    SDLK_r,  // D
    SDLK_f,  // E
    SDLK_v   // F
};

void square_wave_playback(void *userdata, Uint8 *stream, int len){

    static int phase = 0;
    const int sample_rate = 44100;
    const int half_period = sample_rate / (TONE * 2);

    for (int i = 0; i < len; i++) {
        // high or low depending on phase
        stream[i] = (phase < half_period) ? 255 : 0;

        phase++;
        if (phase >= half_period * 2) {
            phase = 0;
        }
    }

}

void initialize_window(Screen *screen){
    // initialize key states
    for (int i =0; i<16; i++){
        screen->key_states[i] = 0;
    }

    // initialize audio
    SDL_zero(screen->want);
    screen->want.freq = 44100;           // sample rate
    screen->want.format = AUDIO_U8;      // unsigned 8-bit samples
    screen->want.channels = 1;           // mono
    screen->want.samples = 1024;         // buffer size
    screen->want.callback = square_wave_playback;

    SDL_OpenAudio(&screen->want, &screen->have);


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
            scr->display_grid[j][i] = 0;
        }
    draw_matrix(scr);
}

}

void draw_matrix(Screen *scr)
{
    SDL_SetRenderDrawColor(scr->ren, 0, 0, 0, 255); 
    SDL_RenderClear(scr->ren);

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
        else if (scr->e.type == SDL_KEYDOWN){
            for (int i=0; i<16; i++){
                if (scr->e.key.keysym.sym == chip8_keymap[i]){
                        scr->key_states[i] = 1;
                        break;
                }
            }
        }
        else if (scr->e.type == SDL_KEYUP){
            for (int i=0; i<16; i++){
                if (scr->e.key.keysym.sym == chip8_keymap[i]){
                        scr->key_states[i] = 0;
                        break;
                }
            }
        }
    }

    return 1;
}


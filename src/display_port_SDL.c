#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "display_port.h"

static struct{
    SDL_Window          *d_window;
    SDL_Renderer        *d_renderer;
    SDL_Texture         *d_texture;
    SDL_bool             d_ready;
} d_port_SDL = { 0 };

static void d_init_SDL_window(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Window *window = SDL_CreateWindow("CHIP-8",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          DISP_WIDTH  * SCREEN_SCALE,
                                          DISP_HEIGHT * SCREEN_SCALE,
                                          SDL_WINDOW_RESIZABLE);

    if (window == NULL){
        fprintf(stderr, "Unable to create window: %s", SDL_GetError());
        return;
    }

    d_port_SDL.d_window = window;
}

static void d_init_SDL_renderer(){
    if(d_port_SDL.d_window == NULL){
        fprintf(stderr, "Window not initialized\n");
        return;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(d_port_SDL.d_window,
                                                -1,
                                                SDL_RENDERER_ACCELERATED );
    
    if(renderer == NULL){
        fprintf(stderr, "Unable to create renderer: %s", SDL_GetError());
        return;
    }

    SDL_RenderSetLogicalSize(renderer, DISP_WIDTH, DISP_HEIGHT);

    d_port_SDL.d_renderer = renderer;
}

static void d_init_SDL_texture(){
    if(d_port_SDL.d_window == NULL || d_port_SDL.d_renderer == NULL){
        fprintf(stderr, "Window or renderer not initialized\n");
        return;
    }

    SDL_Texture *texture = SDL_CreateTexture(d_port_SDL.d_renderer,
                                             SDL_PIXELFORMAT_RGBA32,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             DISP_WIDTH,
                                             DISP_HEIGHT);

    if(texture == NULL){
        fprintf(stderr, "Unable to create texture: %s", SDL_GetError());
        return;
    }

    d_port_SDL.d_texture = texture;
}

static inline bool d_init_SDL_check_if_ready(){
    if(d_port_SDL.d_window && d_port_SDL.d_renderer && d_port_SDL.d_texture){
        if(!d_port_SDL.d_ready) d_port_SDL.d_ready = true;
    }else{
        d_port_SDL.d_ready = false;
    }
    return d_port_SDL.d_ready;
}

static bool d_draw_SDL_fill_display(uint32_t color){
    int ret;
    ret = SDL_SetRenderDrawColor(d_port_SDL.d_renderer, 
                                 COLOR_R(color),
                                 COLOR_G(color),
                                 COLOR_B(color),
                                 COLOR_A(color)
                        );
    if(ret != 0){
        fprintf(stderr, "Unable to set renderer color: %s", SDL_GetError());
        return false;
    }
    
    ret = SDL_RenderClear(d_port_SDL.d_renderer);
    if(ret != 0){
        fprintf(stderr, "Unable to draw to window: %s", SDL_GetError());
        return false;
    }

    return true;
}

void display_port_init(display *display_instance){
    if(!display_instance){
        fprintf(stderr, "Empty display instance: %s", SDL_GetError());
        display_instance->d_state = D_FAILURE;
        return;
    }

    d_init_SDL_window();
    d_init_SDL_renderer();
    d_init_SDL_texture();

    if(!d_init_SDL_check_if_ready()){
        fprintf(stderr, "Unable to initialize display: %s", SDL_GetError());
        display_instance->d_state = D_FAILURE;
        return;
    }

    display_port_clear(display_instance);
}

void display_port_clear(display *display_instance){
    if(!display_instance){
        fprintf(stderr, "Empty display instance: %s", SDL_GetError());
        display_instance->d_state = D_FAILURE;
        return;
    }
    
    if(!d_init_SDL_check_if_ready()){
        fprintf(stderr, "Window is not ready\n");
        display_instance->d_state = D_FAILURE;
        return;
    }

    bool ret = d_draw_SDL_fill_display(BG_COLOR);
    if(ret){
        SDL_RenderPresent(d_port_SDL.d_renderer);
        display_instance->d_state = D_ON;
    }else{
        display_instance->d_state = D_FAILURE;
    }
}

void display_port_update(display *display_instance){
    if(!display_instance){
        fprintf(stderr, "Empty display instance: %s", SDL_GetError());
        display_instance->d_state = D_FAILURE;
        return;
    }

    if(!d_init_SDL_check_if_ready()){
        fprintf(stderr, "Window is not ready\n");
        display_instance->d_state = D_FAILURE;
        return;
    }

    int pitch = 0;
    void *texture_pixels = NULL;

    if(SDL_LockTexture(d_port_SDL.d_texture, NULL, &texture_pixels, &pitch) != 0){
        fprintf(stderr, "Unable to lock texture: %s", SDL_GetError());
        return;
    }

    memcpy(texture_pixels, (uint8_t *)display_instance->d_framebuffer, pitch * DISP_HEIGHT);
    SDL_UnlockTexture(d_port_SDL.d_texture);
    SDL_RenderCopy(d_port_SDL.d_renderer, d_port_SDL.d_texture, NULL, NULL);
    SDL_RenderPresent(d_port_SDL.d_renderer);
    display_instance->d_state = D_ON;
}

void display_port_exit(display *display_instance){
    if(!display_instance){
        fprintf(stderr, "Empty display instance: %s", SDL_GetError());
        display_instance->d_state = D_FAILURE;
        return;
    }

    if(!d_init_SDL_check_if_ready()){
        fprintf(stderr, "Window is not ready\n");
        display_instance->d_state = D_FAILURE;
        return;
    }

    d_port_SDL.d_ready = false;
    display_instance->d_state = D_OFF;
    SDL_DestroyTexture(d_port_SDL.d_texture);
    SDL_DestroyRenderer(d_port_SDL.d_renderer);
    SDL_DestroyWindow(d_port_SDL.d_window);
    SDL_Quit();
}
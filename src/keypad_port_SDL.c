#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include "keypad_port.h"

// Remapping they keyboard buttons to keypad keys
// First row
#define KP_1 SDLK_1
#define KP_2 SDLK_2
#define KP_3 SDLK_3
#define KP_C SDLK_4
// Second row
#define KP_4 SDLK_q
#define KP_5 SDLK_w
#define KP_6 SDLK_e
#define KP_D SDLK_r
// Third row
#define KP_7 SDLK_a
#define KP_8 SDLK_s
#define KP_9 SDLK_d
#define KP_E SDLK_f
// Forth row
#define KP_A SDLK_z
#define KP_0 SDLK_x
#define KP_B SDLK_c
#define KP_F SDLK_v

static struct{
    SDL_Event            k_event;
    SDL_bool             k_ready;
} k_port_SDL = { 0 };

static inline void k_init_SDL_input(void){
    if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0){
        fprintf(stderr, "SDL could not initialize event subsystem! SDL_Error: %s\n", SDL_GetError());
        k_port_SDL.k_ready = false;
        return;
    }

    k_port_SDL.k_ready = true;
}

static inline bool k_poll_key_event(void){
    if(!k_port_SDL.k_ready){
        fprintf(stderr, "Event subsystem not initialized\n");
        return false;
    }
    int8_t ret = SDL_PollEvent(NULL); // Check if there's an event in the event queue
    if(ret == 1){
        SDL_PollEvent(&k_port_SDL.k_event);
        return 1;
    }
    return 0;
}

static inline SDL_Keycode k_get_keycode(keypad *keypad_instance){
    static bool hold = false;
    static SDL_Keycode last_key = 0;
    static keypad_state last_state = K_KEY_RELEASED;

    if(hold){
        keypad_instance->k_state = K_KEY_HELD;
    }

    if(!hold && k_port_SDL.k_event.type == SDL_KEYDOWN){
        puts("down");
        keypad_instance->k_state = K_KEY_PRESSED;
        hold = true;
        last_key = k_port_SDL.k_event.key.keysym.sym;
        last_state = K_KEY_PRESSED;
        return k_port_SDL.k_event.key.keysym.sym;
    }else if(k_port_SDL.k_event.type == SDL_KEYUP){
        puts("up");
        hold = false;
        keypad_instance->k_state = K_KEY_RELEASED;
        last_state = K_KEY_RELEASED;
        return (SDL_Keycode)0;
    }
    puts((last_state == K_KEY_PRESSED) ? "down" : "up");
    return (last_state == K_KEY_PRESSED) ? last_key : 0;
}

void keypad_port_init(keypad *keypad_instance){
    if(!keypad_instance){
        fprintf(stderr, "Empty keypad instance: %s", SDL_GetError());
        keypad_instance->k_state = K_FAILURE;
        return;
    }

    k_init_SDL_input();
    keypad_instance->k_active_key = 0;
    keypad_instance->k_state = K_KEY_RELEASED;
}

void keypad_port_update(keypad *keypad_instance){
    if(!keypad_instance){
        fprintf(stderr, "Empty keypad instance: %s", SDL_GetError());
        keypad_instance->k_state = K_FAILURE;
        return;
    }

    if(!k_poll_key_event()){
        //keypad_instance->k_state = K_KEY_RELEASED;
        return;
    }

    SDL_Keycode current_key = k_get_keycode(keypad_instance);
    if(current_key <= (SDL_Keycode)0){
        //printf("I'm released here %d\n", current_key);
        keypad_instance->k_state = K_KEY_RELEASED;
        return;
    }

    switch(current_key){
    case KP_0:
        keypad_instance->k_active_key = K_0;
        break;
    case KP_1:
        keypad_instance->k_active_key = K_1;
        break;
    case KP_2:
        keypad_instance->k_active_key = K_2;
        break;
    case KP_3:
        keypad_instance->k_active_key = K_3;
        break;
    case KP_4:
        keypad_instance->k_active_key = K_4;
        break;
    case KP_5:
        keypad_instance->k_active_key = K_5;
        break;
    case KP_6:
        keypad_instance->k_active_key = K_6;
        break;
    case KP_7:
        keypad_instance->k_active_key = K_7;
        break;
    case KP_8:
        keypad_instance->k_active_key = K_8;
        break;
    case KP_9:
        keypad_instance->k_active_key = K_9;
        break;
    case KP_A:
        keypad_instance->k_active_key = K_A;
        break;
    case KP_B:
        keypad_instance->k_active_key = K_B;
        break;
    case KP_C:
        keypad_instance->k_active_key = K_C;
        break;
    case KP_D:
        keypad_instance->k_active_key = K_D;
        break;
    case KP_E:
        keypad_instance->k_active_key = K_E;
        break;
    case KP_F:
        keypad_instance->k_active_key = K_F;
        break;
    default:
        keypad_instance->k_state = K_KEY_RELEASED;
        return;
    }

}

void keypad_port_exit(keypad *keypad_instance){
    if(!keypad_instance){
        fprintf(stderr, "Empty keypad instance: %s", SDL_GetError());
        keypad_instance->k_state = K_FAILURE;
        return;
    }

    k_port_SDL.k_ready = false;
    keypad_instance->k_state = K_OFF;
}
#include "display.h"
#include "display_port.h"

void display_start(machine *instance){
    if(!instance){
        fprintf(stderr, "Error: Incorrect Machine instance!\n");
        return;
    }

    instance->m_display.d_state = D_OFF;
    for(int i = 0; i < DISP_WIDTH * DISP_HEIGHT; i++){
        instance->m_display.d_framebuffer[i] = BG_COLOR;
    }
    display_port_init(&instance->m_display);
}

uint8_t display_update_framebuffer(machine *instance, uint8_t x_pos, uint8_t y_pos, uint8_t n){
    if(!instance){
        fprintf(stderr, "Error: Incorrect Machine instance!\n");
        return 0;
    }

    uint8_t collision = 0;

    uint32_t *framebuffer = instance->m_display.d_framebuffer;

    // Create the sprite in RGBA format
    for(int i = 0; i < n; i++){
        uint8_t current_byte = instance->m_ram[instance->m_index + i];
        uint32_t current_pixel = 0;

        for(int j = 7; j >= 0; j--){
            current_pixel = (current_byte & (1 << j)) ? FG_COLOR : BG_COLOR;

            uint16_t current_pos = ((i + y_pos) % DISP_HEIGHT) * DISP_WIDTH + ((7 - j) + x_pos) % DISP_WIDTH;
            if(collision == 0 && (framebuffer[current_pos] == current_pixel && current_pixel == FG_COLOR)){
                collision = 1;
            }

            framebuffer[current_pos] = (framebuffer[current_pos] == current_pixel) ? BG_COLOR : FG_COLOR;
        }
    }

    instance->m_display.d_state = D_AWAIT_UPDATE;
    return collision;
}

void display_update_window(machine *instance){
    if(!instance){
        fprintf(stderr, "Error: Incorrect Machine instance!\n");
        return;
    }

    if(instance->m_display.d_state == D_AWAIT_UPDATE){
        display_port_update(&instance->m_display);
    }
}

void display_clear_window(machine *instance){
    if(!instance){
        fprintf(stderr, "Error: Incorrect Machine instance!\n");
        return;
    }

    if(instance->m_display.d_state == D_ON){
        display_port_clear(&instance->m_display);
        
        for(int i = 0; i < DISP_WIDTH * DISP_HEIGHT; i++){
            instance->m_display.d_framebuffer[i] = BG_COLOR;
        }
    }
}

void display_stop(machine *instance){
    if(!instance){
        fprintf(stderr, "Error: Incorrect Machine instance!\n");
        return;
    }

    if(instance->m_display.d_state == D_ON){
        display_port_exit(&instance->m_display);
    }
}
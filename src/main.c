#include "chip8.h"

#include <SDL2/SDL.h>


int main(){
    machine mac;
    chip8_init(&mac);
    chip8_load_program(&mac, "../programs/chip8-roms/games/Pong (1 player).ch8");
    int8_t t = 8;
    for(;;){
        for(; t >= 0; t--){
            keypad_update(&mac);
            usleep(100);
            chip8_inst_exec(&mac);
            //if(mac.m_pc >= RAM_SIZE) mac.m_pc = 0;
            if(mac.m_state != C_WAITING_KEY) {if(mac.m_state != C_SKIP_INC) mac.m_pc += 2;
            else mac.m_state = C_RUNNING;}
        }
        t = 8;
        //if(--t <= 0){
        //    t = 8;
            if(mac.m_del_reg > 0) mac.m_del_reg--;
        //}
        display_update_window(&mac);
        //chip8_debug_print_cpu_state(&mac);
        //chip8_debug_print_stack(&mac);
        usleep(16667);
        //SDL_Delay(2);
        //chip8_debug_print_framebuffer(&mac);
    }
    //chip8_debug_print_regs(&mac);
    
    //chip8_debug_print_mem(&mac, 0);
    
    //chip8_debug_print_stack(&mac);
}
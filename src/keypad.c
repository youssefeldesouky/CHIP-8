#include "keypad.h"
#include "keypad_port.h"

void keypad_start(machine *instance){
    if(!instance){
        fprintf(stderr, "Error: Incorrect Machine instance!\n");
        return;
    }
    keypad_port_init(&instance->m_keypad);
}

void keypad_update(machine *instance){
    if(!instance){
        fprintf(stderr, "Error: Incorrect Machine instance!\n");
        return;
    }
    keypad_port_update(&instance->m_keypad);
    /*if(instance->m_state == C_WAITING_KEY) {
        instance->m_prev_state = instance->m_state;
        instance->m_state = C_RUNNING;
    }*/
    //if(instance->m_keypad.k_state == K_KEY_PRESSED) printf("key pressed is %x\n", instance->m_keypad.k_active_key);
}

void keypad_stop(machine *instance){
    if(!instance){
        fprintf(stderr, "Error: Incorrect Machine instance!\n");
        return;
    }
    keypad_port_exit(&instance->m_keypad);
}
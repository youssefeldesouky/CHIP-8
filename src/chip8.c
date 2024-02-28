/**
 * file: chip8.c
 * brief: source file that includes implementation of the interpreter
 * author: Youssef S. Eldesouky
 * date: 2/24/2024
 */

#include "chip8_private.h"
#include "chip8.h"

void chip8_init(machine *instance){
    if(!instance){
        fprintf(stderr, "Error: Incorrect Machine instance!\n");
        return;
    }
    display_start(instance);
    keypad_start(instance);
    memset(instance->m_ram, 0, RAM_SIZE);
    memset(instance->m_stack, 0, STACK_SIZE * 2);
    memset(instance->m_regs, 0, REG_NUM);
    instance->m_pc = PROG_ADDR;
    instance->m_index = 0;
    instance->m_stk_ptr = -1;
    instance->m_state = C_STOPPED;
    // set the font bytes in memory at location FONT_ADDR
    memcpy(instance->m_ram + FONT_ADDR, font_data, sizeof(font_data));
    srand(time(NULL));
}

void chip8_reset_registers(machine *instance){
    if(!instance){
        fprintf(stderr, "Error: Incorrect Machine instance!\n");
        return;
    }

    memset(instance->m_stack, 0, STACK_SIZE * 2);
    memset(instance->m_regs, 0, REG_NUM);
    instance->m_pc = PROG_ADDR;
    instance->m_index = 0;
    instance->m_stk_ptr = -1;
    instance->m_state = C_STOPPED;
}

void chip8_load_program(machine *instance, const char *path){
    if(!instance){
        fprintf(stderr, "Error: Incorrect Machine instance!\n");
        return;
    }

    if(instance->m_state != C_STOPPED){
        fprintf(stderr, "Error: chip8_load_program: Machine instance needs to be stopped!\n");
        return;
    }

    if(!path){
        fprintf(stderr, "Error: chip8_load_program: Incorrect path!\n");
        return;
    }

    int fd = open(path, O_RDONLY);
    if(fd == -1){
        fprintf(stderr, "Error: chip8_load_program: open: %s!\n", strerror(errno));
        return;
    }

    char buf[RAM_SIZE] = { 0 };
    ssize_t bytes_read = 0;
    bool program_valid = true;

    bytes_read = read(fd, buf, RAM_SIZE);

    if(bytes_read == -1){
        fprintf(stderr, "Error: chip8_load_program: read: %s!\n", strerror(errno));
        program_valid = false;
    }else if(bytes_read == 0){
        fprintf(stderr, "Error: chip8_load_program: read: file is empty!\n");
        program_valid = false;
    }

    if(bytes_read + PROG_ADDR >= RAM_SIZE){
        fprintf(stderr, "Error: chip8_load_program: program size is too big to fit in memory!\n");
        program_valid = false;
    }

    if(program_valid == true){
        memcpy(instance->m_ram + PROG_ADDR, buf, bytes_read);
    }

    if(close(fd) == -1){
        fprintf(stderr, "Error: chip8_load_program: %s!\n", strerror(errno));
    }
}

void chip8_run_loop(machine *instance, bool clean_run, bool allow_debugging){
    if(!instance){
        fprintf(stderr, "Error: Incorrect Machine instance!\n");
        return;
    }

    if(instance->m_state != C_STOPPED){
        fprintf(stderr, "Error: chip8_run_loop: Machine instance needs to be stopped!\n");
        return;
    }

    if(clean_run){
        chip8_reset_registers(instance);
    }

    while(1){
        // Check if there's debug requests
        // Check input
        // Compute Instruction
        // Check for S_BAD_CODE state to abort
        // Update delay and sound timers
        // Update display
        // Update sound
        // Wait until a cycle is done
    }
}

/************************ Debug Functions ************************/

void chip8_debug_print_mem(machine *instance, ind_reg offset){
    if(!instance){
        fprintf(stderr, "Error: Incorrect Machine instance!\n");
        return;
    }

    if(offset >= RAM_SIZE){
        fprintf(stderr, "Error: Incorrect offset position!\n");
        return;
    }

    printf("* RAM:\n");

    while(offset < RAM_SIZE){
        printf("%04x: ", offset);
        for(ind_reg i = 0; i < 16 && offset + i < RAM_SIZE; i++){
            printf("%02x%c", instance->m_ram[offset + i], (i % 2 == 0) ? '\0' : ' ');
        }
        putchar('\n');
        offset += 16;
    }
}

void chip8_debug_print_regs(machine *instance){
    if(!instance){
        fprintf(stderr, "Error: Incorrect Machine instance!\n");
        return;
    }

    printf("* Program Counter:\t%hx\n", instance->m_pc);
    printf("* Index Pointer:\t%hx\n", instance->m_index);
    printf("* Stack Pointer:\t%hhx\n", instance->m_stk_ptr);
    printf("* Delay Timer Register:\t%hhx\n", instance->m_del_reg);
    printf("* Sound Timer Register:\t%hhx\n", instance->m_snd_reg);

    printf("* Variable Registers:\n");
    for(uint8_t i = 0; i < REG_NUM; i += 2 * sizeof(uint8_t)){
        printf("  *V%hhX: %02hhx\t*V%hhX: %02hhx\n", i, instance->m_regs[i], i + 1, instance->m_regs[i + 1]);
    }
}

void chip8_debug_print_stack(machine *instance){
    if(!instance){
        fprintf(stderr, "Error: Incorrect Machine instance!\n");
        return;
    }

    printf("* Stack:\n");
    for(uint8_t i = 0; i < STACK_SIZE; i++){
        printf("  *%04hhx: %04hx", i * (uint8_t)sizeof(ins_reg), instance->m_stack[i]);
        if(instance->m_stk_ptr == i){
            printf("\t<-- SP");
        }
        putchar('\n');
    }
}

void chip8_debug_print_framebuffer(machine *instance){
    if(!instance){
        fprintf(stderr, "Error: Incorrect Machine instance!\n");
        return;
    }

    for(int i = 0; i < DISP_HEIGHT; i++){
        for(int j = 0; j < DISP_WIDTH; j++){
            putchar(((instance->m_display.d_framebuffer[(i * DISP_WIDTH) + j]) == FG_COLOR) ? '1' : '0');
        }
        putchar('\n');
    }
}

void chip8_debug_print_cpu_state(machine *instance){
    if(!instance){
        fprintf(stderr, "Error: Incorrect Machine instance!\n");
        return;
    }

    printf("Current CPU state: ");
    switch(instance->m_state){
    case C_STOPPED:
        printf("Stopped\n");
        break;
    case C_PAUSED:
        printf("Paused\n");
        break;
    case C_RUNNING:
        printf("Running\n");
        break;
    case C_SKIP_INC:
        printf("Skip next PC increment\n");
        break;
    case C_WAITING_KEY:
        printf("Waiting user input\n");
        break;
    case C_BAD_CODE:
        printf("Bad instruction\n");
        break;
    default:
        printf("UKNOWN\n");
        break;
    }
}
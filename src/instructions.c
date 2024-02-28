/**
 * file: instructions.c
 * brief: source file that includes implementation of the instructions
 * author: Youssef S. Eldesouky
 * date: 2/24/2024
 */

#include "instructions_private.h"
#include "instructions.h"

void chip8_inst_exec(machine *instance){
    //printf("from exec, current key stats is %s\n", (instance->m_keypad.k_state == K_KEY_PRESSED)?"pressed":"released");
    uint16_t opcode = SWAP_NIBBLES(*((uint16_t *)&((instance->m_ram)[instance->m_pc])));
    switch ((opcode & 0xF000) >> 12){
    case 0x0:
        switch(opcode & 0x0FFF){
        case 0x0E0:
            chip8_inst_CLS(instance);
            break;
        case 0x0EE:
            chip8_inst_RET(instance);
            break;
        default:
            chip8_inst_SYS(instance);
            break;
        }
        break;
    
    case 0x1:
        chip8_inst_JP(instance, opcode & 0x0FFF);
        break;

    case 0x2:
        chip8_inst_CALL(instance, opcode & 0x0FFF);
        break;

    case 0x3:
        chip8_inst_SE_I(instance, CHIP8_GET_REG(opcode, 2), opcode & 0x00FF);
        break;

    case 0x4:
        chip8_inst_SNE_I(instance, CHIP8_GET_REG(opcode, 2), opcode & 0x00FF);
        break;

    case 0x5:
        if((opcode & 0x000F) == 0x0){
            chip8_inst_SE(instance, CHIP8_GET_REG(opcode, 2), CHIP8_GET_REG(opcode, 1));
        }else{
            chip8_bad_instruction(instance);
        }
        break;

    case 0x6:
        chip8_inst_LD_I(instance, CHIP8_GET_REG(opcode, 2), opcode & 0x00FF);
        break;

    case 0x7:
        chip8_inst_ADD_I(instance, CHIP8_GET_REG(opcode, 2), opcode & 0x00FF);
        break;

    case 0x8:
        switch(opcode & 0x000F){
        case 0x0:
            chip8_inst_LD(instance, CHIP8_GET_REG(opcode, 2), CHIP8_GET_REG(opcode, 1));
            break;

        case 0x1:
            chip8_inst_OR(instance, CHIP8_GET_REG(opcode, 2), CHIP8_GET_REG(opcode, 1));
            break;

        case 0x2:
            chip8_inst_AND(instance, CHIP8_GET_REG(opcode, 2), CHIP8_GET_REG(opcode, 1));
            break;

        case 0x3:
            chip8_inst_XOR(instance, CHIP8_GET_REG(opcode, 2), CHIP8_GET_REG(opcode, 1));
            break;

        case 0x4:
            chip8_inst_ADD(instance, CHIP8_GET_REG(opcode, 2), CHIP8_GET_REG(opcode, 1));
            break;

        case 0x5:
            chip8_inst_SUB(instance, CHIP8_GET_REG(opcode, 2), CHIP8_GET_REG(opcode, 1));
            break;

        case 0x6:
            chip8_inst_SHR(instance, CHIP8_GET_REG(opcode, 2), CHIP8_GET_REG(opcode, 1));
            break;

        case 0x7:
            chip8_inst_SUBN(instance, CHIP8_GET_REG(opcode, 2), CHIP8_GET_REG(opcode, 1));
            break;

        case 0xE:
            chip8_inst_SHL(instance, CHIP8_GET_REG(opcode, 2), CHIP8_GET_REG(opcode, 1));
            break;

        default:
            chip8_bad_instruction(instance);
            break;
        }
        break;
    
    case 0x9:
        if((opcode & 0x000F) == 0x0){
            chip8_inst_SNE(instance, CHIP8_GET_REG(opcode, 2), CHIP8_GET_REG(opcode, 1));
        }else{
            chip8_bad_instruction(instance);
        }
        break;

    case 0xA:
        chip8_inst_LD_INDEX(instance, opcode & 0xFFF);
        break;

    case 0xB:
        chip8_inst_LD_JP_PC(instance, opcode & 0xFFF);
        break;

    case 0xC:
        chip8_inst_RAND(instance, CHIP8_GET_REG(opcode, 2), opcode & 0xFF);
        break;

    case 0xD:
        chip8_inst_DRAW(instance, CHIP8_GET_REG(opcode, 2), CHIP8_GET_REG(opcode, 1), opcode & 0xF);
        break;

    case 0xE:
        switch(opcode & 0x00FF){
        case 0x9E:
            chip8_inst_SKP(instance, CHIP8_GET_REG(opcode, 2));
            break;

        case 0xA1:
            chip8_inst_SKNP(instance, CHIP8_GET_REG(opcode, 2));
            break;

        default:
            chip8_bad_instruction(instance);
            break;
        }
        break;
    
    case 0xF:
        switch(opcode & 0x00FF){
        case 0x07:
            chip8_inst_LDDT(instance, CHIP8_GET_REG(opcode, 2));
            break;
        
        case 0x0A:
            chip8_inst_LDKEY(instance, CHIP8_GET_REG(opcode, 2));
            break;

        case 0x15:
            chip8_inst_SETDT(instance, CHIP8_GET_REG(opcode, 2));
            break;

        case 0x18:
            chip8_inst_SETST(instance, CHIP8_GET_REG(opcode, 2));
            break;

        case 0x1E:
            chip8_inst_ADD_INDEX(instance, CHIP8_GET_REG(opcode, 2));
            break;

        case 0x29:
            chip8_inst_LD_FONT(instance, CHIP8_GET_REG(opcode, 2));
            break;

        case 0x33:
            chip8_inst_LD_BCD(instance, CHIP8_GET_REG(opcode, 2));
            break;

        case 0x55:
            chip8_inst_ST_MEM(instance, CHIP8_GET_REG(opcode, 2));
            break;

        case 0x65:
            chip8_inst_LD_MEM(instance, CHIP8_GET_REG(opcode, 2));
            break;

        default:
            chip8_bad_instruction(instance);
            break;
        }
        break;

    default:
        printf("%x\n", opcode);
        chip8_bad_instruction(instance);
        break;
    }
}

static inline void chip8_bad_instruction(machine *instance){
    instance->m_state = C_BAD_CODE;
}

static inline int8_t chip8_stack_push(machine *instance){
    if(instance->m_stk_ptr >= STACK_SIZE - 1){
        return 1;
    }
    instance->m_stack[++instance->m_stk_ptr] = instance->m_pc;
    return 0;
}

static inline int8_t chip8_stack_pop(machine *instance){
    if(instance->m_stk_ptr < 0){ // -1 meaning stack is empty
        return 1;
    }
    instance->m_pc = instance->m_stack[instance->m_stk_ptr--];
    return 0;
}

// 0nnn Instruction
static inline void chip8_inst_SYS(machine *instance){
    // Ignored in interpreter
    //printf("%s called\n", __FUNCTION__);
    return;
}

// 00E0 Instruction
static inline void chip8_inst_CLS(machine *instance){
    // Clear screen
    //printf("%s called\n", __FUNCTION__);
    display_clear_window(instance);
}

// 00E0 Instruction
static inline void chip8_inst_RET(machine *instance){
    // Return
    //printf("%s called\n", __FUNCTION__);
    if(chip8_stack_pop(instance) == 1){
        // if stack is empty, terminate program
        chip8_bad_instruction(instance);
    }
}

// 1nnn Instruction
static inline void chip8_inst_JP(machine *instance, ins_reg address){
    // Jump instruction
    //printf("%s called\n", __FUNCTION__);
    instance->m_pc = address;
    instance->m_state = C_SKIP_INC;
}

// 2nnn Instruction
static inline void chip8_inst_CALL(machine *instance, ins_reg address){
    // Call instruction
    //printf("%s called\n", __FUNCTION__);
    chip8_stack_push(instance);
    instance->m_pc = address;
    instance->m_state = C_SKIP_INC;
}

// 3xkk Instruction
static inline void chip8_inst_SE_I(machine *instance, var_reg reg, uint8_t data){
    // Skip if equal instruction (Immediate)
    //printf("%s called\n", __FUNCTION__);
    if(instance->m_regs[reg] == data){
        instance->m_pc += 2;
    }
}

// 4xkk Instruction
static inline void chip8_inst_SNE_I(machine *instance, var_reg reg, uint8_t data){
    // Skip if not equal instruction (immediate)
    //printf("%s called\n", __FUNCTION__);
    if(instance->m_regs[reg] != data){
        instance->m_pc += 2;
    }
}

// 5xy0 Instruction
static inline void chip8_inst_SE(machine *instance, var_reg reg_x, var_reg reg_y){
    // Skip if equal instruction (reg)
    //printf("%s called\n", __FUNCTION__);
    if(instance->m_regs[reg_x] == instance->m_regs[reg_y]){
        instance->m_pc += 2;
    }
}

// 6xkk Instruction
static inline void chip8_inst_LD_I(machine *instance, var_reg reg, uint8_t data){
    // load instruction (immediate)
    //printf("%s called %hhx %hhx\n", __FUNCTION__, reg, data);
    instance->m_regs[reg] = data;
}

// 7xkk Instruction
static inline void chip8_inst_ADD_I(machine *instance, var_reg reg, uint8_t data){
    // Add instruction (immediate)
    //printf("%s called\n", __FUNCTION__);
    instance->m_regs[reg] += data;
}

// 8xy0 Instruction
static inline void chip8_inst_LD(machine *instance, var_reg reg_x, var_reg reg_y){
    // Load instruction (reg)
    //printf("%s called\n", __FUNCTION__);
    instance->m_regs[reg_x] = instance->m_regs[reg_y];
}

// 8xy1 Instruction
static inline void chip8_inst_OR(machine *instance, var_reg reg_x, var_reg reg_y){
    // OR instruction (reg)
    //printf("%s called\n", __FUNCTION__);
    instance->m_regs[reg_x] |= instance->m_regs[reg_y];
}

// 8xy2 Instruction
static inline void chip8_inst_AND(machine *instance, var_reg reg_x, var_reg reg_y){
    // AND instruction (reg)
    instance->m_regs[reg_x] &= instance->m_regs[reg_y];
}

// 8xy3 Instruction
static inline void chip8_inst_XOR(machine *instance, var_reg reg_x, var_reg reg_y){
    // XOR instruction (reg)
    instance->m_regs[reg_x] ^= instance->m_regs[reg_y];
}

// 8xy4 Instruction
static inline void chip8_inst_ADD(machine *instance, var_reg reg_x, var_reg reg_y){
    // Add instruction (reg)
    //printf("%s called\n", __FUNCTION__);
    instance->m_regs[R_VF] = (instance->m_regs[reg_x] + instance->m_regs[reg_y]) > 255;
    instance->m_regs[reg_x] += instance->m_regs[reg_y];
}

// 8xy5 Instruction
static inline void chip8_inst_SUB(machine *instance, var_reg reg_x, var_reg reg_y){
    // Subtract Vx from Vy instruction (reg)
    //printf("%s called\n", __FUNCTION__);
    instance->m_regs[R_VF] = instance->m_regs[reg_x] >= instance->m_regs[reg_y];
    instance->m_regs[reg_x] -= instance->m_regs[reg_y];
}

// 8xy6 Instruction
static inline void chip8_inst_SHR(machine *instance, var_reg reg_x, var_reg reg_y){
    // Shift right instruction (reg)
    //printf("%s called\n", __FUNCTION__);

#if CHIP8_VER == CHIP_SCHIP
    instance->m_regs[R_VF] = instance->m_regs[reg_x] & 0x01;
    instance->m_regs[reg_x] >>= 1;
#else
    // Not sure if it modifies Vf or not
    instance->m_regs[reg_x] = instance->m_regs[reg_y] >> 1;
#endif
}

// 8xy7 Instruction
static inline void chip8_inst_SUBN(machine *instance, var_reg reg_x, var_reg reg_y){
    // Subtract Vy from Vx instruction (reg)
    //printf("%s called\n", __FUNCTION__);
    instance->m_regs[R_VF] = instance->m_regs[reg_y] >= instance->m_regs[reg_x];
    instance->m_regs[reg_x] = instance->m_regs[reg_y] - instance->m_regs[reg_x];
}

// 8xyE Instruction
static inline void chip8_inst_SHL(machine *instance, var_reg reg_x, var_reg reg_y){
    // Shift left instruction (reg)
    //printf("%s called\n", __FUNCTION__);

#if CHIP8_VER == CHIP_SCHIP
    instance->m_regs[R_VF] = instance->m_regs[reg_x] & 0x01;
    instance->m_regs[reg_x] <<= 1;
#else
    // Not sure if it modifies Vf or not
    instance->m_regs[reg_x] = instance->m_regs[reg_y] << 1;
#endif
}

// 9xy0 Instruction
static inline void chip8_inst_SNE(machine *instance, var_reg reg_x, var_reg reg_y){
    // Skip if not equal instruction (reg)
    //printf("%s called\n", __FUNCTION__);
    if(instance->m_regs[reg_x] != instance->m_regs[reg_y]){
        instance->m_pc += 2;
    }
}

// Annn Instruction
static inline void chip8_inst_LD_INDEX(machine *instance, ind_reg address){
    // Load index register instruction
    //printf("%s called\n", __FUNCTION__);
    instance->m_index = address;
}

// Bnnn Instruction
static inline void chip8_inst_LD_JP_PC(machine *instance, ins_reg address){
    // jump to V0 + nnn instruction
    //printf("%s called\n", __FUNCTION__);
    instance->m_pc = instance->m_regs[R_V0] + address;
    instance->m_state = C_SKIP_INC;
}

// Cxkk Instruction
static inline void chip8_inst_RAND(machine *instance, var_reg reg, uint8_t data){
    // Random instruction
    //printf("%s called\n", __FUNCTION__);
    instance->m_regs[reg] = (uint8_t)rand() & data;
}

// Dxyn Instruction
static inline void chip8_inst_DRAW(machine *instance, var_reg reg_x, var_reg reg_y, uint8_t data){
    // Draw instruction
    //printf("%s called with x: %d y: %d and n: %d\n", __FUNCTION__, instance->m_regs[reg_x], instance->m_regs[reg_y], data);
    instance->m_regs[R_VF] = display_update_framebuffer(instance, instance->m_regs[reg_x], instance->m_regs[reg_y], data);
}

// Ex9E Instruction
static inline void chip8_inst_SKP(machine *instance, var_reg reg){
    // Skip if key pressed instruction
    //printf("%s called\n", __FUNCTION__);
    if((instance->m_keypad.k_state == K_KEY_PRESSED || instance->m_keypad.k_state == K_KEY_HELD) &&
    instance->m_regs[reg] == instance->m_keypad.k_active_key){
        //printf("SKP fucking called for value %x, %x pressed\n", instance->m_regs[reg], instance->m_keypad.k_active_key);
        instance->m_pc += 2;
    }
}

// ExA1 Instruction
static inline void chip8_inst_SKNP(machine *instance, var_reg reg){
    // Skip if key not pressed instruction
    //printf("%s called\n", __FUNCTION__);
    if (/*instance->m_keypad.k_state == K_KEY_RELEASED ||*/
       ((instance->m_keypad.k_state == K_KEY_PRESSED || instance->m_keypad.k_state == K_KEY_HELD) &&
        instance->m_regs[reg] != instance->m_keypad.k_active_key))
    {
        //printf("NSKP fucking called for value %x, %x pressed\n", instance->m_regs[reg], instance->m_keypad.k_active_key);
        instance->m_pc += 2;
    }
}

// Fx07 Instruction
static inline void chip8_inst_LDDT(machine *instance, var_reg reg){
    // Load from delay timer instruction
    //printf("%s called\n", __FUNCTION__);
    instance->m_regs[reg] = instance->m_del_reg;
}

// Fx0A Instruction
static inline void chip8_inst_LDKEY(machine *instance, var_reg reg){
    // If entered and the processor state isn't WAITING_KEY, set it to
    // WAITING_KEY, which will halt the increment of PC, hence opcode
    // processing, in the Loop check for key press, and once it is found
    // call this instruction again, while will execute the else clause,
    // setting the key value to the target register and setting the processor
    // state to the previous state
    // It must be noted that it should not work with held-down events
    printf("%s called for register V%x\n", __FUNCTION__, reg);
    if(instance->m_state != C_WAITING_KEY){
        instance->m_prev_state = instance->m_state;
        instance->m_state = C_WAITING_KEY;
        return;
    }else{
        if(instance->m_keypad.k_state != K_KEY_PRESSED) return;
        instance->m_regs[reg] = instance->m_keypad.k_active_key;
        instance->m_state = instance->m_prev_state;
    }
}

// Fx15 Instruction
static inline void chip8_inst_SETDT(machine *instance, var_reg reg){
    // set delay timer instruction
    //printf("%s called\n", __FUNCTION__);
    instance->m_del_reg = instance->m_regs[reg];
}

// Fx18 Instruction
static inline void chip8_inst_SETST(machine *instance, var_reg reg){
    // set sound timer instruction
    //printf("%s called\n", __FUNCTION__);
    instance->m_snd_reg = instance->m_regs[reg];
}

// Fx1E Instruction
static inline void chip8_inst_ADD_INDEX(machine *instance, var_reg reg){
    // Add Vx to I instruction
    //printf("%s called\n", __FUNCTION__);
    instance->m_index += instance->m_regs[reg];
}

// Fx29 Instruction
static inline void chip8_inst_LD_FONT(machine *instance, var_reg reg){
    // Set I to digit in Vx instruction
    //printf("%s called for register V%d I should be: %d\n", __FUNCTION__, reg, instance->m_regs[reg] * 5);
    instance->m_index = FONT_ADDR + instance->m_regs[reg] * 5;
}

// Fx33 Instruction
static inline void chip8_inst_LD_BCD(machine *instance, var_reg reg){
    // store BCD of Vx in I location instruction
    //printf("%s called\n", __FUNCTION__);
    uint8_t tmp = instance->m_regs[reg];
    
    for(int8_t i = 2; i >= 0; i--){
        instance->m_ram[instance->m_index + i] = tmp % 10;
        tmp /= 10;
    }
    // Not sure if I is modified or not, but I'm going to assume it doesn't
}

// Fx55 Instruction
static inline void chip8_inst_ST_MEM(machine *instance, var_reg reg){
    // Store registers V0 to Vx in I location instruction
    //printf("%s called\n", __FUNCTION__);
    for(uint8_t i = 0; i <= reg; i++){
        instance->m_ram[instance->m_index + i] = instance->m_regs[R_V0 + i];
    }
}

// Fx65 Instruction
static inline void chip8_inst_LD_MEM(machine *instance, var_reg reg){
    // load registers V0 to Vx from I location instruction
    //printf("%s called\n", __FUNCTION__);
    for(uint8_t i = 0; i <= reg; i++){
        instance->m_regs[R_V0 + i] = instance->m_ram[instance->m_index + i];
    }
}


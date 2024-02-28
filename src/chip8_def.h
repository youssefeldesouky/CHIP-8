/**
 * @file chip8_def.h
 * @brief header file that includes machine data that is used by the interpreter
 * @author Youssef S. Eldesouky
 * @date 2/24/2024
*/

#ifndef __CHIP8_DEF__H__
#define __CHIP8_DEF__H__

#include <stdint.h>
#include "display_def.h"
#include "keypad_def.h"

#define CHIP8_GET_REG(OPCODE, NIBBLE) (((OPCODE) & (0x000F << ((NIBBLE) * 4))) >> ((NIBBLE) * 4))
#define SWAP_NIBBLES(BYTE) (((((BYTE) & 0xFF00) >> 8) | ((BYTE) << 8)) & 0xFFFF)

#define CHIP8_ORGNL 0
#define CHIP8_SCHIP 1

#define CHIP8_VER   CHIP_SCHIP

#define RAM_SIZE    4096                // size of RAM in bytes
#define REG_NUM     16                  // Number of Varaible Registers
#define STACK_SIZE  32                  // Number of stack 16-bit entries

#define PROG_ADDR   0x200               // Program start location in RAM
#define FONT_ADDR   0x000               // Font start location in RAM

#define CLK_FREQ    500                 // Emulation speed (Based on this resource: https://github.com/AfBu/haxe-CHIP-8-emulator/wiki/(Super)CHIP-8-Secrets#speed-of-emulation)
#define TIM_FREQ    60                  // Frequency of the timers (Default 60Hz)

typedef uint8_t     tim_reg;            // Timer register
typedef int8_t      stk_reg;            // Stack pointer register
typedef uint16_t    ind_reg;            // Index register
typedef uint16_t    ins_reg;            // Instruction pointer register

typedef enum {
    C_STOPPED,
    C_PAUSED,
    C_RUNNING,
    C_SKIP_INC,
    C_WAITING_KEY,
    C_BAD_CODE
} chip8_state;                                // Machine state

typedef enum {
    R_V0, R_V1, R_V2, R_V3,
    R_V4, R_V5, R_V6, R_V7,
    R_V8, R_V9, R_VA, R_VB,
    R_VC, R_VD, R_VE, R_VF
} var_reg;                              // Variable register

typedef struct {
    uint8_t     m_ram   [RAM_SIZE];     // RAM area
    display     m_display;              // Display structure
    uint16_t    m_stack [STACK_SIZE];   // Call Stack
    uint8_t     m_regs  [REG_NUM];      // General Purpose Variable Registers
    keypad      m_keypad;               // Keypad structure
    ins_reg     m_pc;                   // Program Counter
    ind_reg     m_index;                // Index register
    stk_reg     m_stk_ptr;              // Stack pointer
    tim_reg     m_del_reg;              // Delay timer register
    tim_reg     m_snd_reg;              // Sound timer register
    chip8_state m_state;                // Current machine state
    chip8_state m_prev_state;           // Previous machine state (used with debugging)
} machine;

#endif
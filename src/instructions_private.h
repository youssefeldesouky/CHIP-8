/**
 * @file instructions_private.h
 * @brief header file that includes private declarations of the instructions
 * @author Youssef S. Eldesouky
 * @date 2/24/2024
 */

#ifndef __INSTRUCTIONS_PRIVATE__H__
#define __INSTRUCTIONS_PRIVATE__H__

#include "chip8_def.h"

static inline void chip8_bad_instruction(machine *instance);

static inline int8_t chip8_stack_push(machine *instance);

static inline int8_t chip8_stack_pop(machine *instance);

// 0nnn Instruction
static inline void chip8_inst_SYS(machine *instance);

// 00E0 Instruction
static inline void chip8_inst_CLS(machine *instance);

// 00E0 Instruction
static inline void chip8_inst_RET(machine *instance);

// 1nnn Instruction
static inline void chip8_inst_JP(machine *instance, ins_reg address);

// 2nnn Instruction
static inline void chip8_inst_CALL(machine *instance, ins_reg address);

// 3xkk Instruction
static inline void chip8_inst_SE_I(machine *instance, var_reg reg, uint8_t data);

// 4xkk Instruction
static inline void chip8_inst_SNE_I(machine *instance, var_reg reg, uint8_t data);

// 5xy0 Instruction
static inline void chip8_inst_SE(machine *instance, var_reg reg_x, var_reg reg_y);

// 6xkk Instruction
static inline void chip8_inst_LD_I(machine *instance, var_reg reg, uint8_t data);

// 7xkk Instruction
static inline void chip8_inst_ADD_I(machine *instance, var_reg reg, uint8_t data);

// 8xy0 Instruction
static inline void chip8_inst_LD(machine *instance, var_reg reg_x, var_reg reg_y);

// 8xy1 Instruction
static inline void chip8_inst_OR(machine *instance, var_reg reg_x, var_reg reg_y);

// 8xy2 Instruction
static inline void chip8_inst_AND(machine *instance, var_reg reg_x, var_reg reg_y);

// 8xy3 Instruction
static inline void chip8_inst_XOR(machine *instance, var_reg reg_x, var_reg reg_y);

// 8xy4 Instruction
static inline void chip8_inst_ADD(machine *instance, var_reg reg_x, var_reg reg_y);

// 8xy5 Instruction
static inline void chip8_inst_SUB(machine *instance, var_reg reg_x, var_reg reg_y);

// 8xy6 Instruction
static inline void chip8_inst_SHR(machine *instance, var_reg reg_x, var_reg reg_y);

// 8xy7 Instruction
static inline void chip8_inst_SUBN(machine *instance, var_reg reg_x, var_reg reg_y);

// 8xyE Instruction
static inline void chip8_inst_SHL(machine *instance, var_reg reg_x, var_reg reg_y);

// 9xy0 Instruction
static inline void chip8_inst_SNE(machine *instance, var_reg reg_x, var_reg reg_y);

// Annn Instruction
static inline void chip8_inst_LD_INDEX(machine *instance, ind_reg address);

// Bnnn Instruction
static inline void chip8_inst_LD_JP_PC(machine *instance, ins_reg address);

// Cxkk Instruction
static inline void chip8_inst_RAND(machine *instance, var_reg reg, uint8_t data);

// Dxyn Instruction
static inline void chip8_inst_DRAW(machine *instance, var_reg reg_x, var_reg reg_y, uint8_t data);

// Ex9E Instruction
static inline void chip8_inst_SKP(machine *instance, var_reg reg);

// ExA1 Instruction
static inline void chip8_inst_SKNP(machine *instance, var_reg reg);

// Fx07 Instruction
static inline void chip8_inst_LDDT(machine *instance, var_reg reg);

// Fx0A Instruction
static inline void chip8_inst_LDKEY(machine *instance, var_reg reg);

// Fx15 Instruction
static inline void chip8_inst_SETDT(machine *instance, var_reg reg);

// Fx18 Instruction
static inline void chip8_inst_SETST(machine *instance, var_reg reg);

// Fx1E Instruction
static inline void chip8_inst_ADD_INDEX(machine *instance, var_reg reg);

// Fx1E Instruction
static inline void chip8_inst_LD_FONT(machine *instance, var_reg reg);

// Fx33 Instruction
static inline void chip8_inst_LD_BCD(machine *instance, var_reg reg);

// Fx55 Instruction
static inline void chip8_inst_ST_MEM(machine *instance, var_reg reg);

// Fx65 Instruction
static inline void chip8_inst_LD_MEM(machine *instance, var_reg reg);

#endif
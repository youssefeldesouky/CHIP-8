/**
 * @file instructions.h
 * @brief header file that includes interface to instructions parser and executor
 * @author Youssef S. Eldesouky
 * @date 2/24/2024
 */

#ifndef __INSTRUCTIONS__H__
#define __INSTRUCTIONS__H__

#include <stdio.h>
#include <stdlib.h>
#include "chip8_def.h"
#include "display.h"

/**
 * @brief Parses and executes the instruction currently pointed to by PC
 * @param instance pointer to the allocated machine instance
 * @return void
 */
void chip8_inst_exec(machine *instance);

#endif
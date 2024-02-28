/**
 * @file chip8.h
 * @brief header file that includes machine operations that is used by the interpreter
 * @author Youssef S. Eldesouky
 * @date 2/24/2024
 */

#ifndef __CHIP8__H__
#define __CHIP8__H__

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "chip8_def.h"
#include "display.h"
#include "instructions.h"
#include "keypad.h"

/**
 * @brief Initializes a machine instance to the initial values
 * @param instance pointer to the allocated machine instance
 * @return void 
*/
void chip8_init(machine *instance);

/**
 * @brief Initializes a machine instance to the initial values
 * @param instance pointer to the allocated machine instance
 * @param path path to the program file
 * @return void
 */
void chip8_load_program(machine *instance, const char *path);

/************************ Debug Functions ************************/

/**
 * @brief Prints a dump of the contents in the RAM, starting at an offset
 * @param instance pointer to the allocated machine instance
 * @param offset start printing at that address to the end of the RAM
 * @return void
 */
void chip8_debug_print_mem(machine *instance, ind_reg offset);

/**
 * @brief Prints a dump of the registers contents
 * @param instance pointer to the allocated machine instance
 * @return void
 */
void chip8_debug_print_regs(machine *instance);

/**
 * @brief Prints a dump of the stack contents
 * @param instance pointer to the allocated machine instance
 * @return void
 */
void chip8_debug_print_stack(machine *instance);

/**
 * @brief Prints a dump of the framebuffer
 * @param instance pointer to the allocated machine instance
 * @return void
 */
void chip8_debug_print_framebuffer(machine *instance);

/**
 * @brief Prints the current state of the CPU
 * @param instance pointer to the allocated machine instance
 * @return void
 */
void chip8_debug_print_cpu_state(machine *instance);
#endif
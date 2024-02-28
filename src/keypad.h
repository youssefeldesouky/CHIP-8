/**
 * @file keypad.h
 * @brief header file that includes keypad interface
 * @author Youssef S. Eldesouky
 * @date 2/24/2024
 */

#ifndef __KEYPAD__H__
#define __KEYPAD__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chip8_def.h"
#include "keypad_def.h"

/**
 * @brief Initializes the keypad
 * @param instance pointer to the allocated machine instance
 * @return void
 */
void keypad_start(machine *instance);

/**
 * @brief Updates the keypad structure inside of the machine instance to
 *        the read events by the input system
 * @param instance pointer to the allocated machine instance
 * @return void
 */
void keypad_update(machine *instance);

/**
 * @brief Releases and turns off the keypad
 * @param instance pointer to the allocated machine instance
 * @return void
 */
void keypad_stop(machine *instance);

#endif

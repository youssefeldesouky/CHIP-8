/**
 * @file keypad_port.h
 * @brief header file that includes target-independent APIs
 * @author Youssef S. Eldesouky
 * @date 2/24/2024
 */

#ifndef __KEYPAD_PORT__H__
#define __KEYPAD_PORT__H__

#include <stdint.h>
#include <stdbool.h>
#include "keypad_def.h"

/**
 * @brief Initializes the input system that implements this interface
 * @param keypad_instance pointer to the generic keypad structure instance
 * @return void
 */
void keypad_port_init(keypad *keypad_instance);

/**
 * @brief Updates the keypad generic structure with the state of the input
 *        system that implements this interface
 * @param keypad_instance pointer to the generic keypad structure instance
 * @return void
 */
void keypad_port_update(keypad *keypad_instance);

/**
 * @brief releases the input system that implements this interface
 * @param keypad_instance pointer to the generic keypad structure instance
 * @return void
 */
void keypad_port_exit(keypad *keypad_instance);

#endif

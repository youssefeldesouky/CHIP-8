/**
 * @file display_port.h
 * @brief header file that includes target-independent APIs 
 * @author Youssef S. Eldesouky
 * @date 2/24/2024
 */

#ifndef __DISPLAY_PORT__H__
#define __DISPLAY_PORT__H__

#include <stdint.h>
#include "display_def.h"

/**
 * @brief Initializes, runs and clears the display that implements this interface
 * @param display_instance pointer to the generic display structure instance
 * @return void
 */
void display_port_init(display *display_instance);

/**
 * @brief clears the display that implements this interface with the background
 *        color
 * @param display_instance pointer to the generic display structure instance
 * @return void
 */
void display_port_clear(display *display_instance);

/**
 * @brief Updates the display that implements this interface with the contents
 *        of the framebuffer
 * @param display_instance pointer to the generic display structure instance
 * @return void
 */
void display_port_update(display *display_instance);

/**
 * @brief releases the display that implements this interface
 * @param display_instance pointer to the generic display structure instance
 * @return void
 */
void display_port_exit(display *display_instance);

#endif
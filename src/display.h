/**
 * @file display.h
 * @brief header file that includes display interface
 * @author Youssef S. Eldesouky
 * @date 2/24/2024
 */

#ifndef __DISPLAY__H__
#define __DISPLAY__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chip8_def.h"
#include "display_def.h"

/**
 * @brief Initializes the display and the sets all the pixels in the framebuffer
 *        to BG_COLOR
 * @param instance pointer to the allocated machine instance
 * @return void
 */
void display_start(machine *instance);

/**
 * @brief Updates the the contents of the framebuffer with the XOR of the sprite
 *        pointed to by the Index register, setting pixels that are 0 to BG_COLOR
 *        and the ones set to 1 to FG_COLOR
 * @note  Currently it wraps around if the sprite was placed in a coordinate that allows so
 * @param instance pointer to the allocated machine instance
 * @param x_pos the X coordinate in the display
 * @param y_pos the Y coordinate in the display
 * @param n the number of bytes to read from RAM, which resmeble the rows of the sprite
 * @return returns 1 if a bit got cleared (Collision), 0 otherwise
 */
uint8_t display_update_framebuffer(machine *instance, uint8_t x_pos, uint8_t y_pos, uint8_t n);

/**
 * @brief Updates the display window if its framebuffer has been updated
 * @param instance pointer to the allocated machine instance
 * @return void
 */
void display_update_window(machine *instance);

/**
 * @brief Fills the entire window with BG_COLOR, while setting the entire
 *        framebuffer to BG_COLOR
 * @param instance pointer to the allocated machine instance
 * @return void
 */
void display_clear_window(machine *instance);

/**
 * @brief Releases and turns off the display
 * @param instance pointer to the allocated machine instance
 * @return void
 */
void display_stop(machine *instance);

#endif

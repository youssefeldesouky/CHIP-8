/**
 * @file display_def.h
 * @brief header file that includes display related declarations
 * @author Youssef S. Eldesouky
 * @date 2/24/2024
 */

#ifndef __DISPLAY_DEF__H__
#define __DISPLAY_DEF__H__

#include <stdint.h>

#define DISP_WIDTH      64                  // Width of the display
#define DISP_HEIGHT     32                  // Height of the display


#define SCREEN_SCALE    8                   // Scale of the display window
#define BG_COLOR        0xFF001000          // Color of the background (ABGR)
#define FG_COLOR        0xFF0EFF00          // Color of the foreground (ABGR)
#define SPRITE_WIDTH    8                   // Width of the sprite in bits

#define COLOR_R(COLOR) ((COLOR) & 0x000000FF)
#define COLOR_G(COLOR) (((COLOR) & 0x0000FF00) >> 8)
#define COLOR_B(COLOR) (((COLOR) & 0x00FF0000) >> 16)
#define COLOR_A(COLOR) (((COLOR) & 0xFF000000) >> 24)

typedef enum {
    D_OFF,
    D_ON,
    D_AWAIT_UPDATE,
    D_FAILURE
} display_state;

typedef struct {
    uint32_t            d_framebuffer[DISP_WIDTH * DISP_WIDTH];
    display_state       d_state;
} display;

#endif
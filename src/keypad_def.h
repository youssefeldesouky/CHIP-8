/**
 * @file keypad_def.h
 * @brief header file that includes keypad related declarations
 * @author Youssef S. Eldesouky
 * @date 2/24/2024
 */

#ifndef __KEYPAD_DEF__H__
#define __KEYPAD_DEF__H__

#include <stdint.h>

#define KEYS_NUM    16                  // Number of keys

typedef enum {
    K_1 = 0x1,    K_2 = 0x2,    K_3 = 0x3,    K_C = 0xC,
    K_4 = 0x4,    K_5 = 0x5,    K_6 = 0x6,    K_D = 0xD,
    K_7 = 0x7,    K_8 = 0x8,    K_9 = 0x9,    K_E = 0xE,
    K_A = 0xA,    K_0 = 0x0,    K_B = 0xB,    K_F = 0xF
} keys;                                 // Keypad Keys

typedef enum{
    K_OFF,
    K_KEY_PRESSED,
    K_KEY_HELD,
    K_KEY_RELEASED,
    K_FAILURE
} keypad_state;

typedef struct{
    keys            k_active_key;       // The current pressed key
    keypad_state    k_state;            // The current keypad state
} keypad;

#endif
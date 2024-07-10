/** 
 *  Copyright (C) 2024 Joeri Kortenhorst
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>. 
 * 
 * 
 *  If DEBUG is defined, everything will be printed to Serial as text for
 *  debugging purposes. If it is not defined, the byte array will be send
 *  over Serial so that it can be used for the Color program.
 */


#ifndef GLOBALS_H
#define GLOBALS_H
#include "Arduino.h"
#include "RotaryEncoder.h"
#include "grove_alphanumeric_display.h"

#define RESET_PIN_IN 45
#define RESET_PIN_READ 26
#define MODE_PIN_IN 41
#define MODE_PIN_1 24
#define MODE_PIN_2 25
#define RED_BUTTON_IN 49
#define RED_BUTTON 44

#define UPDATES 0.25

#define LEFT 0x01
#define RIGHT 0x02
#define SHORT_PRESS 0x03
#define LONG_PRESS 0x04
#define PRESS_LEFT 0x05
#define PRESS_RIGHT 0x06

#define TUBE_BRIGHTNESS 15

#define I2C_ADDR_DISPLAY_1 0x70
#define ENCODER_1_A_PIN 2
#define ENCODER_1_B_PIN 3
#define ENCODER_1_SWITCH_PIN 4

#define I2C_ADDR_DISPLAY_2 0x71
#define ENCODER_2_A_PIN 5
#define ENCODER_2_B_PIN 6
#define ENCODER_2_SWITCH_PIN 7

#define I2C_ADDR_DISPLAY_3 0x72
#define ENCODER_3_A_PIN 8
#define ENCODER_3_B_PIN 9 
#define ENCODER_3_SWITCH_PIN 10

#define I2C_ADDR_DISPLAY_4 0x73
#define ENCODER_4_A_PIN 11
#define ENCODER_4_B_PIN 12 
#define ENCODER_4_SWITCH_PIN 13 

#define RESOLUTIONS {1, 5, 10}
#define SIZE_OF_RESOLUTIONS 3

#define RESET_MSG { 255, 255, 255, 255 }
#define EASY_COLORS_RESET { 201, 201, 201, 201 }

enum Mode: uint8_t {
    EASY_COLORS,
    NORMAL, 
    HARD,
};

extern Mode mode;

extern uint8_t reset_array[4];
extern uint8_t easy_colors_reset[4];

extern uint8_t loc;
extern uint8_t resolutions[];
extern uint8_t resolution;

extern uint8_t num_1;
extern uint8_t num_2;
extern uint8_t num_3;
extern uint8_t num_4;

extern Expedition::Versatile_RotaryEncoder versatile_encoder1;
extern Expedition::Versatile_RotaryEncoder versatile_encoder2;
extern Expedition::Versatile_RotaryEncoder versatile_encoder3;
extern Expedition::Versatile_RotaryEncoder versatile_encoder4;

extern Seeed_Digital_Tube tube1;
extern Seeed_Digital_Tube tube2;
extern Seeed_Digital_Tube tube3;
extern Seeed_Digital_Tube tube4;


extern bool reset;
extern bool red_button;
extern bool mode_1;
extern bool mode_2;

#endif
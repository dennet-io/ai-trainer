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


#include "Arduino.h"
#include "globals.h"
#include "RotaryEncoder.h"
#include "grove_alphanumeric_display.h"


uint8_t loc = 0;
uint8_t resolutions[SIZE_OF_RESOLUTIONS] = RESOLUTIONS;
uint8_t resolution = resolutions[loc];

uint8_t reset_array[4] = RESET_MSG;
uint8_t easy_colors_reset[4] = EASY_COLORS_RESET;

Mode mode = Mode::NORMAL;

uint8_t num_1 = 10;
uint8_t num_2 = 20;
uint8_t num_3 = 30;
uint8_t num_4 = 40;

Expedition::Versatile_RotaryEncoder versatile_encoder1 = Expedition::Versatile_RotaryEncoder(
    ENCODER_1_A_PIN, 
    ENCODER_1_B_PIN, 
    ENCODER_1_SWITCH_PIN, 
    num_1);

Expedition::Versatile_RotaryEncoder versatile_encoder2 = Expedition::Versatile_RotaryEncoder(
    ENCODER_2_A_PIN, 
    ENCODER_2_B_PIN,
    ENCODER_2_SWITCH_PIN, 
    num_2);

Expedition::Versatile_RotaryEncoder versatile_encoder3 = Expedition::Versatile_RotaryEncoder(
    ENCODER_3_A_PIN, 
    ENCODER_3_B_PIN, 
    ENCODER_3_SWITCH_PIN, 
    num_3);

Expedition::Versatile_RotaryEncoder versatile_encoder4 = Expedition::Versatile_RotaryEncoder(
    ENCODER_4_A_PIN, 
    ENCODER_4_B_PIN, 
    ENCODER_4_SWITCH_PIN, 
    num_4);

Seeed_Digital_Tube tube1;
Seeed_Digital_Tube tube2;
Seeed_Digital_Tube tube3;
Seeed_Digital_Tube tube4;


bool reset = false;
bool red_button = false;
bool mode_1 = false;
bool mode_2 = false;

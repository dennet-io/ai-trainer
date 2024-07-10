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


#ifndef ROTARY_FUNCTIONS_H
#define ROTARY_FUNCTIONS_H

#include "Arduino.h"
#include "RotaryEncoder.h"

// Functions prototyping to be handled on each Encoder Event
void handleRotate(int8_t rotation, uint8_t& num);
void handlePressRotate(int8_t rotation, uint8_t& num);
void handleHeldRotate(int8_t rotation, uint8_t& num);
void handlePress();
void handleDoublePress();
void handlePressRelease();
void handleLongPress();
void handleLongPressRelease();
void handlePressRotateRelease();
void handleHeldRotateRelease();
void assign_function_handles(Expedition::Versatile_RotaryEncoder& versatile_encoder_);

#endif
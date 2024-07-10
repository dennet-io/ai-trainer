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



#include "rotary_functions.h"
#include "globals.h"

void assign_function_handles(Expedition::Versatile_RotaryEncoder& versatile_encoder_) {
    versatile_encoder_.setHandleRotate(handleRotate);
    versatile_encoder_.setHandlePressRotate(handlePressRotate);
    versatile_encoder_.setHandleHeldRotate(handleHeldRotate);
    versatile_encoder_.setHandlePress(handlePress);
    versatile_encoder_.setHandleDoublePress(handleDoublePress);
    //versatile_encoder->setHandleDoublePress(nullptr); // Disables Double Press
    versatile_encoder_.setHandlePressRelease(handlePressRelease);
    versatile_encoder_.setHandleLongPress(handleLongPress);
    versatile_encoder_.setHandleLongPressRelease(handleLongPressRelease);
    versatile_encoder_.setHandlePressRotateRelease(handlePressRotateRelease);
    versatile_encoder_.setHandleHeldRotateRelease(handleHeldRotateRelease);

    // set your own defualt values (optional)
    // versatile_encoder->setInvertedSwitch(true); // inverts the switch behaviour from HIGH to LOW to LOW to HIGH
    // versatile_encoder->setReadIntervalDuration(1); // set 2ms as long press duration (default is 1ms)
    // versatile_encoder->setShortPressDuration(35); // set 35ms as short press duration (default is 50ms)
    // versatile_encoder->setLongPressDuration(550); // set 550ms as long press duration (default is 1000ms)
    // versatile_encoder->setDoublePressDuration(350); // set 350ms as double press duration (default is 250ms)
}

/* Implement your own function when the encoder is turned left.*/
void handleRotate(int8_t rotation, uint8_t& num) {
  #ifdef DEBUG
	Serial.print("#1 Rotated: ");
  #endif
    if (rotation > 0) {
      #ifdef DEBUG
	    Serial.println("Right");
      #endif
      num = (num + resolution) % 99;
    }
    else {
      #ifdef DEBUG
	    Serial.println("Left");
      #endif
      num = (num - resolution) < 0 ? 99 : num - resolution;
    }
}

void handlePressRotate(int8_t rotation, uint8_t& num) {
  #ifdef DEBUG
	Serial.print("#2 Pressed and rotated: ");
  #endif
    if (rotation > 0) {
      #ifdef DEBUG
	    Serial.println("Right");
      #endif
      num = (num + resolution) % 99;
    }
    else {
      #ifdef DEBUG
	    Serial.println("Left");
      #endif
      num = num < resolution ? 99 : num - resolution;
    }
}

void handleHeldRotate(int8_t rotation, uint8_t& num) {
  #ifdef DEBUG
	Serial.print("#3 Held and rotated: ");
  #endif
    if (rotation > 0) {
      #ifdef DEBUG
	    Serial.println("Right");
      #endif
      num = (num + resolution) % 99;
    }
    else {
      #ifdef DEBUG
	    Serial.println("Left");
      #endif
      num = num < resolution ? 99 : num - resolution;
    }
}

void handlePress() {
  #ifdef DEBUG
  Serial.write(SHORT_PRESS);
  Serial.println("- SWITCH -");
  #endif
  loc = (loc + 1) % SIZE_OF_RESOLUTIONS;
  resolution = resolutions[loc];
}

void handleDoublePress() {
  #ifdef DEBUG
	Serial.println("#4.2 Double Pressed");
  #endif
}

void handlePressRelease() {
  #ifdef DEBUG
	Serial.println("#5 Press released");
  #endif
}

void handleLongPress() {
  #ifdef DEBUG
  Serial.write(LONG_PRESS);
	Serial.println("#6 Long pressed");
  #endif
}

void handleLongPressRelease() {
  #ifdef DEBUG
	Serial.println("#7 Long press released");
  #endif
}

void handlePressRotateRelease() {
  #ifdef DEBUG
	Serial.println("#8 Press rotate released");
  #endif
}

void handleHeldRotateRelease() {
  #ifdef DEBUG
	Serial.println("#9 Held rotate released");
  #endif
}
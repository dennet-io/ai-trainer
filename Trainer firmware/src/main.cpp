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

#include <Arduino.h>
#include "Wire.h"
#include "grove_alphanumeric_display.h"
#include "RotaryEncoder.h"
#include "globals.h"
#include "rotary_functions.h"


// Set up initial array. 
uint8_t values[6] = { num_1, num_2, num_3, num_4, mode, red_button };
unsigned long timing = 0;

/**
 * Function to setup a seed digital tube. A segment display with 2 segments. 
 */
void setup_tube(Seeed_Digital_Tube &tube_, uint8_t addr) 
{
  #ifdef DEBUG
  Serial.print("Setup tube: ");
  Serial.println(addr);
  #endif

  tube_.setTubeType(TYPE_2, addr);
  tube_.setBrightness(TUBE_BRIGHTNESS);
  tube_.setBlinkRate(BLINK_OFF);
}

/**
 * Update value on a segment display
 */
void update_tube(Seeed_Digital_Tube& tube_, const uint8_t& value) {
  tube_.displayNum(value);
}

void setup() {
    Serial.begin(9600);
    #ifdef DEBUG
    Serial.println("\nStart");
    #endif

    Wire.begin();
    
    delay(50);

    // Set up pins to read the different buttons
    pinMode(RESET_PIN_READ, INPUT_PULLUP);
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(MODE_PIN_1, INPUT_PULLUP);
    pinMode(MODE_PIN_2, INPUT_PULLUP);

    // Set up 4 segment displays
    setup_tube(tube1, I2C_ADDR_DISPLAY_1);
    setup_tube(tube2, I2C_ADDR_DISPLAY_2);
    setup_tube(tube3, I2C_ADDR_DISPLAY_3);
    setup_tube(tube4, I2C_ADDR_DISPLAY_4);

    // Assign functions to the 4 encoders
    assign_function_handles(versatile_encoder1);
    assign_function_handles(versatile_encoder2);
    assign_function_handles(versatile_encoder3);
    assign_function_handles(versatile_encoder4);

    tube1.displayNum(num_1);
    tube2.displayNum(num_2);
    tube3.displayNum(num_3);
    tube4.displayNum(num_4);

    timing = millis();

}

void loop() {
    // Read periphals
    reset = !digitalRead(RESET_PIN_READ);
    red_button = !digitalRead(RED_BUTTON);
    mode_1 = !digitalRead(MODE_PIN_1);
    mode_2 = !digitalRead(MODE_PIN_2);

    // If reset is true, send reset switch and reset values of the encoders
    if (reset) {
#ifndef DEBUG
      uint8_t values[6] = { 255, 255, 255, 255, mode, red_button };
      Serial.write(values, sizeof(values));
#else
      Serial.println("Reset button pressed.");
#endif
      num_1 = 10;
      tube1.displayNum(num_1);
      num_2 = 20;
      tube2.displayNum(num_2);
      num_3 = 30;
      tube3.displayNum(num_3);
      num_4 = 40;
      tube4.displayNum(num_4);
      delay(1000);
    }

    // mode_1 and mode_2 are connected to a 3 way switch.
    if (mode_1) {
      mode = Mode::EASY_COLORS;
    } else if (mode_1 == mode_2) {
      mode = Mode::NORMAL;
    } else if (mode_2) {
      mode = Mode::HARD;
    }

    // Do the encoder reading and processing
    if (versatile_encoder1.ReadEncoder()) {
        // Do something here whenever an encoder action is read
        update_tube(tube1, num_1);
    }

    if (versatile_encoder2.ReadEncoder()) {
        // Do something here whenever an encoder action is read
        update_tube(tube2, num_2); 
    }

    if (versatile_encoder3.ReadEncoder()) {
        // Do something here whenever an encoder action is read
        update_tube(tube3, num_3); 
    }

    if (versatile_encoder4.ReadEncoder()) {
        // Do something here whenever an encoder action is read
        update_tube(tube4, num_4);
    }

    // Send update when timout is reached
    if (millis() - timing > (UPDATES * 1000) ) {
      uint8_t values[6] = { num_1, num_2, num_3, num_4, mode, red_button };
#ifndef DEBUG
        Serial.write(values, sizeof(values));
#else
        if (red_button) {
          Serial.print("Red button pressed.");
        }

        switch (mode)
        {
          case Mode::EASY_COLORS:
            Serial.println("Easy mode.");
            break;
          case Mode::NORMAL:
            Serial.println("Normal mode.");
            break;
          case Mode::HARD:
            Serial.println("Hard mode.");
            break;
          default:
            break;
        }

        Serial.print("[");
        Serial.print(values[0]);
        Serial.print(", ");
        Serial.print(values[1]);
        Serial.print(", ");
        Serial.print(values[2]);
        Serial.print(", ");
        Serial.print(values[3]);
        Serial.println("]");
#endif
      timing = millis();
    }
} 

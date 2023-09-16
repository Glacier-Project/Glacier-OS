/*
 * Glacier OS
 * Copyright (C) 2023 Johnny Stene
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#define KEYPAD_KEY_UP               0x10
#define KEYPAD_KEY_DOWN             0x11
#define KEYPAD_KEY_LEFT             0x12
#define KEYPAD_KEY_RIGHT            0x13
#define KEYPAD_KEY_OK               0x14
#define KEYPAD_KEY_CANCEL           0x15
#define KEYPAD_KEY_POWER            0x16
#define KEYPAD_KEY_VOLUME_UP        0x17
#define KEYPAD_KEY_VOLUME_DOWN      0x18
#define KEYPAD_KEY_SPECIAL_LEFT     0x19
#define KEYPAD_KEY_SPECIAL_RIGHT    0x1A
#define KEYPAD_KEY_SHIFT            0x1B
#define KEYPAD_KEY_CONTROL          0x1C

/*
 * ButtonMatrix
 * Stores information about button matrices.
 *
 * pulse_pins : Array of pin numbers. These will be pulsed LOW when reading the corresponding line.
 * sense_pins : Array of pin numbers. These will be pulled HIGH normally, and will sense when they are being dropped LOW.
 * values     : 2-dimensional array. First index corresponds to each pulse pin, second corresponds to each sense pin. Used to translate.
 */
class ButtonMatrix {
public:
    int pulse_pins[16];
    int sense_pins[16];
    int values[16][16];
};

int pressed[128]; // Enough space for the whole ASCII table. Each integer is how many times
ButtonMatrix current_button_matrix; // This will be set by drivers
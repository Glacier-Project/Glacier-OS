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

#ifndef BRINGUP_HPP
#define BRINGUP_HPP

int lcd_pins[5] = {1, 2, 3, 5, 10};
int keypad_out_pins[4] = {6, 7, 8, 9};
int keypad_in_pins[4] = {11, 12, 13, 14};

void bringup() {
    // Init LCD pins
    for(int i = 0; i < 5; i++) {
        gpio_init(lcd_pins[i]);
        gpio_set_dir(lcd_pins[i], GPIO_OUT);
    }

    // Init keypad pins
    for(int i = 0; i < 4; i++) {
        gpio_init(keypad_in_pins[i]);
        gpio_set_dir(keypad_in_pins[i], GPIO_IN);
        pinMode(keypad_in_pins[i], INPUT_PULLDOWN);
    }

    for(int i = 0; i < 4; i++) {
        gpio_init(keypad_out_pins[i]);
        gpio_set_dir(keypad_out_pins[i], GPIO_OUT);
    }

    // Init cellular pins
    Serial1.setTX(16);
    Serial1.setRX(17);
}

#endif
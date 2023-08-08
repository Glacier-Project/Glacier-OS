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

class IME {
public:
    void ime_wait_keypress() {

    }
protected:
    uint32_t last_keypress_time;
};

class IME_TripleClick : IME {
public:
    void ime_wait_keypress() {
        for(;;) {
            char key = keypad_get_key();
            if(key != '\0') {

            } else if(global_timer - last_keypress_time > 1000) {

            }
        }
    }
protected:
    int current_cycle_pos = 0;
    char last_pressed_key = '\0';
    
    char key_cycle[][] = {
        {'.', ',', '?', '!', '@', '$', '1', '\0', '\0'},
        {'a', 'b', 'c', 'A', 'B', 'C', '2', '\0', '\0'},
        {'d', 'e', 'f', 'D', 'E', 'F', '3', '\0', '\0'},
        {'g', 'h', 'i', 'G', 'H', 'I', '4', '\0', '\0'},
        {'j', 'k', 'l', 'J', 'K', 'L', '5', '\0', '\0'},
        {'m', 'n', 'o', 'M', 'N', 'O', '6', '\0', '\0'},
        {'p', 'q', 'r', 's', 'P', 'Q', 'R', 'S', '7'},
        {'t', 'u', 'v', 'T', 'U', 'V', '8', '\0', '\0'},
        {'w', 'x', 'y', 'z', 'W', 'X', 'Y', 'Z', '9'},
        {':', ')', '(', '%', '^', '&', '*', '\0', '\0'},
        {' ', '0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
        {'+', '-', '=', '/', '\'', '"', '#', '\0', '\0'}
    };

    char key_translation[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '0', '#'};
    
};

IME current_ime;
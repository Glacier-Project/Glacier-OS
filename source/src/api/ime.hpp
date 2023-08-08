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
    char ime_wait_keypress() {

    }
protected:
    uint32_t last_keypress_time;
};

class IME_TripleClick : IME {
public:
    char ime_wait_keypress() {
        for(;;) {
            char key = keypad_get_key();
            if(key != '\0') {
                if(key == last_pressed_key) {
                    current_cycle_pos ++;
                    if(get_key == '\0') current_cycle_pos = 0;
                } else {
                    current_cycle_pos = 0;
                    last_pressed_key = key;
                }
            } else if(global_timer - last_keypress_time > 1000) {
                char translated = get_key();
                if(translated != '\0') return translated;
            }
        }
    }
protected:
    int current_cycle_pos = 0;
    char last_pressed_key = '\0';
    
    char key_cycle[12][10] = {
        {'.', ',', '?', '!', '@', '$', '1', '\0', '\0', '\0'},
        {'a', 'b', 'c', 'A', 'B', 'C', '2', '\0', '\0', '\0'},
        {'d', 'e', 'f', 'D', 'E', 'F', '3', '\0', '\0', '\0'},
        {'g', 'h', 'i', 'G', 'H', 'I', '4', '\0', '\0', '\0'},
        {'j', 'k', 'l', 'J', 'K', 'L', '5', '\0', '\0', '\0'},
        {'m', 'n', 'o', 'M', 'N', 'O', '6', '\0', '\0', '\0'},
        {'p', 'q', 'r', 's', 'P', 'Q', 'R', 'S', '7', '\0'},
        {'t', 'u', 'v', 'T', 'U', 'V', '8', '\0', '\0', '\0'},
        {'w', 'x', 'y', 'z', 'W', 'X', 'Y', 'Z', '9', '\0'},
        {':', ')', '(', '%', '^', '&', '*', '\0', '\0', '\0'},
        {' ', '0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
        {'+', '-', '=', '/', '\'', '"', '#', '\0', '\0', '\0'}
    };

    char key_translation[12] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '0', '#'};
    
    char get_key() {
        if(last_pressed_key == '\0') return '\0';

        for(int i = 0; i<12; i++) {
            if(last_pressed_key == key_translation[i]) {
                return key_cycle[i][current_cycle_pos];
            }
        }
    }
};

IME current_ime;
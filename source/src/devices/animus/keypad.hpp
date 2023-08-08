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

char keypad_translation[4][4] = {
    {KEY_CANCEL, KEY_OK, KEY_DOWN, KEY_UP},
    {'1', '4', '7', '*'},
    {'2', '5', '8', '0'},
    {'3', '6', '9', '#'}
};

char keypad_get_key() {
    for(int out = 0; out < 4; out++) {
        digitalWrite(keypad_out_pins[out], HIGH);
        for(int in = 0; in < 4; in++) {
            if(digitalRead(keypad_in_pins[in]) == HIGH) {
                return keypad_translation[out][in];
            }
        }
        digitalWrite(keypad_out_pins[out], LOW);
    }
    return '\0';
}

char keypad_wait_key() {
    char in = '\0';
    while(in == '\0') {
        in = keypad_get_key();
    }
    return in;
}

/*
uint16_t key_translation[4][4] = {
    {KEYPAD_KEY_CANCEL, KEYPAD_KEY_OK, KEYPAD_KEY_DOWN, KEYPAD_KEY_UP},
    {KEYPAD_KEY_1,KEYPAD_KEY_4,KEYPAD_KEY_7,KEYPAD_KEY_ASTERISK},
    {KEYPAD_KEY_2,KEYPAD_KEY_5,KEYPAD_KEY_8,KEYPAD_KEY_0},
    {KEYPAD_KEY_3,KEYPAD_KEY_6,KEYPAD_KEY_9,KEYPAD_KEY_POUND}
}

void keypad_refresh() {
    for(int out = 0; out < 4; out++) {
        digitalWrite(keypad_out_pins[out], HIGH);
        for(int in = 0; in < 4; in++) {
            if(digitalRead(keypad_in_pins[in]) == HIGH) {
                key_status |= key_translation[out][in];
            } else {
                key_status &= ~key_translation[out][in];
            }
        }
        digitalWrite(keypad_out_pins[out], LOW);
    }
}*/
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

void dialer_in_call() {
    while(cellular_current_state == CELLULAR_STATE_IN_CALL) {
        // TODO: display
    }
}

void dialer_call(String number) {
    cellular_call_dial(number);
    dialer_in_call();
}

void dialer_ring(String number) {
    // TODO: display
    debug("Ringing\n");
    bool answer = false;

    if(answer) {
        cellular_call_answer();
        dialer_in_call();
        return;
    }
    
    cellular_call_end();
}

void dialer_dialpad(char start_character) {
    debug("Starting dialpad\n");
    String number;
    if(start_character) number = number + start_character; // If we've been passed a number from the home screen, add it here

    for(;;) {
        // Render screen
        display_clear();
        if(number.length() * 8 <= DISPLAY_WIDTH) // If the number fits, draw it normally
            display_draw_string(0, 0, (char*) number.c_str(), 1);
        else { // Otherwise, only draw the last few digits
            String display_string = number.substr(number.length() - (DISPLAY_WIDTH / 8), number.length());
            display_draw_string(0, 0, (char*) display_string.c_str(), 1);
        }
        display_draw_string((display_width() / 2) - 16, display_height() - 8, STRING_DIAL, 1);

        // Get keypresses
        char key = keypad_wait_key();
        if(key == KEY_OK) { // OK is to dial
            debug("Dialing %s\n", number.c_str());
            dialer_call(number);
            return;
        } else if(key == KEY_CANCEL) { // C deletes a character, or exits if the string is empty
            if(number.length() == 0) return;
            else number.pop_back();
        } else if(key >= '0' && key <= '9') { // Add number
            number = number + key;
        }
    }

}

void start_dialer() {
    dialer_dialpad('\0');
}

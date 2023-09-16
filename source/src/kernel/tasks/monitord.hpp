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

void monitord(void*) {
    // General system cleanup
    multitasking_cleanup();

    // Check for new keypad input
    for(int pulse = 0; pulse < 16; pulse++) {
        digitalWrite(current_button_matrix.pulse_pins[pulse], LOW);
        for(int sense = 0; sense < 16; sense++) {
            if(digitalRead(current_button_matrix.sense_pins[sense]) == HIGH) {
                pressed[(int) current_button_matrix.values[pulse][sense]] ++;
            } else {
                pressed[(int) current_button_matrix.values[pulse][sense]] = 0;
            }
        }
        digitalWrite(current_button_matrix.pulse_pins[pulse], HIGH);
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);
}
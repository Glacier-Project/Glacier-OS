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

typedef struct {
    int in_use;
    uint8_t* icon;
    char* name;
    void (*start_function)();
} app_entry;

app_entry apps[16];

void add_application_entry(uint8_t* icon, char* name, void(*start_function)()) {
    app_entry new_entry;
    new_entry.in_use = 1;
    new_entry.icon = icon;
    new_entry.name = name;
    new_entry.start_function = start_function;
    
    for(int i = 0; i < MAXIMUM_APP_COUNT; i++) {
        if(apps[i].in_use == 0) {
            apps[i] = new_entry;
            return;
        }
    }

    panic("Not enough app slots");
}

void draw_app_screen(app_entry current_entry) {
    display_draw_bitmap(26, 8, 32, 32, current_entry.icon);
    display_draw_string(10, 0, current_entry.name, 1);

    display_draw_string(0, display_height() - 8, STRING_OPEN, 1);
    display_draw_string(display_width() - 32, display_height() - 8, STRING_EXIT, 1);
}

void start_home_menu() {
    for(;;) {
        display_draw_line(0, 9, display_width() - 1, 9, 1);

        int dx = 0;

        // Draw cell strength
        int strength = cellular_strength();
        if(strength > 0) {
            display_draw_pixel(1, 7, 1);

            if(strength > 33) {

            } 
            
            if(strength > 66) {

            }

            if(strength > 80) {

            }
            dx += 8;
        } else {
            display_draw_string(dx, 0, STRING_NO_CELL, 1);
            dx += 8 * 7;
        }
        
        display_draw_string(0, display_height() - 8, STRING_MENU, 1);
        display_draw_string(display_width() - 32, display_height() - 8, STRING_DIAL, 1);
    }
}

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
    int in_use; // Whether or not this entry is in use
    uint8_t* icon; // Bitmap for the app icon
    String name; // Name for the app
    void (*start_function)(); // Function to start the app
} app_entry;

app_entry apps[MAXIMUM_APP_COUNT]; // Table for all registered applications

void add_application_entry(uint8_t* icon, char* name, void(*start_function)()) {
    debug("Adding app entry for \"%s\"\n", name);

    // Populate an app entry
    app_entry new_entry;
    new_entry.in_use = 1;
    new_entry.icon = icon;
    new_entry.name = name;
    new_entry.start_function = start_function;
    
    // Check for a free slot
    for(int i = 0; i < MAXIMUM_APP_COUNT; i++) {
        if(apps[i].in_use == 0) {
            apps[i] = new_entry;
            return;
        }
    }

    // Will only get here if there isn't enough
    panic("Not enough app slots");
}

void app_picker() {
    debug("Starting app picker\n");
    int current_app = 0;
    
    for(;;) {
        debug("Displaying app %s\n", apps[current_app].name.c_str());
        // Render screen for currently chosen app
        display_clear();
        display_draw_bitmap((display_width() / 2) - 16, 8 + ((display_height() - 16) / 2) - 16, 32, 32, apps[current_app].icon);
        display_draw_string((display_width() / 2) - (apps[current_app].name.length() * 8 / 2), 0, (char*) apps[current_app].name.c_str(), 1);
        display_draw_string((display_width() / 2) - 16, display_height() - 8, STRING_OPEN, 1);

        char key = keypad_wait_key();
        switch(key) {
            case 'D':
                if(current_app < MAXIMUM_APP_COUNT - 1 && apps[current_app + 1].in_use) current_app++;
                break;
            case 'U':
                if(current_app > 0) current_app --;
                break;
            case 'O':
                apps[current_app].start_function();
                return; // We want to drop to home screen when exiting whatever app we start
            case 'C':
                return; // Exit to home screen
        }
    }
}

void start_home_menu() {
    for(;;) {
        debug("Entering home menu\n");
        display_draw_line(0, 9, display_width() - 1, 9, 1);
        display_draw_string((display_width() / 2) - 16, display_height() - 8, STRING_MENU, 1);

        char key = keypad_wait_key();
        if(key != '\0') {
            if(key == 'O') {
                app_picker();
            } else if(key >= '0' && key <= '9') {
                dialer_dialpad(key);
            }

            display_clear();
        }
    }
}

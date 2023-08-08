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

// GraphicsManager
std::vector<GraphicsObject> gui_objects;
bool gui_should_exit = false;

void gui_add(GraphicsObject object) {
    if(object.requested_height > gui_max_height()) object.height = gui_max_height();
    else object.height = object.requested_height;

    gui_objects.push_back(object);
}

int gui_list(String title, std::vector<String> items) {
    debug("Showing list %s\n", title.c_str());
    int current_selection = 0;

    if(items.size() == 0) {
        debug("List is blank, returning\n");
        return -1;
    }

    for(;;) {
        debug("Selected item: %d\n", current_selection);
        display_clear();
        display_draw_string((display_width() / 2) - (title.length() * 8 / 2), 0, (char*) title.c_str(), 1);
        display_draw_string((display_width() / 2) - 16, display_height() - 8, STRING_OPEN, 1);

        display_fill_rect(0, 8, display_width(), 8, 1);
        display_draw_string(0, 8, (char*) items.at(current_selection).c_str(), 0);
        for(int i = 0; i < 2; i++) {
            if(items.size() - current_selection - i - 1 > 0) {
                display_draw_string(0, 16 + (8 * i), (char*) items.at(current_selection + 1 + i).c_str(), 1);
            } else break;
        }

        char key = keypad_wait_key();
        if(key == 'D') {
            if(current_selection + 1 < items.size()) {
                current_selection ++;
            }
        } else if(key == 'U') {
            if(current_selection >= 1) current_selection --;
        } else if(key == 'O') {
            return current_selection;
        } else if(key == 'C') {
            return -1;
        }
    }
}

void gui_enter() {
    int current_selection = 0;

    for(;;) {
        

        for(int i = 0; i < gui_objects.size(); i++) {
            // Check if object should be selected
            if(i == current_selection) gui_objects.at(i).selected = true;
            else gui_objects.at(i).selected = false;

            // Run update function
            gui_objects.at(i).update();

            // TODO: copy framebuffer to screen
        }

        // Get keypresses
        // TODO: IME
        // TODO: Check if object can be selected before selecting it
        // TODO: Pass input to object
        char key = keypad_wait_key();
        if(key == 'C') break;
        else if(key == 'U') {
            if(current_selection > 0) current_selection--;
        } else if(key == 'D') {
            if(current_selection < gui_objects.size()) current_selection++;
        } else {
            
        }
    }
}

uint16_t gui_max_height() {
    return display_height() - 8;
}
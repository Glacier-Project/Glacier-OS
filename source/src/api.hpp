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

// TODO: Should probably move this all to separate files

#ifndef API_HPP
#define API_HPP

#include <stdbool.h>
#include <stdint.h>

// Kernel functions
void shutdown(); 

// Bringup functions
void bringup();

// Contacts API
typedef struct {
    String contents;
    bool incoming;
} message_t;

typedef struct {
    int duration;
    bool incoming;
} call_t;

typedef struct {
    String name;
    String number;
    std::vector<message_t> messages;
    std::vector<call_t> calls;
} contact_t;

std::vector<contact_t> contacts;

int contact_search();

// Keypad functions
char keypad_wait_key();
char keypad_get_key();

// Display functions
void display_init();
void display_shutdown();
uint16_t display_width();
uint16_t display_height();
void display_clear();
void display_draw_pixel(uint16_t x, uint16_t y, int value);
void display_fill_rect(uint16_t x, uint16_t y, int width, int height, int value);
void display_draw_bitmap(uint16_t x, uint16_t y, int width, int height, uint8_t* data);

void display_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int value) {
    if(x1 == x2) display_fill_rect(x1, y1, 1, y2 - y1, value);
    else if(y1 == y2) display_fill_rect(x1, y1, x2 - x1, 1, value);
    else {
        // TODO: DDA line drawing
    }
}

void display_draw_rect(uint16_t x, uint16_t y, int width, int height, int value) {
    display_draw_line(x, y, x + width, y, value);
    display_draw_line(x, y, x, y + height, value);
    display_draw_line(x, y + height, x + width, y + height, value);
    display_draw_line(x + width, y, x + width, y + height, value);
}

void display_fill(int value) {
    display_fill_rect(0, 0, display_width(), display_height() + 1, value);
}

void display_draw_circle(uint16_t x, uint16_t y, int r, int value) {
    // TODO: this
}

void display_fill_circle(uint16_t x, uint16_t y, int r, int value) {
    // TODO: this
}

void display_draw_character(uint16_t x, uint16_t y, char character, int value);

void display_draw_string(uint16_t x, uint16_t y, char* text, int value) {
    uint16_t dx = x;
    uint16_t dy = y;
    for(int i = 0; text[i] != '\0'; i++) {
        if(text[i] == '\n') {
            dx = x;
            dy += 8;
        } else if(text[i] == '\t') {
            dx += 8 * 4;
        } else {
            display_draw_character(dx, dy, text[i], value);
            dx += 8;
        }
    }
}

// GUI toolkit
int gui_list(String title, std::vector<String> items) {
    debug("Showing list %s\n", title.c_str());
    int current_selection = 0;

    if(items.size() == 0) {
        debug("List is blank, returning\n");
        return -1;
    }

    for(;;) {
        display_clear();
        display_draw_string((display_width() / 2) - (title.length() * 8 / 2), 0, (char*) title.c_str(), 1);
        display_draw_string((display_width() / 2) - 16, display_height() - 8, STRING_OPEN, 1);

        display_fill_rect(0, 8, display_width(), 8, 1);
        display_draw_string(0, 8, (char*) items.at(current_selection).c_str(), 0);
        /*for(int i = 0; i < 2; i++) {
            if(items.size() - current_selection - i > 0) {
                display_draw_string(0, 16 + (8 * i), (char*) items.at(current_selection).c_str(), 1);
            }
        }*/

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

// Cellular functions
#define CELLULAR_STATE_NORMAL 0
#define CELLULAR_STATE_RINGING 1
#define CELLULAR_STATE_IN_CALL 2
#define CELLULAR_STATE_ERROR 3

int cellular_current_state = CELLULAR_STATE_NORMAL;

void cellular_init();
String cellular_get_manufacturer();
String cellular_get_model();
int cellular_available();
void cellular_refresh();
void cellular_sms_send(String recipient, String contents);
void cellular_sms_delete_all();
void cellular_call_dial(String number);
void cellular_call_answer();
void cellular_call_end();

// IME functions

#endif
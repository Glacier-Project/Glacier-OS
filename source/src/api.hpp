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
    String name;
    String number;
    bool valid;
} contact_t;

std::list<contact_t> contacts;

contact_t contact_search_name() {
    contact_t contact;
    contact.valid = false;
    return contact;
}

contact_t contact_search_number() {
    contact_t contact;
    contact.valid = false;
    return contact;
}

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

// Keypad functions
#define KEYPAD_KEY_CANCEL   0b0000000000000001
#define KEYPAD_KEY_OK       0b0000000000000010
#define KEYPAD_KEY_DOWN     0b0000000000000100
#define KEYPAD_KEY_UP       0b0000000000001000
#define KEYPAD_KEY_1        0b0000000000010000
#define KEYPAD_KEY_2        0b0000000000100000
#define KEYPAD_KEY_3        0b0000000001000000
#define KEYPAD_KEY_4        0b0000000010000000
#define KEYPAD_KEY_5        0b0000000100000000
#define KEYPAD_KEY_6        0b0000001000000000
#define KEYPAD_KEY_7        0b0000010000000000
#define KEYPAD_KEY_8        0b0000100000000000
#define KEYPAD_KEY_9        0b0001000000000000
#define KEYPAD_KEY_ASTERISK 0b0010000000000000
#define KEYPAD_KEY_0        0b0100000000000000
#define KEYPAD_KEY_POUND    0b1000000000000000

uint16_t key_status = 0x0000;
void keypad_refresh();

// IME functions

#endif
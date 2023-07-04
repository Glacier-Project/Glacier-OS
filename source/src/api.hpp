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

#ifndef API_HPP
#define API_HPP

#include <stdbool.h>
#include <stdint.h>

// Kernel functions
void shutdown(); 

// Bringup functions
void bringup();

// Display functions
void display_init();
void display_shutdown();
int display_width();
int display_height();
void display_clear();
void display_draw_pixel(int x, int y, int value);
void display_fill_rect(int x, int y, int width, int height, int value);
void display_draw_bitmap(int x, int y, int width, int height, uint8_t* data);

void display_draw_line(int x1, int y1, int x2, int y2, int value) {
    if(x1 == x2) display_fill_rect(x1, y1, 1, y2 - y1, value);
    else if(y1 == y2) display_fill_rect(x1, y1, x2 - x1, 1, value);
    else {
        // TODO: DDA line drawing
    }
}

void display_draw_rect(int x, int y, int width, int height, int value) {
    display_draw_line(x, y, x + width, y, value);
    display_draw_line(x, y, x, y + height, value);
    display_draw_line(x, y + height, x + width, y + height, value);
    display_draw_line(x + width, y, x + width, y + height, value);
}

void display_fill(int value) {
    display_fill_rect(0, 0, display_width(), display_height() + 1, value);
}

void display_draw_circle(int x, int y, int r, int value) {
    // TODO: this
}

void display_fill_circle(int x, int y, int r, int value) {
    // TODO: this
}

void display_draw_character(int x, int y, char character, int value);

void display_draw_string(int x, int y, char* text, int value) {
    uint8_t dx = x;
    uint8_t dy = y;
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
String cellular_get_modem_manufacturer();
String cellular_get_modem_model();
int cellular_available();
void cellular_init();
void cellular_shutdown();
void cellular_get_imei(char* buffer, int len);
void cellular_answer();
void cellular_hang_up();
void cellular_get_caller(char* buffer, int len);
void cellular_get_text(char* sender_buffer, int sender_len, char* message_buffer, int message_len);
int cellular_strength();

#endif
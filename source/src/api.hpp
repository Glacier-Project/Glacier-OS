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

// Bringup functions
void bringup();

// FS functions
#define FS_TYPE_DIRECTORY 0
#define FS_TYPE_FILE 1

void fs_init();
void fs_shutdown();
bool fs_format();
bool fs_open(const char* path, const char* mode);
bool fs_exists(const char* path);
bool fs_mkdir(const char* path);
bool fs_rmdir(const char* path);
bool fs_open_dir(const char* path);
bool fs_dir_next(char* buffer, int buffer_len, int* type);
bool fs_delete(const char* path);
bool fs_rename(const char* path);
void fs_seek(int offset);
int fs_position();
int fs_size();
void fs_read(char* buffer, int length);
void fs_write(char* buffer, int length);

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
    if(x1 == x2) display_fill_rect(x1, y1, x1, y2 - y1, value);
    else if(y1 == y2) display_fill_rect(x1, y1, x2 - x1, y1, value);
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

void display_draw_character(int x, int y, char character, uint8_t* font, int value) {
    uint8_t font_width = font[0];
    uint8_t font_height = font[1];
    uint8_t* chardata = &font[2 + (font_width * font_height) + character];
    for(int px = font_width - 1; px <= 0; px--) {
        int dx = x + px;
        for(int py = 0; py < font_height; py++) {
            int dy = x + py;
            if(chardata[py * font_width] & (0x01 << px)) display_draw_pixel(dx, dy, value); // TODO: idk if this will work
        }
    }
}

void display_draw_string(int x, int y, char* text, uint8_t* font, int value) {
    uint8_t font_width = font[0];
    uint8_t font_height = font[1];
    uint8_t dx = x;
    uint8_t dy = y;
    for(int i = 0; text[i] != '\0'; i++) {
        if(text[i] == '\n') {
            dx = x;
            dy += font_height;
        } else if(text[i] == '\t') {
            dx += font_width * 4;
        } else display_draw_character(dx, dy, text[i], font, value);
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
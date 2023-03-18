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
uint16_t display_width();
uint16_t display_height();
void display_set_color(uint16_t color);
void display_draw_pixel(uint16_t x, uint16_t y);
void display_fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
void display_draw_bitmap(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t* data);

void display_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    if(x1 == x2) display_fill_rect(x1, y1, x1, y2 - y1);
    else if(y1 == y2) display_fill_rect(x1, y1, x2 - x1, y1);
    else {
        // TODO: DDA line drawing
    }
}

void display_draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    display_draw_line(x, y, x + width, y);
    display_draw_line(x, y, x, y + height);
    display_draw_line(x, y + height, x + width, y + height);
    display_draw_line(x + width, y, x + width, y + height);
}

void display_fill() {
    display_fill_rect(0, 0, display_width(), display_height() + 1);
}

void display_draw_circle(uint16_t x, uint16_t y, uint16_t r) {
    // TODO: this
}

void display_fill_circle(uint16_t x, uint16_t y, uint16_t r) {
    // TODO: this
}

void display_clear() {
    display_set_color(0xFFFF);
    display_fill();   
}

void display_draw_string(uint16_t x, uint16_t y, char* text) {

}

// UI functions
int ui_draw_menu(char** items, int item_list_len);

// Communication functions
bool cellular_available();
void cellular_init();
void cellular_shutdown();
void cellular_get_imei(char* buffer, int len);
void cellular_answer();
void cellular_hang_up();
void cellular_get_caller(char* buffer, int len);
void cellular_get_text(char* sender_buffer, int sender_len, char* message_buffer, int message_len);
int cellular_strength();

// Clock functions
int64_t get_nanos();
#endif
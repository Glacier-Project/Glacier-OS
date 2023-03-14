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
void display_set_color(uint16_t color);
void display_draw_pixel(int x, int y);
void display_draw_line(int x1, int y1, int x2, int y2);
void display_draw_rect(int x, int y, int width, int height);
void display_fill_rect(int x, int y, int width, int height);
void display_draw_circle(int x, int y, int r);
void display_fill_circle(int x, int y, int r);
void display_draw_bitmap(int x, int y, int width, int height, uint16_t data);
void display_fill();
void display_draw_string(int x, int y, char* text);

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
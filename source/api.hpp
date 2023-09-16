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

// Debug functions
void panic();

// Display functions
void display_init();
void display_shutdown();
uint16_t display_width();
uint16_t display_height();
void display_clear();
void display_draw_pixel(uint16_t x, uint16_t y, int value);
void display_fill_rect(uint16_t x, uint16_t y, int width, int height, int value);
void display_draw_bitmap(uint16_t x, uint16_t y, int width, int height, uint8_t* data);
void display_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int value);
void display_draw_rect(uint16_t x, uint16_t y, int width, int height, int value);
void display_fill(int value);
void display_draw_circle(uint16_t x, uint16_t y, int r, int value);
void display_fill_circle(uint16_t x, uint16_t y, int r, int value);
void display_draw_character(uint16_t x, uint16_t y, char character, int value);
void display_draw_string(uint16_t x, uint16_t y, char* text, int value);

// Keypad functions


// Multitasking functions
int get_process_pid(String name);
int spawn_process(String name, TaskFunction_t function);
void multitasking_cleanup();
void multitasking_init();
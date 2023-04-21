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

// https://www.robotpark.com/image/data/PRO/91579/Nokia5110.pdf

#ifndef DISPLAY_HPP
#define DISPLAY_HPP
void display_init() { }
void display_draw_pixel(int x, int y, int value) { }
void display_shutdown();
int display_width() { return 0; }
int display_height() { return 0; }
void display_clear() { }
void display_fill_rect(int x, int y, int width, int height, int value) { }
void display_draw_bitmap(int x, int y, int width, int height, uint8_t* data) { }
#endif
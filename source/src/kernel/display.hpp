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
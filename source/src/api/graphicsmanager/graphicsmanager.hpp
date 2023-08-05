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

class GraphicsObject {
public:
    uint32_t framebuffer[display_width() * 8];
    uint16_t text_scroll_speed = 1;
    uint16_t height = 0;
    uint16_t requested_height = 8;

    void update() {

    }

    bool isSelectable() {
        return false;
    }

    void select() {

    }

    void input(char key) {

    }

    void commit() {

    }

protected:
    uint32_t text_clock;
    uint32_t text_finished_time;

    void draw_pixel(uint16_t x, uint16_t y, int value) {
        if(y >= height) return;
        if(x >= display_width()) return;

        if(value) framebuffer[(y * display_width()) + x] = 0;
        else framebuffer[(y * display_width()) + x] = 255;
    }

    void draw_character(uint16_t x, uint16_t y, char character, int value) {
        uint8_t* chardata = &font8x8_basic[character][0];
        for(int dy = 0; dy < 8; dy++) {
            for(int dx = 0; dx < 8; dx++) {
                if((chardata[dy] >> dx) & 0x01) draw_pixel(x + dx, y + dy, value);
            }
        }
    }
    
    void draw_text(uint16_t x, uint16_t y, uint16_t width, char* text, int value) {
        // Text scroll calculations
        uint16_t starting_index = 0;
        uint16_t max_characters = width / 8;
        if(strlen(text) > max_characters) { // See if we actually need to scroll
            if(text_clock >= 1000) { // Wait 1s before scrolling
                starting_index = (text_clock - 1000) / text_scroll_speed; // What position in the string we should start from
                if(strlen(text[starting_index]) == max_characters) { // If we've reached the end,
                    if(text_finished_time == 0) text_finished_time = text_clock; // Start counting the time since we have
                    else if(text_clock - text_finished_time >= 1000) { // Or check to see if we need to reset
                        starting_index = 0;
                        text_clock = 0;
                        text_finished_time = 0;
                    }
                }
            }
        }

        // String drawing function
        uint16_t dx = x;
        uint16_t dy = y;
        for(int i = starting_index; text[i] != '\0'; i++) {
            if(i >= starting_index + max_characters) return; // Make sure we're not drawing past the specified width
            if(text[i] == '\n') {
                dx = x;
                dy += 8;
            } else if(text[i] == '\t') {
                dx += 8 * 4;
            } else {
                draw_character(dx, dy, text[i], value);
                dx += 8;
            }
        }
    }

    void draw_hline(uint16_t y, int value) {
        for(int x = 0; x < display_width(); x++) {
            draw_pixel(x, y, value);
        }
    }

    void draw_vline(uint16_t x, int value) {
        for(int y = 0; y < height; y++) {
            draw_pixel(x, y, value);
        }
    }

    void fill(int value) { 
        for(int x = 0; x < display_width(); x++) {
            for(int y = 0; y < height; y++) {
                draw_pixel(x, y, value);
            }
        }
    }
};

class GUILabel : GraphicsObject {
public:
    String label;

    void update() {
        fill(0);
        draw_text(0, 0, display_width(), label.c_str(), 1);
    }
};
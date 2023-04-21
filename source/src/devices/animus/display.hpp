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

// TODO: set these
#define ANIMUS_LCD_SCE 0
#define ANIMUS_LCD_RESET 0
#define ANIMUS_LCD_DC 0
#define ANIMUS_LCD_SDIN 0
#define ANIMUS_LCD_SCLK 0

#define ANIMUS_LCD_WIDTH 84
#define ANIMUS_LCD_HEIGHT 5

uint8_t animus_lcd_framebuffer[ANIMUS_LCD_WIDTH][ANIMUS_LCD_HEIGHT];

void animus_lcd_send_command(uint8_t command) {
    gpio_put(ANIMUS_LCD_DC, 0);
    gpio_put(ANIMUS_LCD_SCE, 0);
    // TODO: does shiftOut work with arduino-pico?
    shiftOut(ANIMUS_LCD_SDIN, ANIMUS_LCD_SCLK, command);
    gpio_put(ANIMUS_LCD_SCE, 1);
}

void animus_lcd_send_data(uint8_t data) {
    gpio_put(ANIMUS_LCD_DC, 1);
    gpio_put(ANIMUS_LCD_SCE, 0);
    // TODO: does shiftOut work with arduino-pico?
    shiftOut(ANIMUS_LCD_SDIN, ANIMUS_LCD_SCLK, data);
    gpio_put(ANIMUS_LCD_SCE, 1);
}

void display_init() {
    // Reset LCD to prevent damage
    gpio_put(ANIMUS_LCD_RESET, 0);
    delay(50);
    gpio_put(ANIMUS_LCD_RESET, 1);

    // Init LCD
    animus_lcd_send_command(0x21); // Extended commands
    animus_lcd_send_command(0xBF); // Contrast
    animus_lcd_send_command(0x04); // Temp. coefficient
    animus_lcd_send_command(0x14); // LCD bias mode 1:48
    animus_lcd_send_command(0x0C); // Normal mode
}

void animus_lcd_set_address(int x, int y) {
    if(x < 0 || x > 83 || y < 0 || y > 5) return;
    animus_lcd_send_command(0x80 | x);
    animus_lcd_send_command(0x40 | y);
}

void animus_lcd_push_framebuffer() {
    animus_lcd_set_address(0, 0);
    for(int x = 0; x < ANIMUS_LCD_WIDTH; x++) {
        for(int y = 0; y < ANIMUS_LCD_HEIGHT; y++) {
            animus_lcd_send_data(animus_lcd_framebuffer[x][y]);
        }
    }
}

// TODO: Should work?
void display_draw_pixel(int x, int y, int value) {
    if(x < 0 || x > 83 || y < 0 || y > 47) return;
    int address_y = 4;
    for(;;) {
        if(y >= 8) {
            y -= 8;
            address_y --;
        } else break;
    }

    if(val > 1) val = 1;
    if(val < 0) val = 0;
    animus_lcd_framebuffer[x][address_y] |= (val << y);
    animus_lcd_set_address(x, address_y);
    animus_lcd_send_data(animus_lcd_framebuffer[x][address_y]);
}

void display_shutdown();
int display_width() { return ANIMUS_LCD_WIDTH; }
int display_height() { return ANIMUS_LCD_HEIGHT * 8; }

void display_clear() {
    for(int x = 0; x < ANIMUS_LCD_WIDTH; x++) {
        for(int y = 0; y < ANIMUS_LCD_HEIGHT; y++) {
            animus_lcd_framebuffer[x][y] = 0x00;
        }
    }
    animus_lcd_push_framebuffer();
}

// TODO: make these more efficient
void display_fill_rect(int x, int y, int width, int height, int value) {
    for(int dx = 0; dx < width; dx++) {
        for(int dy = 0; dy < height; dy++) {
            display_draw_pixel(x + dx, y + dy, value);
        }
    }
}

// TODO: make these more efficient
void display_draw_bitmap(int x, int y, int width, int height, uint8_t* data) {
    int i;
    for(int dx = 0; dx < width; dx++) {
        for(int dy = 0; dy < height; dy++) {
            display_draw_pixel(x + dx, y + dy, data[i]);
            i ++;
        }
    }
}

#endif
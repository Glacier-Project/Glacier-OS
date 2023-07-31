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
#define LCD_SCE 1
#define LCD_RESET 5
#define LCD_DC  10
#define LCD_SDIN 3
#define LCD_SCLK 2

#define LCD_WIDTH 84
#define LCD_HEIGHT 6

#define LCD_BIT_ORDER MSBFIRST

#define LCD_COMMAND_NOP                                          0b00000000
#define LCD_COMMAND_FUNCTION_SET                                 0b00100000
#define LCD_COMMAND_FUNCTION_SET_ACTIVE                          0b00000000
#define LCD_COMMAND_FUNCTION_SET_INACTIVE                        0b00000100
#define LCD_COMMAND_FUNCTION_SET_HORIZONTAL_ADDRESSING           0b00000000
#define LCD_COMMAND_FUNCTION_SET_VERTICAL_ADDRESSING             0b00000010
#define LCD_COMMAND_FUNCTION_SET_BASIC_ISA                       0b00000000
#define LCD_COMMAND_FUNCTION_SET_EXTENDED_ISA                    0b00000001
#define LCD_COMMAND_DISPLAY_CONTROL                              0b00001000
#define LCD_COMMAND_DISPLAY_CONTROL_BLANK                        0b00001000
#define LCD_COMMAND_DISPLAY_CONTROL_NORMAL                       0b00001100
#define LCD_COMMAND_DISPLAY_CONTROL_ALL_ON                       0b00001001
#define LCD_COMMAND_DISPLAY_CONTROL_INVERTED                     0b00001101
#define LCD_COMMAND_SET_Y_ADDRESS                                0b01000000
#define LCD_COMMAND_SET_X_ADDRESS                                0b10000000
#define LCD_COMMAND_SET_TEMPERATURE_COEFFICIENT                  0b00000100
#define LCD_COMMAND_SET_BIAS_SYSTEM                              0b00010000
#define LCD_COMMAND_SET_CONTRAST                                 0b10000000

uint8_t lcd_framebuffer[LCD_WIDTH][LCD_HEIGHT];

void lcd_send_command(uint8_t command) {
    gpio_put(LCD_SCE, 0);
    gpio_put(LCD_DC, 0);
    shiftOut(LCD_SDIN, LCD_SCLK, LCD_BIT_ORDER, command);
    gpio_put(LCD_SCE, 1);
}

void lcd_send_data(uint8_t data) {
    gpio_put(LCD_SCE, 0);
    gpio_put(LCD_DC, 1);
    shiftOut(LCD_SDIN, LCD_SCLK, LCD_BIT_ORDER, data);
    gpio_put(LCD_SCE, 1);
}

void lcd_set_address(int x, int y) {
    if(x < 0 || x > 83 || y < 0 || y > 5) return;
    lcd_send_command(LCD_COMMAND_SET_X_ADDRESS | x);
    lcd_send_command(LCD_COMMAND_SET_Y_ADDRESS | y);
}

void lcd_push_framebuffer() {
    lcd_set_address(0, 0);
    for(int y = 0; y < LCD_HEIGHT; y++) {
        for(int x = 0; x < LCD_WIDTH; x++) {
            lcd_send_data(lcd_framebuffer[x][y]);
        }
    }
}

void display_init() {
    // Reset LCD to prevent damage
    gpio_put(LCD_RESET, 0);
    delay(50);
    gpio_put(LCD_RESET, 1);

    // Init LCD
    lcd_send_command(LCD_COMMAND_FUNCTION_SET | LCD_COMMAND_FUNCTION_SET_ACTIVE | LCD_COMMAND_FUNCTION_SET_EXTENDED_ISA | LCD_COMMAND_FUNCTION_SET_HORIZONTAL_ADDRESSING); // Turn on LCD and set extended instruction set
    lcd_send_command(LCD_COMMAND_SET_CONTRAST | 0x3F); // Set contrast
    lcd_send_command(LCD_COMMAND_FUNCTION_SET | LCD_COMMAND_FUNCTION_SET_ACTIVE | LCD_COMMAND_FUNCTION_SET_BASIC_ISA | LCD_COMMAND_FUNCTION_SET_HORIZONTAL_ADDRESSING); // Back to basic ISA
    lcd_send_command(LCD_COMMAND_DISPLAY_CONTROL | LCD_COMMAND_DISPLAY_CONTROL_NORMAL);

    display_clear();

    lcd_send_data(0b11111111);
    lcd_send_data(0b11111111);
    lcd_send_data(0b11111111);
    lcd_send_data(0b00011111);
    lcd_send_data(0b00011111);
    lcd_send_data(0b00011111);
}

void lcd_framebuffer_draw_pixel(int x, int y, int value) {
    if(x < 0 || x > 83 || y < 0 || y > 47) return;
    uint8_t val;
    if(value > 1) val = 0b00000001;
    if(value < 0) val = 0b00000000;
    lcd_framebuffer[x][address_y] |= (val << y);
}

void display_draw_pixel(int x, int y, int value) {
    lcd_framebuffer_draw_pixel(x, y, value);
    lcd_push_framebuffer();
}

void display_shutdown();
int display_width() { return LCD_WIDTH; }
int display_height() { return LCD_HEIGHT * 8; }

void display_clear() {
    for(int x = 0; x < LCD_WIDTH; x++) {
        for(int y = 0; y < LCD_HEIGHT; y++) {
            lcd_framebuffer[x][y] = 0x00;
        }
    }
    lcd_push_framebuffer();
}

void display_fill_rect(int x, int y, int width, int height, int value) {
    for(int dx = 0; dx < width; dx++) {
        for(int dy = 0; dy < height; dy++) {
            lcd_framebuffer_draw_pixel(x + dx, y + dy, value);
        }
    }
    lcd_push_framebuffer();
}

void display_draw_bitmap(int x, int y, int width, int height, uint8_t* data) {
    for(int dx = 0; dx < width; dx++) {
        for(int dy = 0; dy < height; dy++) {
            if(data[(dy * width) + dx] == 1) lcd_framebuffer_draw_pixel(x + dx, y + dy, 1);
        }
    }
    lcd_push_framebuffer();
}

void display_draw_character(int x, int y, char character, int value) {
    uint8_t* chardata = &font8x8_basic[character][0];
    for(int dy = 0; dy < 8; dy++) {
        for(int dx = 0; dx < 8; dx++) {
            if((chardata[dy] >> dx) & 0x01) lcd_framebuffer_draw_pixel(x + dx, y + dy, value);
        }
    }
    lcd_push_framebuffer();
}

#endif
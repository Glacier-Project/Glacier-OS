/*
 * Glacier OS
 * Copyright (C) 2023 Gavin Lyons, Bernhard Bablok, Johnny Stene
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

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Arduino.h>
#include <Print.h>
#include <SPI.h>

#define ANIMUS_TFT_WIDTH            128
#define ANIMUS_TFT_HEIGHT           160

#define ANIMUS_TFT_DELAY            0x80
#define ANIMUS_TFT_NOP              0x00
#define ANIMUS_TFT_SWRESET          0x01
#define ANIMUS_TFT_RDDID            0x04
#define ANIMUS_TFT_RDDST            0x09

#define ANIMUS_TFT_SLPIN            0x10
#define ANIMUS_TFT_SLPOUT           0x11
#define ANIMUS_TFT_PTLON            0x12
#define ANIMUS_TFT_NORON            0x13

#define ANIMUS_TFT_INVOFF           0x20
#define ANIMUS_TFT_INVON            0x21
#define ANIMUS_TFT_DISPOFF          0x28
#define ANIMUS_TFT_DISPON           0x29
#define ANIMUS_TFT_CASET            0x2A
#define ANIMUS_TFT_RASET            0x2B
#define ANIMUS_TFT_RAMWR            0x2C
#define ANIMUS_TFT_RAMRD            0x2E

#define ANIMUS_TFT_PTLAR            0x30
#define ANIMUS_TFT_TEOFF            0x34
#define ANIMUS_TFT_TEON             0x35
#define ANIMUS_TFT_MADCTL           0x36
#define ANIMUS_TFT_COLMOD           0x3A

#define ANIMUS_TFT_MADCTL_MY        0x80
#define ANIMUS_TFT_MADCTL_MX        0x40
#define ANIMUS_TFT_MADCTL_MV        0x20
#define ANIMUS_TFT_MADCTL_ML        0x10
#define ANIMUS_TFT_MADCTL_MH        0x04
#define ANIMUS_TFT_MADCTL_RGB       0x00
#define ANIMUS_TFT_MADCTL_BGR       0x08

#define ANIMUS_TFT_RDID1            0xDA
#define ANIMUS_TFT_RDID2            0xDB
#define ANIMUS_TFT_RDID3            0xDC
#define ANIMUS_TFT_RDID4            0xDD

#define ANIMUS_TFT_FRMCTR1          0xB1
#define ANIMUS_TFT_FRMCTR2          0xB2
#define ANIMUS_TFT_FRMCTR3          0xB3
#define ANIMUS_TFT_INVCTR           0xB4
#define ANIMUS_TFT_DISSET5          0xB6

#define ANIMUS_TFT_PWCTR1           0xC0
#define ANIMUS_TFT_PWCTR2           0xC1
#define ANIMUS_TFT_PWCTR3           0xC2
#define ANIMUS_TFT_PWCTR4           0xC3
#define ANIMUS_TFT_PWCTR5           0xC4
#define ANIMUS_TFT_PWCTR6           0xFC
#define ANIMUS_TFT_VMCTR1           0xC5

#define ANIMUS_TFT_GMCTRP1          0xE0
#define ANIMUS_TFT_GMCTRN1          0xE1

#define ANIMUS_TFT_SPISETTINGS      SPISettings(15000000, MSBFIRST, SPI_MODE0)

uint16_t animus_tft_current_color;
uint16_t animus_tft_rowstart;
uint16_t animus_tft_colstart;

/*
 * The following command list is from the Adafruit ST7735 library.
 * 
 * This is a library for several Adafruit displays based on ST77* drivers.
 * 
 *   Works with the Adafruit 1.8" TFT Breakout w/SD card
 *     ----> http://www.adafruit.com/products/358
 *   The 1.8" TFT shield
 *     ----> https://www.adafruit.com/product/802
 *   The 1.44" TFT breakout
 *     ----> https://www.adafruit.com/product/2088
 *   as well as Adafruit raw 1.8" TFT display
 *     ----> http://www.adafruit.com/products/618
 *  
 * Check out the links above for our tutorials and wiring diagrams.
 * These displays use SPI to communicate, 4 or 5 pins are required to
 * interface (RST is optional).
 * 
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 * 
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 * MIT license, all text above must be included in any redistribution.
 */
static uint8_t Bcmd[] = {                        // Init commands for 7735B screens
    18,                             // 18 commands in list:
    ANIMUS_TFT_SWRESET,   ANIMUS_TFT_DELAY, //  1: Software reset, no args, w/delay
      50,                           //     50 ms delay
    ANIMUS_TFT_SLPOUT,    ANIMUS_TFT_DELAY, //  2: Out of sleep mode, no args, w/delay
      255,                          //     255 = max (500 ms) delay
    ANIMUS_TFT_COLMOD,  1+ANIMUS_TFT_DELAY, //  3: Set color mode, 1 arg + delay:
      0x05,                         //     16-bit color
      10,                           //     10 ms delay
    ANIMUS_TFT_FRMCTR1, 3+ANIMUS_TFT_DELAY, //  4: Frame rate control, 3 args + delay:
      0x00,                         //     fastest refresh
      0x06,                         //     6 lines front porch
      0x03,                         //     3 lines back porch
      10,                           //     10 ms delay
    ANIMUS_TFT_MADCTL,  1,              //  5: Mem access ctl (directions), 1 arg:
      0x08,                         //     Row/col addr, bottom-top refresh
    ANIMUS_TFT_DISSET5, 2,              //  6: Display settings #5, 2 args:
      0x15,                         //     1 clk cycle nonoverlap, 2 cycle gate
                                    //     rise, 3 cycle osc equalize
      0x02,                         //     Fix on VTL
    ANIMUS_TFT_INVCTR,  1,              //  7: Display inversion control, 1 arg:
      0x0,                          //     Line inversion
    ANIMUS_TFT_PWCTR1,  2+ANIMUS_TFT_DELAY, //  8: Power control, 2 args + delay:
      0x02,                         //     GVDD = 4.7V
      0x70,                         //     1.0uA
      10,                           //     10 ms delay
    ANIMUS_TFT_PWCTR2,  1,              //  9: Power control, 1 arg, no delay:
      0x05,                         //     VGH = 14.7V, VGL = -7.35V
    ANIMUS_TFT_PWCTR3,  2,              // 10: Power control, 2 args, no delay:
      0x01,                         //     Opamp current small
      0x02,                         //     Boost frequency
    ANIMUS_TFT_VMCTR1,  2+ANIMUS_TFT_DELAY, // 11: Power control, 2 args + delay:
      0x3C,                         //     VCOMH = 4V
      0x38,                         //     VCOML = -1.1V
      10,                           //     10 ms delay
    ANIMUS_TFT_PWCTR6,  2,              // 12: Power control, 2 args, no delay:
      0x11, 0x15,
    ANIMUS_TFT_GMCTRP1,16,              // 13: Gamma Adjustments (pos. polarity), 16 args + delay:
      0x09, 0x16, 0x09, 0x20,       //     (Not entirely necessary, but provides
      0x21, 0x1B, 0x13, 0x19,       //      accurate colors)
      0x17, 0x15, 0x1E, 0x2B,
      0x04, 0x05, 0x02, 0x0E,
    ANIMUS_TFT_GMCTRN1,16+ANIMUS_TFT_DELAY, // 14: Gamma Adjustments (neg. polarity), 16 args + delay:
      0x0B, 0x14, 0x08, 0x1E,       //     (Not entirely necessary, but provides
      0x22, 0x1D, 0x18, 0x1E,       //      accurate colors)
      0x1B, 0x1A, 0x24, 0x2B,
      0x06, 0x06, 0x02, 0x0F,
      10,                           //     10 ms delay
    ANIMUS_TFT_CASET,   4,              // 15: Column addr set, 4 args, no delay:
      0x00, 0x02,                   //     XSTART = 2
      0x00, 0x81,                   //     XEND = 129
    ANIMUS_TFT_RASET,   4,              // 16: Row addr set, 4 args, no delay:
      0x00, 0x02,                   //     XSTART = 1
      0x00, 0x81,                   //     XEND = 160
    ANIMUS_TFT_NORON,     ANIMUS_TFT_DELAY, // 17: Normal display on, no args, w/delay
      10,                           //     10 ms delay
    ANIMUS_TFT_DISPON,    ANIMUS_TFT_DELAY, // 18: Main screen turn on, no args, delay
      255 },                        //     255 = max (500 ms) delay

  Rcmd1[] = {                       // 7735R init, part 1 (red or green tab)
    15,                             // 15 commands in list:
    ANIMUS_TFT_SWRESET,   ANIMUS_TFT_DELAY, //  1: Software reset, 0 args, w/delay
      150,                          //     150 ms delay
    ANIMUS_TFT_SLPOUT,    ANIMUS_TFT_DELAY, //  2: Out of sleep mode, 0 args, w/delay
      255,                          //     500 ms delay
    ANIMUS_TFT_FRMCTR1, 3,              //  3: Framerate ctrl - normal mode, 3 arg:
      0x01, 0x2C, 0x2D,             //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ANIMUS_TFT_FRMCTR2, 3,              //  4: Framerate ctrl - idle mode, 3 args:
      0x01, 0x2C, 0x2D,             //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ANIMUS_TFT_FRMCTR3, 6,              //  5: Framerate - partial mode, 6 args:
      0x01, 0x2C, 0x2D,             //     Dot inversion mode
      0x01, 0x2C, 0x2D,             //     Line inversion mode
    ANIMUS_TFT_INVCTR,  1,              //  6: Display inversion ctrl, 1 arg:
      0x07,                         //     No inversion
    ANIMUS_TFT_PWCTR1,  3,              //  7: Power control, 3 args, no delay:
      0xA2,
      0x02,                         //     -4.6V
      0x84,                         //     AUTO mode
    ANIMUS_TFT_PWCTR2,  1,              //  8: Power control, 1 arg, no delay:
      0xC5,                         //     VGH25=2.4C VGSEL=-10 VGH=3 * AVDD
    ANIMUS_TFT_PWCTR3,  2,              //  9: Power control, 2 args, no delay:
      0x0A,                         //     Opamp current small
      0x00,                         //     Boost frequency
    ANIMUS_TFT_PWCTR4,  2,              // 10: Power control, 2 args, no delay:
      0x8A,                         //     BCLK/2,
      0x2A,                         //     opamp current small & medium low
    ANIMUS_TFT_PWCTR5,  2,              // 11: Power control, 2 args, no delay:
      0x8A, 0xEE,
    ANIMUS_TFT_VMCTR1,  1,              // 12: Power control, 1 arg, no delay:
      0x0E,
    ANIMUS_TFT_INVOFF,  0,              // 13: Don't invert display, no args
    ANIMUS_TFT_MADCTL,  1,              // 14: Mem access ctl (directions), 1 arg:
      0xC8,                         //     row/col addr, bottom-top refresh
    ANIMUS_TFT_COLMOD,  1,              // 15: set color mode, 1 arg, no delay:
      0x05 },                       //     16-bit color

  Rcmd2green[] = {                  // 7735R init, part 2 (green tab only)
    2,                              //  2 commands in list:
    ANIMUS_TFT_CASET,   4,              //  1: Column addr set, 4 args, no delay:
      0x00, 0x02,                   //     XSTART = 0
      0x00, 0x7F+0x02,              //     XEND = 127
    ANIMUS_TFT_RASET,   4,              //  2: Row addr set, 4 args, no delay:
      0x00, 0x01,                   //     XSTART = 0
      0x00, 0x9F+0x01 },            //     XEND = 159

  Rcmd2red[] = {                    // 7735R init, part 2 (red tab only)
    2,                              //  2 commands in list:
    ANIMUS_TFT_CASET,   4,              //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,                   //     XSTART = 0
      0x00, 0x7F,                   //     XEND = 127
    ANIMUS_TFT_RASET,   4,              //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,                   //     XSTART = 0
      0x00, 0x9F },                 //     XEND = 159

  Rcmd2green144[] = {               // 7735R init, part 2 (green 1.44 tab)
    2,                              //  2 commands in list:
    ANIMUS_TFT_CASET,   4,              //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,                   //     XSTART = 0
      0x00, 0x7F,                   //     XEND = 127
    ANIMUS_TFT_RASET,   4,              //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,                   //     XSTART = 0
      0x00, 0x7F },                 //     XEND = 127

  Rcmd2green160x80[] = {            // 7735R init, part 2 (mini 160x80)
    2,                              //  2 commands in list:
    ANIMUS_TFT_CASET,   4,              //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,                   //     XSTART = 0
      0x00, 0x4F,                   //     XEND = 79
    ANIMUS_TFT_RASET,   4,              //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,                   //     XSTART = 0
      0x00, 0x9F },                 //     XEND = 159

  Rcmd2green160x80plugin[] = {      // 7735R init, part 2 (mini 160x80 with plugin FPC)
    3,                              //  3 commands in list:
    ANIMUS_TFT_INVON,  0,              //   1: Display is inverted
    ANIMUS_TFT_CASET,   4,              //  2: Column addr set, 4 args, no delay:
      0x00, 0x00,                   //     XSTART = 0
      0x00, 0x4F,                   //     XEND = 79
    ANIMUS_TFT_RASET,   4,              //  3: Row addr set, 4 args, no delay:
      0x00, 0x00,                   //     XSTART = 0
      0x00, 0x9F },                 //     XEND = 159

  Rcmd3[] = {                       // 7735R init, part 3 (red or green tab)
    4,                              //  4 commands in list:
    ANIMUS_TFT_GMCTRP1, 16      ,       //  1: Gamma Adjustments (pos. polarity), 16 args + delay:
      0x02, 0x1c, 0x07, 0x12,       //     (Not entirely necessary, but provides
      0x37, 0x32, 0x29, 0x2d,       //      accurate colors)
      0x29, 0x25, 0x2B, 0x39,
      0x00, 0x01, 0x03, 0x10,
    ANIMUS_TFT_GMCTRN1, 16      ,       //  2: Gamma Adjustments (neg. polarity), 16 args + delay:
      0x03, 0x1d, 0x07, 0x06,       //     (Not entirely necessary, but provides
      0x2E, 0x2C, 0x29, 0x2D,       //      accurate colors)
      0x2E, 0x2E, 0x37, 0x3F,
      0x00, 0x00, 0x02, 0x10,
    ANIMUS_TFT_NORON,     ANIMUS_TFT_DELAY, //  3: Normal display on, no args, w/delay
      10,                           //     10 ms delay
    ANIMUS_TFT_DISPON,    ANIMUS_TFT_DELAY, //  4: Main screen turn on, no args w/delay
      100 };                        //     100 ms delay

void animus_tft_cs_low() { gpio_put(1, 0); }
void animus_tft_cs_high() { gpio_put(1, 1); }
void animus_tft_command_mode() { gpio_put(10, 0); }
void animus_tft_data_mode() { gpio_put(10, 1); }

void animus_tft_send_command(uint8_t command, uint8_t *data, uint8_t length) {
    SPI.beginTransaction(ANIMUS_TFT_SPISETTINGS);

    animus_tft_cs_low();
    animus_tft_command_mode();
    SPI.transfer(command);
    animus_tft_data_mode();

    for(int i = 0; i < length; i++) {
        SPI.transfer(data[i]);
    }

    animus_tft_cs_high();
    SPI.endTransaction();
}

#define ANIMUS_TFT_ADDR addr++[0]
void animus_tft_display_init(uint8_t *addr) {
    uint8_t numCommands, cmd, numArgs;
    uint16_t ms;

    numCommands = ANIMUS_TFT_ADDR;
    while(numCommands --) {
        cmd = ANIMUS_TFT_ADDR;
        numArgs = ANIMUS_TFT_ADDR;
        ms = numArgs & ANIMUS_TFT_DELAY;
        numArgs &= ~ANIMUS_TFT_DELAY;
        animus_tft_send_command(cmd, addr, numArgs);
        addr += numArgs;

        if(ms) {
            ms = ANIMUS_TFT_ADDR;
            if(ms == 255) ms = 500;
            delay(ms);
        }
    }
}

void animus_tft_set_rotation(uint8_t m) {
    // TODO: this
}

void display_init() {
    // This init function is for green-tab displays.
    // For others, see https://github.com/adafruit/Adafruit-ST7735-Library/blob/master/Adafruit_ST7735.cpp

    // Init CS, RST, and DC pins
    gpio_init(1); // CS
    gpio_set_dir(1, GPIO_OUT);
    gpio_put(1, 0);

    gpio_init(5); // RST
    gpio_set_dir(5, GPIO_OUT);
    gpio_put(5, 1);

    gpio_init(10); // DC
    gpio_set_dir(10, GPIO_OUT);
    gpio_put(10, 0);

    // Send the commands to init the display
    animus_tft_display_init(Rcmd1);
    animus_tft_display_init(Rcmd2green);
    //animus_tft_colstart = 2;
    //animus_tft_rowstart = 3;
    animus_tft_display_init(Rcmd3);
    animus_tft_set_rotation(0);
}

void display_shutdown() {}
uint16_t display_width() { return ANIMUS_TFT_WIDTH; }
uint16_t display_height() { return ANIMUS_TFT_HEIGHT; }
void display_set_color(uint16_t color) {
    animus_tft_current_color = color;
}

void animus_tft_set_address(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2) {
    if(x >= ANIMUS_TFT_WIDTH || y >= ANIMUS_TFT_HEIGHT) return;
    animus_tft_cs_low();

    // Convert x and y coords to 8-bit since SPI.transfer sends 16-bit values wrong
    uint8_t x_hi = (x + animus_tft_colstart) >> 8;
    uint8_t x_lo = x + animus_tft_colstart;
    uint8_t y_hi = (y + animus_tft_rowstart) >> 8;
    uint8_t y_lo = y + animus_tft_rowstart;

    uint8_t x2_hi = (x2 + animus_tft_colstart) >> 8;
    uint8_t x2_lo = x2 + animus_tft_colstart;
    uint8_t y2_hi = (y2 + animus_tft_rowstart) >> 8;
    uint8_t y2_lo = y2 + animus_tft_rowstart;

    // Send X address space
    animus_tft_command_mode();
    SPI.transfer(ANIMUS_TFT_CASET);
    animus_tft_data_mode();
    SPI.transfer(x_hi);
    SPI.transfer(x_lo);
    SPI.transfer(x2_hi);
    SPI.transfer(x2_lo);
    
    // Send Y address space
    animus_tft_command_mode();
    SPI.transfer(ANIMUS_TFT_RASET);
    animus_tft_data_mode();
    SPI.transfer(y_hi);
    SPI.transfer(y_lo);
    SPI.transfer(y2_hi);
    SPI.transfer(y2_lo);

    // Tell it we're writing to RAM
    animus_tft_command_mode();
    SPI.transfer(ANIMUS_TFT_RAMWR);

    animus_tft_cs_high();
}

void display_draw_pixel(uint16_t x, uint16_t y) {
    // Push a single pixel
    if(x >= ANIMUS_TFT_WIDTH || y >= ANIMUS_TFT_HEIGHT) return;

    animus_tft_set_address(x, y, x + 1, y + 1);

    animus_tft_cs_low();
    animus_tft_data_mode();

    SPI.transfer((uint8_t) (animus_tft_current_color >> 8));
    SPI.transfer((uint8_t) animus_tft_current_color);

    animus_tft_cs_high();
}

void display_fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    // Push a ton of pixels
    if(x >= ANIMUS_TFT_WIDTH || y >= ANIMUS_TFT_HEIGHT) return;
    if(x + width >= ANIMUS_TFT_WIDTH) width = ANIMUS_TFT_WIDTH - x;
    if(y + height >= ANIMUS_TFT_HEIGHT) height = ANIMUS_TFT_HEIGHT - y;

    animus_tft_set_address(x, y, x + width, y + height);

    animus_tft_cs_low();
    animus_tft_data_mode();

    uint8_t hi = animus_tft_current_color >> 8;
    uint8_t lo = animus_tft_current_color;

    for(int i = 0; i < (width * height) - 1; i++) {
        SPI.transfer(hi);
        SPI.transfer(lo);
    }

    animus_tft_cs_high();
}

void display_draw_bitmap(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t* data) {
    // Push a ton of pixels
    if(x >= ANIMUS_TFT_WIDTH || y >= ANIMUS_TFT_HEIGHT) return;
    if(x + width >= ANIMUS_TFT_WIDTH) width = ANIMUS_TFT_WIDTH - x;
    if(y + height >= ANIMUS_TFT_HEIGHT) height = ANIMUS_TFT_HEIGHT - y;

    animus_tft_set_address(x, y, x + width, y + height);

    animus_tft_cs_low();
    animus_tft_data_mode();

    for(int i = 0; i < (width * height); i++) {
        SPI.transfer((uint8_t) (data[i] >> 8));
        SPI.transfer((uint8_t) data[i]);
    }

    animus_tft_cs_high();
}
#endif
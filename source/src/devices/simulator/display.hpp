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

#include <SDL.h>

#define DISPLAY_WIDTH 84
#define DISPLAY_HEIGHT 48

SDL_Event event;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;

uint32_t* pixels;

void display_init() {
    if(SDL_Init(SDL_INIT_VIDEO) == -1) {
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(-1);
    }
    window = SDL_CreateWindow("Glacier OS Siulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    pixels = (uint32_t*) malloc(DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(uint32_t));
}

void window_update() {
    if(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                SDL_DestroyTexture(texture);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                exit(0);
        }
    }

    SDL_UpdateTexture(texture, NULL, pixels, DISPLAY_WIDTH * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void window_set_pixel(int x, int y, int value) {
    if(value) {
        pixels[((y * DISPLAY_WIDTH) + x)] = 255;
    } else pixels[((y * DISPLAY_WIDTH) + x)] = 0;
}

void display_draw_pixel(int x, int y, int value) {
    window_set_pixel(x, y, value);
    window_update();
}

void display_shutdown();
int display_width() { return DISPLAY_WIDTH; }
int display_height() { return DISPLAY_HEIGHT; }

void display_clear() {
    memset(pixels, 255, DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(uint32_t));
    window_update();
}

void display_fill_rect(int x, int y, int width, int height, int value) {
    for(int dx = 0; dx < width; dx++) {
        for(int dy = 0; dy < height; dy++) {
            window_set_pixel(x + dx, y + dy, value);
        }
    }
    window_update();
}

void display_draw_bitmap(int x, int y, int width, int height, uint8_t* data) {
    for(int dx = 0; dx < width; dx++) {
        for(int dy = 0; dy < height; dy++) {
            if(data[(dy * width) + dx]) window_set_pixel(x + dx, y + dy, 1);
        }
    }
    window_update();
}

void display_draw_character(int x, int y, char character, int value) {
    uint8_t* chardata = &font8x8_basic[character][0];
    for(int dy = 0; dy < 8; dy++) {
        for(int dx = 0; dx < 8; dx++) {
            if((chardata[dy] >> dx) & 0x01) window_set_pixel(x + dx, y + dy, value);
        }
    }
    window_update();
}

#endif
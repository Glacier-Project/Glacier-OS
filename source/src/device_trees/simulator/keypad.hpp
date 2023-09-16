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

char keypad_wait_key() {
    debug("Waiting for keypress\n");
    for(;;) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                SDL_DestroyTexture(texture);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                exit(0);
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_UP: return KEY_UP;
                    case SDLK_DOWN: return KEY_DOWN;
                    case SDLK_c: return KEY_CANCEL;
                    case SDLK_o: return KEY_OK;
                    case SDLK_1: return '1';
                    case SDLK_2: return '2';
                    case SDLK_3: return '3';
                    case SDLK_4: return '4';
                    case SDLK_5: return '5';
                    case SDLK_6: return '6';
                    case SDLK_7: return '7';
                    case SDLK_8: return '8';
                    case SDLK_9: return '9';
                    case SDLK_ASTERISK: return '*';
                    case SDLK_0: return '0';
                    case SDLK_HASH: return '#';
                }
        }
    }
}

char keypad_get_key() {
    if(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                SDL_DestroyTexture(texture);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                exit(0);
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_UP: return KEY_UP;
                    case SDLK_DOWN: return KEY_DOWN;
                    case SDLK_c: return KEY_CANCEL;
                    case SDLK_o: return KEY_OK;
                    case SDLK_1: return '1';
                    case SDLK_2: return '2';
                    case SDLK_3: return '3';
                    case SDLK_4: return '4';
                    case SDLK_5: return '5';
                    case SDLK_6: return '6';
                    case SDLK_7: return '7';
                    case SDLK_8: return '8';
                    case SDLK_9: return '9';
                    case SDLK_ASTERISK: return '*';
                    case SDLK_0: return '0';
                    case SDLK_HASH: return '#';
                }
        }
    } 
    return '\0';
}
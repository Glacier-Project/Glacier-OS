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

class GUILabel : GraphicsObject {
public:
    String label;

    void update() {
        fill(0);
        draw_text(0, 0, display_width(), label.c_str(), 1, GRAPHICS_TEXT_BEHAVIOUR_SCROLL);
    }
};

class GUITextInput : GraphicsObject {
public:
    String text;

    bool isSelectable() {
        return true;
    }

    void input(char key) {
        if(key == KEY_OK) {

        } else {
            text = text + key;
        }
    }

    void update() {
        draw_hline(height - 1, 1);
        if(selected) {
            draw_hline(0, 1);
            draw_vline(0, 1);
            draw_vline(display_width() - 1, 1);
        }

        draw_text(0, 0, display_width(), text.c_str(), 1, GRAPHICS_TEXT_BEHAVIOUR_END);
    }
};

class GUISelector : GraphicsObject {
public:
    std::vector<String> items;
    int selected_item;

    bool isSelectable() {
        return true;
    }

    void input(char key) {
        if(key == KEY_OK) {
            selected_item = gui_list("Select", items);
        }
    }

    void update() {
        draw_text(0, 0, display_width() - 8, 1, GRAPHICS_TEXT_BEHAVIOUR_START);
        draw_pixel(display_width - 4, 4, 1);
        draw_pixel(display_width - 3, 4, 1);
        draw_pixel(display_width - 2, 4, 1);
        draw_pixel(display_width - 3, 5, 1);
    }

};

class GUIButton : GraphicsObject {
public:
    String text;
    void (*callback)();

    bool isSelectable() {
        return true;
    }

    void input(char key) {
        if(key == KEY_OK) {
            callback();
        }
    }

    void update() {
        draw_text(0, 0, display_width(), 1, GRAPHICS_TEXT_BEHAVIOUR_SCROLL);
        draw_vline(0, 1);
    }
};
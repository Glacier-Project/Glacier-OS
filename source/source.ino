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

#include "config.hpp"

#include "src/locales/locale.hpp"
#include "src/graphics/graphics.hpp"

#include "src/api.hpp"
#include "src/devices/drivers.hpp"

#include "LittleFS.h" // Part of arduino-pico

#include "src/apps/home_screen.hpp"
#include "src/apps/shell.hpp"

void setup() {
    bringup();

    // Init peripherals
    display_init();
    //cellular_init();

    // Init filesystem
    LittleFS.begin();
    // TODO: load settings

    // Populate application array
    add_application_entry(&icon_messages[0], STRING_MESSAGES, &start_home_menu);
    add_application_entry(&icon_contacts[0], STRING_CONTACTS, &start_home_menu);
    add_application_entry(&icon_calculator[0], STRING_CALC, &start_home_menu);
    add_application_entry(&icon_notepad[0], STRING_NOTEPAD, &start_home_menu);
    add_application_entry(&icon_settings[0], STRING_SETTINGS, &start_home_menu);

    // Start OS
    display_clear();
    start_home_menu();
    shutdown();
}

void loop() {
    
}

void shutdown() {
    LittleFS.end();
}

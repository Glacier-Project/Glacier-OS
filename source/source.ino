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

#include <vector>

#ifndef debug
#define debug Serial.printf
#endif

void panic(String message) {
    debug("PANIC: ");
    debug(message.c_str());
    for(;;) {}
}

#include "src/locales/locale.hpp"
#include "src/graphics/graphics.hpp"

#include "src/api.hpp"
#include "src/devices/drivers.hpp"

//#include "LittleFS.h" // Part of arduino-pico

#include "src/apps/dialer.hpp"
#include "src/apps/messages.hpp"
#include "src/apps/contacts.hpp"
#include "src/apps/home_screen.hpp"

void setup() {
    bringup();
    debug("Initial bringup complete.\n");

    // Init peripherals
    debug("Initialising display...\n");
    display_init();
    
    debug("Initialising cellular...\n");
    cellular_init();

    // Init filesystem
    //LittleFS.begin();

    // Load user data
    // TODO: load settings
    load_contacts();

    // Populate application array
    debug("Populating app entries...\n");
    add_application_entry(&icon_messages[0], STRING_MESSAGES, &start_messages);
    add_application_entry(&icon_contacts[0], STRING_CONTACTS, &start_contacts);
    add_application_entry(&icon_calculator[0], STRING_CALC, &start_home_menu);
    add_application_entry(&icon_notepad[0], STRING_NOTEPAD, &start_home_menu);
    add_application_entry(&icon_settings[0], STRING_SETTINGS, &start_home_menu);

    // Start IME
    debug("Creating Input Method Editor...\n");
    ime_init();

    // Start OS
    debug("Welcome to Glacier OS!\n");
    display_clear();
    start_home_menu();
    shutdown();
}

void loop() {
    
}

void shutdown() {
    //LittleFS.end();
}

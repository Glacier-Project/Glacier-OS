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

#include "src/api.hpp"
#include "src/devices/drivers.hpp"

#include "src/extensions/apps.hpp"
#include "src/extensions/kexts.hpp"

void setup() {
    bringup();
    Serial.begin();
    Serial.setTimeout(0xFFFF);
    Serial.println("Initial hardware bringup OK");
    Serial.println("Starting peripheral bringup...");

    display_init();
    Serial.println("Display bringup OK");

    cellular_init();
    Serial.println("Cellular bringup OK");

    Serial.println("Running kernel extensions...");
    kexts_init();
    Serial.println("Completed.");

    Serial.println("Welcome to Glacier OS!");
    kext_shell_run();
}

void loop() {
    
}
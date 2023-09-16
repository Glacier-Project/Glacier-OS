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
#include "src/device_trees/drivers.hpp"

// Kernel code
#include "src/kernel/display.hpp"
#include "src/kernel/keypad.hpp"
#include "src/kernel/debug.hpp"

void setup() {
    Serial.init(9600);
    dprintf("Glacier OS!\n");

    // Do hardware init
    dprintf("Display init START");
    display_init();

    // Enter userspace
    kpanic("Userspace not implemented")
}

void loop() {

}
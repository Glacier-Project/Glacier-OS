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

#include "src/hypervisor/app_loader.hpp"

void setup() {
    bringup();

    Serial.begin();
    Serial.setTimeout(0xFFFF);
    Serial.println("HW init done!");

    Serial.print("Init modules: ");
    display_init();
    Serial.print("display ");
    cellular_init();
    Serial.print("cellular ");
    Serial.println();

    display_set_color(0xFFFF);
    display_fill_rect(0, 0, 128, 160);
    display_set_color(0x0000);
    display_fill_rect(10, 10, 20, 20);
}

void loop() {
    #ifdef UI_SERIAL_SHELL
    Serial.print(">");
    while(Serial.available() == 0) {}
    String instring = Serial.readStringUntil('\n');
    Serial.println(instring);
    if(!instring.compareTo("cell_model")) Serial.println(cellular_get_modem_model());
    else if(!instring.compareTo("cell_manufacturer")) Serial.println(cellular_get_modem_manufacturer());
    

    #endif
}

void setup1() {

}

void loop1() {

}
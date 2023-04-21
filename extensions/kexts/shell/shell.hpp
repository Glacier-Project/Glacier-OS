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

// TODO: Add method to allow apps + kexts to register more commands
void kext_shell_run() {
    Serial.print("\n>");
    while(Serial.available() == 0) {}
    String instring = Serial.readStringUntil('\n');
    Serial.println(instring);
    
    // Built-in kexts
    if(!instring.compareTo("self_test")) kext_textmode_run();

    // Cellular Commands
    else if(!instring.compareTo("cell_model")) Serial.println(cellular_get_modem_model());
    else if(!instring.compareTo("cell_manufacturer")) Serial.println(cellular_get_modem_manufacturer());
    
    // Illegal command message
    else Serial.println("Illegal command");
}

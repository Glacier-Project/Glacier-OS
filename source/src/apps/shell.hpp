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

/*
void self_test() {
    Serial.println("Self-test starting...");
    int pass = 1;

    // Display self-test
    Serial.print("Starting display test... ");
    if(display_width() < 1) {
        Serial.println("FAIL! Display drivers reporting 0 pixel width");
        pass = 0;
    } else if(display_height() < 1) {
        Serial.println("FAIL! Display drivers reporting 0 pixel height");
        pass = 0;
    } else Serial.println("PASS!");

    // Cellular self-test
    Serial.println("Starting cellular test...");
    Serial.print("Cellular modem is a ");
    String response = cellular_get_modem_manufacturer();
    Serial.print(response);
    Serial.print(" ");
    response = cellular_get_modem_model();
    Serial.println(response);

    /*Serial.print("Checking IMEI... ");
    char imei_buffer[16];
    cellular_get_imei(&imei_buffer[0], 16);
    if(imei_buffer[0] == '\0') {
        Serial.println("FAIL! IMEI is null!");
        pass = 0;
    } else Serial.println("PASS!");*/

    Serial.print("Checking availability...");
    if(!cellular_available()) {
        Serial.println("FAIL! Is network connected?");
        pass = 0;
    } else Serial.println("PASS!");

    // Check if we passed
    if(pass) Serial.println("Self-test passed!");
    else Serial.println("Self-test failed!");
}

void start_shell() {
    Serial.print("\n>");
    while(Serial.available() == 0) {}
    String instring = Serial.readStringUntil('\n');
    Serial.println(instring);
    
    // Built-in kexts
    if(!instring.compareTo("self_test")) self_test();

    // Cellular Commands
    else if(!instring.compareTo("cell_model")) Serial.println(cellular_get_modem_model());
    else if(!instring.compareTo("cell_manufacturer")) Serial.println(cellular_get_modem_manufacturer());
    
    // Illegal command message
    else Serial.println("Illegal command");
}*/
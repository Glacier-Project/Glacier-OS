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

//https://www.waveshare.com/w/upload/5/54/SIM7500_SIM7600_Series_AT_Command_Manual_V1.08.pdf

#ifndef CELLULAR_HPP
#define CELLULAR_HPP
int animus_cellular_send_command(const char* command) {
    Serial1.println(command);
    String response = Serial1.readString();
    if(!response.compareTo("OK")) return 0;
    return 1;
}

int animus_cellular_send_command_with_argument(const char* command, const char* argument) {
    Serial1.print(command);
    Serial1.println(argument);
    String response = Serial1.readStringUntil('\n');
    if(!response.compareTo("OK")) return 0;
    return 1;
}

String animus_cellular_send_command_with_response(const char* command) {
    Serial1.println(command);
    Serial1.readStringUntil('\n');
    String response = Serial1.readStringUntil('\n');
    Serial1.readStringUntil('\n');
    Serial1.readStringUntil('\n');
    return response;
}

String cellular_get_modem_manufacturer() {
    return animus_cellular_send_command_with_response("AT+CGMI");
}

String cellular_get_modem_model() {
    return animus_cellular_send_command_with_response("AT+CGMM");
}

int cellular_available() {
    if(animus_cellular_send_command_with_response("AT+CPIN?").indexOf("READY") != -1) return 1;
    return 0;
}

void cellular_init() {
    Serial1.begin(115200);
    Serial1.setTimeout(0xFFFF);
    Serial1.println("ATE0");
    for(int i = 0; i < 5; i++) {
        String returnString = Serial1.readStringUntil('\n');
        if(returnString.indexOf("OK") != -1) {
            Serial1.readStringUntil('\n');
            break;
        }
    }
}

void cellular_shutdown();
void cellular_get_imei(char* buffer, int len);

void cellular_answer() {
    animus_cellular_send_command("ATA");
}

void cellular_dial(const char* number) {
    animus_cellular_send_command("AT+CSDVC=1");
    animus_cellular_send_command_with_argument("ATD", number);
}

void cellular_hang_up() {
    animus_cellular_send_command("AT+CHUP");
}

int cellular_enter_pin(const char* pin) {
    return animus_cellular_send_command_with_argument("AT+CPIN=", pin);
}

void cellular_send_dtmf(char tone) {
    char command[2] = {0, 0};
    command[0] = tone;
    animus_cellular_send_command_with_argument("AT+VTS=", (const char*) &command[0]);
}

void cellular_get_caller(char* buffer, int len);
void cellular_get_text(char* sender_buffer, int sender_len, char* message_buffer, int message_len);
int cellular_strength() { return 0; }
#endif
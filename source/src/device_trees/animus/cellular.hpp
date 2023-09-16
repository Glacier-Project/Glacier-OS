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

int cellular_previous_sms_count = 0;

String cellular_transmit(String command);
void cellular_init();
String cellular_get_manufacturer();
String cellular_get_model();
int cellular_available();
int cellular_sms_get_unreceived_count();
void cellular_sms_get();
void cellular_sms_send(String recipient, String contents);
void cellular_sms_delete_all();
void cellular_call_dial(String number);
void cellular_call_answer();
void cellular_call_end();
void cellular_refresh();

String cellular_transmit(String command) {
    Serial1.println(command);
    Serial1.readStringUntil('\n');
    String response = Serial1.readStringUntil('\n');
    Serial1.readStringUntil('\n');
    Serial1.readStringUntil('\n');
    return response;
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

    cellular_previous_sms_count = cellular_sms_get_unreceived_count();
}

String cellular_get_manufacturer() {
    return cellular_transmit("AT+CGMI");
}

String cellular_get_model() {
    return cellular_transmit("AT+CGMM");
}

int cellular_available() {
    if(cellular_transmit("AT+CPIN?").indexOf("READY") != -1) return 1;
    return 0;
}

int cellular_sms_get_unreceived_count() {
    String count = cellular_transmit("AT+CPMS?");
    // todo: parse, should get count back
} // Get the amount of SMS messages we've received

void cellular_sms_get() {
    // set to text mode
    cellular_transmit("AT+CMGF=1");
    cellular_transmit("AT+CSDH=1");

    int count = cellular_sms_get_unreceived_count();
    while(count > cellular_previous_sms_count) {
        cellular_transmit("AT+CMGR=" + String(cellular_previous_sms_count + 1));
        // todo: parse
        //messages_show_sms(sender, contents);
        cellular_previous_sms_count ++;
    }
}

void cellular_sms_send(String recipient, String contents) {
    cellular_transmit("AT+CMGF=1");
    delay(50);
    cellular_transmit("AT+CMGS=\"" + recipient + "\"");
    delay(50);
    cellular_transmit(contents);
    delay(50);
    Serial1.println(0x26) // TODO: maybe not println? maybe need to send this byte with above contents?
}

void cellular_sms_delete_all() {
    cellular_transmit("AT+CMGD1,4");
}

void cellular_call_dial(String number) {
    cellular_send_command("AT+CSDVC=1");
    cellular_transmit("ATD" + number);
    cellular_state = CELLULAR_STATE_IN_CALL;
}

void cellular_call_answer() {
    cellular_transmit("ATA");
    cellular_state = CELLULAR_STATE_IN_CALL;
}

void cellular_call_end() {
    cellular_transmit("ATH")
    cellular_state = CELLULAR_STATE_NORMAL;
}

void cellular_refresh() {
    cellular_sms_get();
    // TODO: check for incoming call
}

#endif
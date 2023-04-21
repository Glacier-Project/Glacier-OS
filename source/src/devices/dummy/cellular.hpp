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

#ifndef CELLULAR_HPP
#define CELLULAR_HPP
String cellular_get_modem_manufacturer() { return "Glacier"; }
String cellular_get_modem_model() { return "Fake Cellular Driver"; }
int cellular_available() { return 0; }
void cellular_init() { }
void cellular_shutdown() { }
void cellular_get_imei(char* buffer, int len) { }
void cellular_answer() { }
void cellular_dial(const char* number) { }
void cellular_hang_up() { }
int cellular_enter_pin(const char* pin) { return 1; }
void cellular_send_dtmf(char tone) {}
void cellular_get_caller(char* buffer, int len) { }
void cellular_get_text(char* sender_buffer, int sender_len, char* message_buffer, int message_len) { } 
int cellular_strength() { return 0; }
#endif
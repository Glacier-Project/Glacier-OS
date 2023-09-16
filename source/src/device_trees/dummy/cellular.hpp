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

void cellular_init() {}
String cellular_get_manufacturer() { return "Glacier"; }
String cellular_get_model() { return "Dummy"; }
int cellular_available() { return 0; }
void cellular_refresh() {}
void cellular_sms_send(String recipient, String contents) {}
void cellular_sms_delete_all() {}
void cellular_call_dial(String number) {}
void cellular_call_answer() {}
void cellular_call_end() {}

#endif
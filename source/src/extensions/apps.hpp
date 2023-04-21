/*
 * === This file should be populated by the generate.py script! ===
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

#ifndef APPS_HPP
#define APPS_HPP

// Structure for an app
typedef struct {
    char name[8];
    uint8_t bitmap[16][16];
    void (*main_function)(void);
} app_t;

app_t apps[64];

#define APPS_HPP_REPLACE_ME

#endif
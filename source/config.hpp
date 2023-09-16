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

// Device-specific information
#ifndef DEVICE_SIMULATOR // This is defined by the build script
#define DEVICE_ANIMUS // Specifies device to use for drivers
//#define DEVICE_CODEX // Specifies device to use for drivers
#define ENABLE_CELLULAR // Comment to turn off cellular functionality (req'd by included apps)
#endif

// Kernel settings
#define MAXIMUM_PROCESS_COUNT 64

// Basic OS settings
#define LOCALE_EN_US // Language file to use

// Home Screen settings
#define MAXIMUM_APP_COUNT 16 // Maximum apps that can be installed at any given time.

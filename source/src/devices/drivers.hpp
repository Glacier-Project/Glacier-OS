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

#ifndef DRIVERS_HPP
#define DRIVERS_HPP

#ifdef DEVICE_ANIMUS
#include "animus/bringup.hpp"
#include "animus/display.hpp"
#include "animus/cellular.hpp"
#include "animus/keypad.hpp"
#endif

#ifdef DEVICE_CODEX
#include "codex/bringup.hpp"
#include "codex/display.hpp"
#include "animus/cellular.hpp"
#include "animus/keypad.hpp"
#endif

#endif
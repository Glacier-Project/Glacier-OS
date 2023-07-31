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

// Features that can be disabled. Include guards will make sure dummy drivers are the only ones that load.
#ifndef ENABLE_CELLULAR
#include "dummy/cellular.hpp"
#endif

// Device trees:
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

#ifdef DEVICE_SIMULATOR
#include "simulator/bringup.hpp"
#include "simulator/display.hpp"
#include "simulator/keypad.hpp"
#endif

#endif
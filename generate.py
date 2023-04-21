# Glacier OS generator
# Copyright (C) 2023 Johnny Stene
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# Process:
#   Copy "source" folder to "dest" folder
#   Create buffer to store app data
#   Create buffer to store app code
#   Look through apps folder for valid apps
#       Copy all app code into buffer
#       Put contents of extensions/api.hpp in app code
#       Load app icon and convert into uint8_t array text
#       Copy app name, icon, and function pointer into buffer
#   Combine app data and code buffers 
#   Replace line "#define APPS_HPP_REPLACE_ME" with buffer
#   Create buffer to store kext function definitions
#   Create buffer to store kext init data
#   Create buffer to store kext code
#   Look through kexts folder for valid kexts
#       Copy all function defines into buffer
#       Copy all kext code into buffer
#       Put contents of extensions/api.hpp in kext code
#       Put kext init function into buffer
#   Replace line "#define KEXTS_HPP_INIT_REPLACE_ME" with init buffer
#   Replace line "#define KEXTS_HPP_REPLACE_ME" with code buffer

import os, sys, json
print("Glacier OS Generator v1.00")


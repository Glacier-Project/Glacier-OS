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

# Process TODO:
#   Look through apps folder for valid apps
#       Copy all app code into buffer
#       Put contents of extensions/api.hpp in app code
#       Load app icon and convert into uint8_t array text
#       Copy app name, icon, and function pointer into buffer
#   Combine app data and code buffers 
#   Replace line "#define APPS_HPP_REPLACE_ME" with buffer

import os, sys, json, shutil
print("Glacier OS Generator v1.00")

if(os.path.exists("dest")):
    print("Destination folder already exists. Attempting to remove...")
    try:
        shutil.rmtree("dest")
    except:
        print("Failed to remove.")
        sys.exit(-1)

try:
    print("Copying Glacier OS to the \"dest\" folder...")
    shutil.copytree("source", "dest")
except:
    print("Failed to copy.")
    sys.exit(-1)

app_data = ""
app_code = ""
# TODO: load apps

print("Processing kexts...")
kext_defines = ""
kext_init_code = ""
kext_code = ""

for kext_name in os.listdir("extensions/kexts"):
    if(os.path.isdir("extensions/kexts/" + kext_name)):
        print("Found kext " + kext_name)
        manifest_data = {}
        try:
            with open("extensions/kexts/" + kext_name + "/manifest.json") as manifest_file:
                manifest_data = json.load(manifest_file)
            print("Successfully loaded manifest data")
        except:
            print("Failed to load manifest data")
            sys.exit(-1)
        
        print("Including all declared functions...")
        for define in manifest_data["api_functions"]:
            kext_defines += define + "\n"
            print(define)
        
        print("Including kext code...")
        try:
            with open("extensions/kexts/" + kext_name + "/" + kext_name + ".hpp") as kextfile:
                kext_init_code += kextfile.read() + "\n"
            print("Done.")
        except:
            print("Failed to load " + kext_name + ".hpp from kext directory.")
            sys.exit(-1)
        
        if(manifest_data["init_function"] != ""):
            print("Including init function...")
            kext_init_code += manifest_data["init_function"] + "\n"

print("Adding kexts...")
try:
    with open("extensions/api.hpp") as apifile:
        kext_defines = apifile.read() + "\n" + kext_defines
except:
    print("Failed to read extensions/api.hpp.")
    sys.exit(-1)

try:
    with open("dest/src/extensions/kexts.hpp", "r+") as kextfile:
        contents = kextfile.read()
        contents = contents.replace("#define KEXTS_HPP_DEFINES_REPLACE_ME", kext_defines)
        contents = contents.replace("#define KEXTS_HPP_INIT_REPLACE_ME", kext_init_code)
        contents = contents.replace("#define KEXTS_HPP_REPLACE_ME", kext_code)
        kextfile.seek(0)
        kextfile.write(contents)
        kextfile.truncate()
    print("Success.")
except:
    print("Failed to output built hexts.hpp")
    sys.exit(-1)

print("Done.")
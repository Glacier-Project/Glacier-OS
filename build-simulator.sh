#!/bin/bash
clear
echo "=================================="
echo " Building Glacier OS Simulator..."
echo "=================================="
cd source
export DISPLAY=localhost:0.0
g++ -Wall -o ../simulator.exe simulator.c -DDEVICE_SIMULATOR `sdl2-config --cflags --libs`
cd ..
./simulator.exe
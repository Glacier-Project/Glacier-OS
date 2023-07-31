# Using the Glacier OS Simulator

## On Windows
1. Install Cygwin with the GNU Compiler Collection, SDL2 development packages, and dbus
2. Install XMing and run it
3. In Cygwin, run build-simulator.sh - this will build Glacier OS and run the simulator.

## On *NIX (untested)
1. Ensure you have dbus and an X server running.
2. Install the GNU compiler collection and SDL2 development libraries.
3. Run build-simulator.sh

## Known Issues
- If you have multiple monitors connected, the simulator will display in the middle of them. Hit Windows+Shift+Left Arrow to send it to the far left monitor, then maximise the screen to get something usable.
- Filesystem support is non-existant.

## Keybindings
`1, 2, 3, 4, 5, 6, 7, 8, 9, 0` - The usual keys on the keypad.  
`C` - The Cancel button  
`O` - The OK button  
`Down Arrow` - The Down key  
`Up Arrow` - The Up key  

## Debugging Information
Glacier OS will print any debug() calls to stdout.
# Kernel folder
This contains any core functionality not directly provided by the device drivers.

## Folder structure
- `display.hpp` - Display primitives API  
- `keypad.hpp` - Code for keypad matrices and for getting key presses.
- `debug.hpp` - Debug API: serial console, kpanics, etc...
- `tasks` - Folder for each system daemon
- `tasks/testd.hpp` - For testing FreeRTOS
# Kernel Extension Format
Kernel Extensions are stored as a C++ header file, and a JSON manifest.

## Header file
The header file should contain all of your extension's code in one file. It will be automatically included when building Glacier OS.

## Manifest
The manifest is a JSON file including some information about the functions your kext contains.  
`init_function`: A line of C++ (including a semicolon!) that runs at startup to initialise your kernel extension.
`api_functions`: An array of strings containing function definitions (also with semicolons!) that can be used by other kernel extensions.
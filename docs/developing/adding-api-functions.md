# Adding API functions
To add an API function, you must first decide whether the API function directly accesses the hardware (Direct Hardware Access) or only accesses other API functions (Common Wrapper).

## Direct Hardware Access
1. Determine if you are extending an existing API (cellular, display, etc...) or creating a new one. If extending, skip to step `5`.
2. Create a file in `source/src/devices/dummy` for the new API.
3. Add the dummy file to any unsupported devices in `source/src/devices/drivers.hpp`
4. Create a file in each supported device for the new API.
5. Populate the relevant files in all devices with driver content. Do not do this if the device uses dummy drivers.
6. Add definitions for the API functions in `source/src/api.hpp` and `extensions/api.hpp`.
7. Add documentation for the API in the relevant files in `docs/api`.

## Common Wrapper
1. Add code for the API function in `source/src/api.hpp`.
2. Add definitions for the API functions in `extensions/api.hpp`
3. Add documentation for the API in the relevant files in `docs/api`.
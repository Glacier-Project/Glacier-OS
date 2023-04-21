# Dropping Support for Old Devices
1. Update `docs/hardware/support-history.md` with the latest release and the latest commit in which the device is still supported.
2. In some cases, devices may share files (due to similar hardware, for example). Ensure that this either is not the case, or remedy the issue by copying the files to the device's respective folders.
3. Remove the device's files from `source/src/devices`.
4. Remove the device's entry from `source/src/devices/drivers.hpp`.
5. Remove the device's entry from `source/config.hpp`.
6. Remove the device's folder from `docs/hardware`.
7. Remove the device's entry in the `Glacier OS Hardware` section of `docs/TABLE_OF_CONTENTS.md`.
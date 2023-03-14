# TODO
Current goal: Developer preview 1

## App loader
- Load the application into memory

## Hypervisor
- Check application permissions before executing dangerous system calls

## Documentation
- Comment all code

### System Calls
- Document system calls and their structure

## API
### Filesystem

### Display
- Provide re-usable code (shapes + font rendering) in api.hpp - maybe lift code from arcticOS?

### Communication
- Mobile data

### Permissions
- Store current app permissions in memory
- FS access permission
- Separate system folder permission for FS access
- Cellular calls permission
- Cellular texts permission
- Cellular data permission

### UI
- Create menu UI - maybe lift code from arcticOS?
- Create way to let user cycle between UI items to select
- Include font - probably m6x11 as it looks good at small sizes + decent at large ones

## Drivers (Animus)
- Finish filesystem driver
- Create display driver
- Create cellular driver

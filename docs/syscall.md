# GlacierOS System Calls

## Calling
System calls can be called by writing a pointer to a valid syscall object (see `Structure`) to 0x40004000.

## Structure
(1 byte) - Function ID  
(1 byte) - Return value (will be overwritten by syscall)
(n bytes) - Arguments

## System call list
### Information syscalls

### Display syscalls

### Filesystem syscalls

### Communication syscalls

### User input syscalls


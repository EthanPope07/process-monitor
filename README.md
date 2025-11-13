# Process Monitor (C)

A simple Linux process monitoring tool written in C.

## Current Stage
**Stage 1 — Project Initialization**

This version simply sets up the project structure and build system.
Future stages will progressively add features such as:
- Listing process IDs from `/proc`
- Displaying process names
- Showing CPU and memory usage
- Real-time updates with ncurses

##Build Instructions
```bash
make
./procmon

# Process Monitor (C)

A simple Linux process monitoring tool written in C. The end goal of this project is to be a simplified version of 'top'

## Current Stage
**Stage 3 — Display process IDs and names**

This version:
- Lists all running processes by PID
- Displays the process name from `/proc/[pid]/comm`

## Build Instructions
```bash
make
./procmon
```

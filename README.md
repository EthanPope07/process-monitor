# Process Monitor (C)

A simple Linux process monitoring tool written in C.  
Inspired by `top`, this project progressively builds a command-line process monitor, reading data directly from the `/proc` filesystem.

---

## Project Stages
In order to develop this project I divided it into simple stages which showcase the process behind its creation.
### **Stage 1 — Project Initialization**
- Set up project structure (`src/`, `include/`, `Makefile`)
- Added initial `main.c` printing a welcome message
- Created basic README and placeholder header file

### **Stage 2 — List Process IDs**
- Reads `/proc` directory
- Identifies numeric entries corresponding to running processes
- Prints all process IDs to the terminal

### **Stage 3 — Display Process Names**
- Reads `/proc/[pid]/comm` for each process
- Prints PID alongside the process name
- Example:
	- "PID | Name
	-	1 | systemd
	-	317 | bash
	-	1189 | firefox"

### **Stage 4 — CPU & Memory Usage**
- Displays PID, process name, CPU usage (raw jiffies for now)
- Displays memory usage (VmRSS in KB)
- Prepares for real-time percentage calculation in future stages

### **Stage 5 — Real-Time Refresh**
- Process table updates every few seconds
- Clears the terminal for live display
- Users can press Ctrl+C to exit
- Keeps same columns: PID, Name, CPU (raw jiffies), Memory

### **Stage 6 — ncurses UI (Likely Goal)**
- Add a colored, terminal-based interface
- Allow navigation, sorting, and filtering

### **Stage 7 — Polish and Documentation**
- Add test cases and Valgrind checks
- Improve README, comments, and code readability

---

## Build Instructions
```bash
make
./procmon
```

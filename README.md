# Process Monitor (C)

A simple Linux process monitoring tool written in C.  
Inspired by `top`, this project progressively builds a command-line process monitor, reading data directly from the `/proc` filesystem.

---

## Project Stages

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

### **Stage 4 — CPU & Memory Usage (Upcoming)**
- Read `/proc/[pid]/stat` for CPU usage (utime, stime)
- Read `/proc/[pid]/status` for memory usage (VmRSS)
- Display CPU percentage and memory usage per process
- Optional: calculate CPU usage over intervals

### **Stage 5 — Real-Time Refresh**
- Refresh the process table every few seconds
- Clear the terminal on each refresh for live monitoring

### **Stage 6 — ncurses UI (Stretch Goal)**
- Add a colored, terminal-based interface
- Allow navigation, sorting, and filtering

### **Stage 7 — Polish and Documentation**
- Add test cases and Valgrind checks
- Improve README, comments, and code readability

---

## 🛠️ Build Instructions
```bash
make
./procmon
```

#ifndef PROC_H
#define PROC_H

void list_processes(void); //Stage 2
void list_processes_with_names(void); //Stage 3
void list_processes_with_stats(void);  // Stage 4: PID + Name + CPU + Mem
void monitor_processes_realtime(unsigned int interval_sec);  // Stage 5: live refresh

#endif

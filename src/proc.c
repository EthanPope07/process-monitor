#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "proc.h"

#define BUFFER_SIZE 256

typedef struct {
    unsigned long utime;
    unsigned long stime;
} CpuTimes;

unsigned long get_total_jiffies() {
    FILE *fp = fopen("/proc/stat", "r");
    char buffer[BUFFER_SIZE];
    unsigned long user, nice, system, idle;
    if (fp == NULL) return 0;
    fgets(buffer, sizeof(buffer), fp);
    sscanf(buffer, "cpu %lu %lu %lu %lu", &user, &nice, &system, &idle);
    fclose(fp);
    return user + nice + system + idle;
}

CpuTimes get_proc_cpu_times(const char *pid) {
    char path[BUFFER_SIZE];
    snprintf(path, sizeof(path), "/proc/%s/stat", pid);
    FILE *fp = fopen(path, "r");
    CpuTimes times = {0, 0};
    if (fp) {
        char buf[BUFFER_SIZE];
        fgets(buf, sizeof(buf), fp);
        // utime is 14th field, stime is 15th
        char *token = strtok(buf, " ");
        for (int i = 1; token && i <= 15; i++) {
            if (i == 14) times.utime = strtoul(token, NULL, 10);
            if (i == 15) times.stime = strtoul(token, NULL, 10);
            token = strtok(NULL, " ");
        }
        fclose(fp);
    }
    return times;
}

unsigned long get_proc_mem(const char *pid) {
    char path[BUFFER_SIZE];
    snprintf(path, sizeof(path), "/proc/%s/status", pid);
    FILE *fp = fopen(path, "r");
    unsigned long mem = 0;
    char line[BUFFER_SIZE];
    if (fp) {
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "VmRSS:", 6) == 0) {
                sscanf(line + 6, "%lu", &mem); // in KB
                break;
            }
        }
        fclose(fp);
    }
    return mem;
}

// Stage 4 function
void list_processes_with_stats(void) {
    DIR *dir;
    struct dirent *entry;
    char path[BUFFER_SIZE], name[BUFFER_SIZE];
    FILE *fp;

    dir = opendir("/proc");
    if (!dir) {
        perror("opendir");
        return;
    }

    unsigned long total_jiffies_before = get_total_jiffies();

    printf("%-8s | %-20s | %-6s | %-8s\n", "PID", "Name", "CPU%", "Mem(KB)");
    printf("------------------------------------------------------\n");

    while ((entry = readdir(dir))) {
        if (isdigit(entry->d_name[0])) {
            // Get process name
            snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);
            fp = fopen(path, "r");
            if (fp) {
                if (fgets(name, sizeof(name), fp)) {
                    name[strcspn(name, "\n")] = 0; // strip newline
                }
                fclose(fp);
            }

            // Get CPU and memory
            CpuTimes times = get_proc_cpu_times(entry->d_name);
            unsigned long mem = get_proc_mem(entry->d_name);

            // For demo, we’ll just print raw jiffies; accurate % needs interval
            unsigned long cpu_jiffies = times.utime + times.stime;

            printf("%-8s | %-20s | %-6lu | %-8lu\n",
                   entry->d_name, name, cpu_jiffies, mem);
        }
    }

    closedir(dir);
}


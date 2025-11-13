#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include "proc.h"

void list_processes(void) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc");
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    printf("Listing all process IDs:\n");

    while ((entry = readdir(dir)) != NULL) {
        if (isdigit(entry->d_name[0])) {
            printf("Found process: %s\n", entry->d_name);
        }
    }

    closedir(dir);
}

// Stage 3: List PID and process name
void list_processes_with_names(void) {
    DIR *dir;
    struct dirent *entry;
    char path[256];
    char name[256];
    FILE *fp;

    dir = opendir("/proc");
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    printf("%-8s | %s\n", "PID", "Name");
    printf("-------------------------\n");

    while ((entry = readdir(dir)) != NULL) {
        if (isdigit(entry->d_name[0])) {
            // Build path to /proc/[pid]/comm
            snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);
            fp = fopen(path, "r");
            if (fp) {
                if (fgets(name, sizeof(name), fp) != NULL) {
                    // Remove newline character if present
                    name[strcspn(name, "\n")] = 0;
                    printf("%-8s | %s\n", entry->d_name, name);
                }
                fclose(fp);
            }
        }
    }

    closedir(dir);
}

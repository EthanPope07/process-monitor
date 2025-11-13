#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
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
        // Only consider directories with numeric names
        if (isdigit(entry->d_name[0])) {
            printf("Found process: %s\n", entry->d_name);
        }
    }

    closedir(dir);
}

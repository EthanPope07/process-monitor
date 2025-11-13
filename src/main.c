#include <stdio.h>
#include "proc.h"

int main(void) {
    printf("=== Process Monitor ===\n\n");

    // Stage 2 output:
    // list_processes();

    // Stage 3 output:
    //list_processes_with_names();

	// Stage 4 output:
	//list_processes_with_stats();

	// Stage 5 output: (input is seconds per refresh)
	monitor_processes_realtime(1);
	return 0;
}


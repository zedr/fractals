#include <stdio.h>
#include <signal.h>
#include "utils/signal.h"

int EXIT_REQUESTED = 0;

void signal_exit(int sig)
{
	EXIT_REQUESTED = 1;
	fprintf(stderr, "\nExiting...\n");
}

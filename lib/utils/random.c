#include <stdio.h>

int randint(int max, FILE *generator)
{
	return fgetc(generator) % max;
}


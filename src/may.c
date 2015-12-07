#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gfx/gfx.h"

#define TITLE "May"
#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 1024
#define DEFAULT_ITERS 100

void usage()
{
	fputs("Usage: ./may <p> \n", stderr);
}

void compute(float p1)
{
	float k = 0.0;
	float x;
	float inc = 0.025;
	float y = DEFAULT_HEIGHT;
	float x2, y2;
	float p2, p;
	int iters;
	int step = DEFAULT_WIDTH / DEFAULT_ITERS;

	gfx_color(0, 200, 100);

	while (1) {
		iters = 100;
		p = p1;
		x = 0.0;

		while(iters--) {
			p2 = k * p * (1 - p);
			x2 = x + step;
			y2 = DEFAULT_HEIGHT * (1 - p2);

			gfx_line(x, y, x2, y2);

			p = p2;
			x = x2;
			y = y2;
		}

		gfx_sleep(50000000L);

		if (k > 4.0 || k < 0.0)
			inc = -inc;
		k += inc;

		gfx_clear();
	}
	sleep(1);
}

void create_picture()
{
	gfx_open(DEFAULT_WIDTH, DEFAULT_HEIGHT, TITLE);
}

int main(int argc, const char *argv[])
{
	float p;

	if (argc == 2) {
		p = atof(argv[1]);
		create_picture();
		compute(p);
	} else {
		usage();
		return 1;
	}

	return 0;
}

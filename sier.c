#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gfx/gfx.h"


int randint(int max)
{
	FILE *fp = fopen("/dev/urandom", "rb");
	int ch = fgetc(fp);
	fclose(fp);
	return ch % max;
}

void plot_point(int pair[])
{
	gfx_point(pair[0], pair[1]);
}

int main(int argc, const char *argv[])
{
	int tri[3][2];
	int px, py;
	int *vertex;

	tri[0][0] = 320;
	tri[0][1] = 10;

	tri[1][0] = 50;
	tri[1][1] = 190;

	tri[2][0] = 590;
	tri[2][1] = 190;

	// Open a new window for drawing.
	gfx_open(1024, 1024, "Sierpinski");
	gfx_color(0,200,100);

	plot_point(tri[0]);
	plot_point(tri[1]);
	plot_point(tri[2]);

	vertex = tri[randint(3)];
	px = vertex[0];
	py = vertex[1];

	while(1) {
		vertex = tri[randint(3)];
		px = px + (vertex[0] - px) / 2;
		py = py + (vertex[1] - py) / 2;
		gfx_point(px, py);
		//(void) gfx_wait();
	}

	return 0;
}

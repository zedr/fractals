#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gfx/gfx.h"

#define TITLE "Sierpinski"


int randint(int max, FILE *generator)
{
	return fgetc(generator) % max;
}

void plot_point(int pair[])
{
	gfx_point(pair[0], pair[1]);
}

void paint_fractal()
{
	int tri[3][2];
	int px, py;
	int *vertex;
	FILE *fp = fopen("/dev/urandom", "rb");

	tri[0][0] = 320;
	tri[0][1] = 10;

	tri[1][0] = 50;
	tri[1][1] = 190;

	tri[2][0] = 590;
	tri[2][1] = 190;

	plot_point(tri[0]);
	plot_point(tri[1]);
	plot_point(tri[2]);

	vertex = tri[randint(3, fp)];
	px = vertex[0];
	py = vertex[1];

	while(1) {
		vertex = tri[randint(3, fp)];
		px = px + (vertex[0] - px) / 2;
		py = py + (vertex[1] - py) / 2;
		gfx_point(px, py);
	}

	fclose(fp);
}

void create_picture(int width, int height)
{
	// Open a new window for drawing.
	gfx_open(width, height, TITLE);
	gfx_color(0,200,100);
	paint_fractal();
}

int main(int argc, const char *argv[])
{
	unsigned int width = 640;
	unsigned int height = 256;

	create_picture(width, height);
	return 0;
}

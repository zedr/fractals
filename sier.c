#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gfx/gfx.h"

#define TITLE "Sierpinski"

struct point {
	int x;
	int y;
};

int randint(int max, FILE *generator)
{
	return fgetc(generator) % max;
}

void plot_point(struct point *p)
{
	gfx_point(p->x, p->y);
}

void paint_fractal()
{
	FILE *fp = fopen("/dev/urandom", "rb");
	struct point *triangle[3];
	struct point *vertex;
	int px, py;

	triangle[0] = malloc(sizeof *triangle);
	triangle[0]->x = 320;
	triangle[0]->y = 10;

	triangle[1] = malloc(sizeof *triangle);
	triangle[1]->x = 50;
	triangle[1]->y = 190;

	triangle[2] = malloc(sizeof *triangle);
	triangle[2]->x = 590;
	triangle[2]->y = 190;

	plot_point(triangle[0]);
	plot_point(triangle[1]);
	plot_point(triangle[2]);

	vertex = triangle[randint(3, fp)];
	px = vertex->x;
	py = vertex->y;

	while(1) {
		vertex = triangle[randint(3, fp)];
		px = px + (vertex->x - px) / 2;
		py = py + (vertex->y - py) / 2;
		gfx_point(px, py);
	}

	free(triangle[0]);
	free(triangle[1]);
	free(triangle[2]);

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

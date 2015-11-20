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

void paint_fractal(x1, y1, x2, y2, x3, y3)
{
	FILE *fp = fopen("/dev/urandom", "rb");
	struct point *triangle[3];
	struct point *vertex;
	int px, py;

	triangle[0] = malloc(sizeof *triangle);
	triangle[0]->x = x1;
	triangle[0]->y = y1;

	triangle[1] = malloc(sizeof *triangle);
	triangle[1]->x = x2;
	triangle[1]->y = y2;

	triangle[2] = malloc(sizeof *triangle);
	triangle[2]->x = x3;
	triangle[2]->y = y3;

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
	int x1, y1, x2, y2, x3, y3;

	x1 = width / 2;
	y1 = 0;
	x2 = 0;
	y2 = height;
	x3 = width;
	y3 = height;

	// Open a new window for drawing.
	gfx_open(width, height, TITLE);
	gfx_color(0,200,100);

	paint_fractal(x1, y1, x2, y2, x3, y3);
}

int main(int argc, const char *argv[])
{
	unsigned int width = 640;
	unsigned int height = 256;

	create_picture(width, height);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

#include "gfx/gfx.h"
#include "utils/random.h"
#include "utils/signal.h"

#define TITLE "Sierpinski"
#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 800

struct point {
	int x;
	int y;
};

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

	signal(SIGINT, signal_exit);

	while(!EXIT_REQUESTED) {
		vertex = triangle[randint(3, fp)];
		px = px + (vertex->x - px) / 2;
		py = py + (vertex->y - py) / 2;
		gfx_point(px, py);
		gfx_sleep(50000L);
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

	gfx_open(width, height, TITLE);
	gfx_color(0,200,100);

	paint_fractal(x1, y1, x2, y2, x3, y3);
}

int main(int argc, const char *argv[])
{
	unsigned int width, height;

	width = DEFAULT_WIDTH;
	height = DEFAULT_HEIGHT;

	if (argc > 1)
		width = atoi(argv[1]);
	if (argc == 3)
		height = atoi(argv[2]);


	if ((width > 0) && (height > 0)) {
		fprintf(stdout,"Creating %dx%d Sierpinski triangle...\n",
				width,
				height);
		create_picture(width, height);
	} else
		fprintf(stderr, "Cannot create a %dx%d triangle.\n",
				width,
				height);

	return 0;
}

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <assert.h>

#include "graphics.h"

Canvas::Canvas() {
	xres = XRES;
	yres = YRES;
	max_color = MAX_COLOR;
	screen = (color *)calloc(xres * yres, sizeof(color));
}

Canvas::Canvas(int init_xres, int init_yres, int init_max_color) {
	xres = init_xres;
	yres = init_yres;
	max_color = init_max_color;
	screen = (color *)calloc(xres * yres, sizeof(color));
}

void Canvas::plot(color c, int x, int y) {
	if (x >= 0 && x < xres && y >= 0 && y < yres) {
		screen[x + y * xres] = c;
	}
}

void Canvas::plot(color c, point p) {
    plot(c, GET_X(p), GET_Y(p));
}

void Canvas::clear_screen() {
	for (int x = 0 ; x < xres ; x++) {
		for (int y = 0 ; y < yres ; y++) {
			screen[x + y * xres].r = 0;
			screen[x + y * xres].g = 0;
			screen[x + y * xres].b = 0;
		}
	}
}

void Canvas::display() {
	FILE *f;

	f = popen("display", "w");

	fprintf(f, "P3\n%d %d\n%d\n", xres, yres, max_color);

	for (int y = 0 ; y < yres ; y++) {
		for (int x = 0 ; x < xres ; x++) {
			fprintf(f, "%d %d %d ", screen[x + y * xres].r,
					screen[x + y * xres].g,
					screen[x + y * xres].b);
		}
		fprintf(f, "\n");
	}

	pclose(f);
}


void Canvas::save_ppm(const char *file) {
	std::ofstream fout(file);
	fout << "P3\n" << xres << " " << yres << " " << max_color << '\n';

	for (int y = 0 ; y < yres ; y++) {
		for (int x = 0 ; x < xres ; x++) {
			fout << screen[x + y * xres].r << " ";
			fout << screen[x + y * xres].g << " ";
			fout << screen[x + y * xres].b << " ";
		}
		fout << "\n";
	}

	fout.close();
}

void Canvas::draw_line(color c, int x0, int y0, int x1, int y1) {


	int x, y, d, dx, dy;

	x = x0;
	y = y0;

	//swap points so we're always draing left to right
	if ( x0 > x1 ) {
	    draw_line(c, x1, y1, x0, y0);
        return;
	}

	//need to know dx and dy for this version
	dx = (x1 - x) * 2;
	dy = (y1 - y) * 2;

	//positive slope: Octants 1, 2 (5 and 6)
	if ( dy > 0 ) {

		//slope < 1: Octant 1 (5)
		if ( dx > dy ) {
			d = dy - ( dx / 2 );

			while ( x <= x1 ) {
				plot(c, x, y);

				if ( d < 0 ) {
					x = x + 1;
					d = d + dy;
				}
				else {
					x = x + 1;
					y = y + 1;
					d = d + dy - dx;
				}
			}
		}

		//slope > 1: Octant 2 (6)
		else {
			d = ( dy / 2 ) - dx;
			while ( y <= y1 ) {

				plot(c, x, y);
				if ( d > 0 ) {
					y = y + 1;
					d = d - dx;
				}
				else {
					y = y + 1;
					x = x + 1;
					d = d + dy - dx;
				}
			}
		}
	}

	//negative slope: Octants 7, 8 (3 and 4)
	else { 

		//slope > -1: Octant 8 (4)
		if ( dx > abs(dy) ) {

			d = dy + ( dx / 2 );

			while ( x <= x1 ) {

				plot(c, x, y);

				if ( d > 0 ) {
					x = x + 1;
					d = d + dy;
				}
				else {
					x = x + 1;
					y = y - 1;
					d = d + dy + dx;
				}
			}
		}

		//slope < -1: Octant 7 (3)
		else {

			d =  (dy / 2) + dx;

			while ( y >= y1 ) {

				plot(c, x, y);
				if ( d < 0 ) {
					y = y - 1;
					d = d + dx;
				}
				else {
					y = y - 1;
					x = x + 1;
					d = d + dy + dx;
				}
			}
		}
	}
}

void Canvas::draw_line(color c, coor_2d init, coor_2d finish) {
	draw_line(c, init.first, init.second, finish.first, finish.second);
}

void Canvas::draw_line(color c, point i, point f) {
	draw_line(c, GET_X(i), GET_Y(i), GET_X(f), GET_Y(f));
}

void Canvas::draw_edge(color c, edge e) {
	draw_line(c, e.first, e.second);
}

void Canvas::draw_edge_set(color c, edge_set es) {
	size_t sz = es.size();
	for (int i = 0 ; i < sz ; i++) {
		draw_edge(c, es.at(i));
	}
}

void Canvas::draw_point_set(color c, point_set ps) {
    size_t sz = ps.size();
    for (int i = 0 ; i < sz ; i++) {
        plot(c, ps.at(i));
    }
}

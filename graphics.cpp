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

void Canvas::clear_screen() {
    for (int x = 0 ; x < xres ; x++) {
        for (int y = 0 ; y < yres ; y++) {
            screen[x + y * xres].r = 0;
            screen[x + y * xres].g = 0;
            screen[x + y * xres].b = 0;
        }
    }
}

void Canvas::save_ppm(char *file) {
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
    int x, y, d, A, B, tmp;

    if (x1 < x0) { // always flip x0 and x1 such that x1 > x0
        tmp = x0;
        x0 = x1;
        x1 = tmp;
        tmp = y0;
        y0 = y1;
        y1 = tmp;
    }

    // quadrant '1' -- actually looks like quadrant 8 due to origin location
    x = x0;
    y = y0;
    A = y1 - y0; // should be positive
    B = x0 - x1; // should be negative

    if (y1 > y0) {
        d = 2 * A + B;
        if (-1 * B > A) { // octant '1'
            while (x < x1) {
                //std::cout << "point (" << x << ", " << y << ") plotted" << std::endl;
                plot(c, x, y);

                if (d > 0) {
                    y++;
                    d += B;
                }

                x++;
                d += A;
            }
        }
        else { // octant '2'
            while (y < y1) {
                plot(c, x, y);

                if (d < 0) {
                    x++;
                    d += A;
                }

                y++;
                d += B;
            }
        }
    }

    else {
        d = 2 * A - B;
        if (A > B) {
            while (x < x1) { // octant '8'
                plot(c, x, y);

                if (d < 0) {
                    y--;
                    d -= B;
                }

                x++;
                d += A;
            }
        }
        else {
            while (y > y1) { // octant '7'
                plot(c, x, y);

                if (d > 0) {
                    x++;
                    d += A;
                }

                y--;
                d -= B;
            }
        }
    }
}

void Canvas::draw_line(color c, point init, point finish) {
    draw_line(c, init.first, init.second, finish.first, finish.second);
}

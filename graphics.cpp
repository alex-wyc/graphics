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

    if (x1 < x0) { // flip!
        draw_line(c, x1, y1, x0, y0);
        return;
    }

    int x, y, d, A, B;

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

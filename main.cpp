#include <cstdlib>
#include <iostream>

#include "graphics.h"

int main() {
    Canvas screen; // default vals

    color c;

    c.r = 0;
    c.g = 255;
    //c.b = 255;

    screen.clear_screen();

    //{{{ test
    //octant 1
    //screen.draw_line(c, 0, 0, XRES-1, YRES - 75);
    ////octant 2
    //screen.draw_line(c, 0, 0, XRES - 75, YRES-1); 
    ////octant 8
    //screen.draw_line(c, 0, YRES-1, XRES-1, 75);  
    ////octant 7
    //screen.draw_line(c, 0, YRES-1, XRES - 75, 0); // <--!!!

    //c.g = 0;
    //c.b = MAX_COLOR;
    ////octant 5
    //screen.draw_line(c, XRES - 1, YRES - 1, 0, 75);
    ////octant 6
    //screen.draw_line(c, XRES - 1, YRES -1, 75, 0); // <--!!!
    ////octant 4
    //screen.draw_line(c, XRES - 1, 0, 0, YRES - 75);
    ////octant 3
    //screen.draw_line(c, XRES - 1, 0, 75, YRES - 1);

    //c.b = 0;
    //c.r = MAX_COLOR;
    ////y = x, y = -x
    //screen.draw_line(c, 0, 0, XRES - 1, YRES - 1);
    //screen.draw_line(c, 0, YRES - 1, XRES - 1, 0);

    ////horizontal, vertical line
    //screen.draw_line(c, 0, YRES / 2, XRES - 1, YRES / 2);
    //screen.draw_line(c, XRES / 2, 0, XRES / 2, YRES - 1);
    //}}}

    c.r = c.g = MAX_COLOR;
    c.b = 0;
    int d = 10;

    edge_set es;

    //for (int i = 0 ; i < 20 ; i++) {
    //    screen.draw_line(c, XRES/2, YRES/2 + (20 - i) * d, XRES/2 + i * d, YRES/2);
    //    screen.draw_line(c, XRES/2, YRES/2 - (20 - i) * d, XRES/2 - i * d, YRES/2);
    //    screen.draw_line(c, XRES/2, YRES/2 - (20 - i) * d, XRES/2 + i * d, YRES/2);
    //    screen.draw_line(c, XRES/2, YRES/2 + (20 - i) * d, XRES/2 - i * d, YRES/2);
    //}

    for (int i = 0 ; i < 20 ; i++) {
        es.push_back(EDGE(PT(XRES/2, YRES/2 + (20 - i) * d, 0), PT(XRES/2 + i * d, YRES/2, 0)));
        es.push_back(EDGE(PT(XRES/2, YRES/2 - (20 - i) * d, 0), PT(XRES/2 - i * d, YRES/2, 0)));
        es.push_back(EDGE(PT(XRES/2, YRES/2 - (20 - i) * d, 0), PT(XRES/2 + i * d, YRES/2, 0)));
        es.push_back(EDGE(PT(XRES/2, YRES/2 + (20 - i) * d, 0), PT(XRES/2 - i * d, YRES/2, 0)));
    }

    screen.draw_edge_set(c, es);
    es = dilate_figure(es, 1.5, 1, 1);

    c.b = MAX_COLOR;
    screen.draw_edge_set(c, es);

    es = translate_figure(es, -200, 30, 0);
    c.r = 0;
    screen.draw_edge_set(c, es);

    es = rotate_figure(es, Z, 30);
    c.g = 0;
    screen.draw_edge_set(c, es);

    screen.display();
    screen.save_ppm("line.ppm");

    float I[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    float A[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    float B[4][4];

    matrix_multiply_4(B, I, A);

    print_matrix_4(B);
}

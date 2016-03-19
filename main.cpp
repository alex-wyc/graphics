#include <cstdlib>
#include <iostream>

#include "graphics.h"

float sin_x(float t) {
    return 25 * cos(2 * PI * t) + XRES / 2;
}

float sin_y(float t) {
    return 25 * sin(2 * PI * t) + YRES / 2;
}

int main() {
    Canvas screen; // default vals

    color c;

    screen.clear_screen();

    c.r = c.g = MAX_COLOR;
    c.b = MAX_COLOR;
    int d = 10;

    edge_set es = circle(XRES / 2, YRES / 2, 50);
    edge_set es2 = bezier_curve(XRES / 2 - 50, YRES / 2,
                                XRES / 2 - 25, YRES / 2 + 25,
                                XRES / 2 + 25, YRES / 2 - 25,
                                XRES / 2 + 50, YRES / 2);
    edge_set es3 = hermite_curve(XRES / 2 - 50, YRES / 2, 0.5, 0.5,
                                 XRES / 2 + 50, YRES / 2, -0.5, -0.5);

    CONCAT_EDGE_SETS(es, es2);
    CONCAT_EDGE_SETS(es, es3);
    ADD_TO_EDGE_SET(es, EDGE(PT(XRES/2, 0, 0), PT(XRES/2, YRES, 0)));
    ADD_TO_EDGE_SET(es, EDGE(PT(0, YRES/2, 0), PT(XRES, YRES/2, 0)));
    
    screen.draw_edge_set(c, es);
    screen.display();
}

#include <cstdlib>
#include <iostream>

#include "graphics.h"

int main() {
    Canvas screen; // default vals

    color c;

    c.r = 0;
    c.g = 255;
    c.b = 255;

    screen.clear_screen();

    // draw coordinates
    screen.draw_line(c, 250, 0, 250, YRES - 1);
    screen.draw_line(c, 0, 250, XRES - 1, 250);

    // start drawing lines
    c.r = 255;

    // octant 8
    screen.draw_line(c, 0, 230, XRES - 1, 270);
    screen.draw_line(c, XRES - 1, 270, 0, 230);
    //screen.draw_line(c, 230, 0, 280, YRES - 1);
    //screen.draw_line(c, 280, YRES - 1, 230, 0);
    //screen.plot(c,0,0);
    screen.save_ppm("line.ppm");
}

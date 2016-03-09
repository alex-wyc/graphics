#include <cstdlib>
#include <iostream>

#include "graphics.h"

#define PI 3.14159265359

float sin_x(float t) {
    return 25 * cos(2 * PI * t) + XRES / 2;
}

float sin_y(float t) {
    return 25 * sin(2 * PI * t) + YRES / 2;
}

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
    c.b = MAX_COLOR;
    int d = 10;

    edge_set es = generate_edge_set(sin_x, sin_y, 0, 1, 0.1);

    for (int i = 0 ; i < es.size() ; i++) {
                    std::cout << "(" << GET_X(es.at(i).first) << ", ";
                    std::cout << GET_Y(es.at(i).first) << ", ";
                    std::cout << GET_Z(es.at(i).first) << ")--(";
                    std::cout << GET_X(es.at(i).second) << ", ";
                    std::cout << GET_Y(es.at(i).second) << ", ";
                    std::cout << GET_Z(es.at(i).second) << "), ";
                }//for (int   = 0 ; i < 20 ; i++) {
    std::cout << "\n";
    //    screen.draw_line(c, XRES/2, YRES/2 + (20 - i) * d, XRES/2 + i * d, YRES/2);
    //    screen.draw_line(c, XRES/2, YRES/2 - (20 - i) * d, XRES/2 - i * d, YRES/2);
    //    screen.draw_line(c, XRES/2, YRES/2 - (20 - i) * d, XRES/2 + i * d, YRES/2);
    //    screen.draw_line(c, XRES/2, YRES/2 + (20 - i) * d, XRES/2 - i * d, YRES/2);
    //}
    
    screen.draw_edge_set(c, es);
    screen.display();
}

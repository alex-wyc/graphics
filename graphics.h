#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#define XRES 500
#define YRES 500
#define MAX_COLOR 255

struct point_t {
    int r;
    int g;
    int b;
};

typedef struct point_t color;

class Canvas {
        int xres, yres, max_color;
        color *screen;
    public:
        Canvas();
        Canvas(int init_xres, int init_yres, int max_color);
        void plot(color c, int x, int y);
        void clear_screen();
        void save_ppm(char *file);
        void draw_line(color c, int x0, int y0, int x1, int y1);
};

#endif // GRAPHICS_H_

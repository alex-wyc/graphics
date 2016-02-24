#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <tuple>
#include <vector>

#define XRES 500
#define YRES 500
#define MAX_COLOR 255

// I <3 macro hacks
#define GET_X(p) std::get<0>(p)
#define GET_Y(p) std::get<1>(p)
#define GET_Z(p) std::get<2>(p)
#define GET_W(p) std::get<3>(p)

#define MAKE_PT(x, y, z) std::make_tuple(x, y, z, 1)

typedef struct pixel {
    int r;
    int g;
    int b;
} color;

typedef std::pair<int, int> 2d_coor;
typedef std::tuple<float, float, float, float> point;
typedef std::pair<point, point> edge;
typedef std::vector<edge> edge_set;

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
        void draw_line(color c, 2d_coor init, 2d_coor finish);
        void draw_line(color c, point i, point f);
        void draw_edge(color c, edge e);
        void draw_edge_set(color c, edge_set es);
};

#endif // GRAPHICS_H_

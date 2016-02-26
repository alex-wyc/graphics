#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <cmath>
#include <tuple>
#include <vector>

#define XRES 500
#define YRES 500
#define MAX_COLOR 255

#define X 0
#define Y 1
#define Z 2
#define W 3

// I <3 macro hacks
#define GET_X(p) std::get<0>(p)
#define GET_Y(p) std::get<1>(p)
#define GET_Z(p) std::get<2>(p)
#define GET_W(p) std::get<3>(p)

#define PT(x, y, z) std::make_tuple(x, y, z, 1)
#define EDGE(pt1, pt2) std::make_pair(pt1, pt2)

typedef struct pixel {
    int r;
    int g;
    int b;
} color;

typedef std::pair<int, int> coor_2d;
typedef std::tuple<float, float, float, float> point;
typedef std::pair<point, point> edge;
typedef std::vector<edge> edge_set;

class Canvas {
        int xres, yres, max_color;
        color *screen;
    public:
        Canvas();
        Canvas(int init_xres, int init_yres, int max_color);

        void clear_screen();

        void plot(color c, int x, int y);

        void draw_line(color c, int x0, int y0, int x1, int y1);
        void draw_line(color c, coor_2d init, coor_2d finish);
        void draw_line(color c, point i, point f);
        void draw_edge(color c, edge e);
        void draw_edge_set(color c, edge_set es);

        void save_ppm(char *file);
};

float dot_product(float v1[4], float v2[4]);
void transpose_4(float result[4][4]);
void matrix_multiply_4(float result[4][4], float first[4][4], float second[4][4]);

point transform(point v, float A[4][4]);
edge transform(edge e, float A[4][4]);
edge_set transform_figure(edge_set es, float A[4][4]);

void generate_dilation_matrix(float A[4][4], float sx, float sy, float sz);
point dilate(point v, float sx, float sy, float sz);
edge dilate(edge e, float sx, float sy, float sz);
edge_set dilate_figure(edge_set es, float sx, float sy, float sz);

void generate_translation_matrix(float A[4][4], float dx, float dy, float dz);
point translate(point v, float dx, float dy, float dz);
edge translate(edge e, float dx, float dy, float dz);
edge_set translate_figure(edge_set es, float dx, float dy, float dz);

void generate_rotation_matrix(float A[4][4], int axis, float angle);
point rotate(point v, int axis, float angle);
edge rotate(edge e, int axis, float angle);
edge_set rotate_figure(edge_set es, int axis, float angle);

void generate_rotation_matrix(float A[4][4], float ax, float ay, float az);
point rotate(point v, float ax, float ay, float az);
edge rotate(edge e, float ax, float ay, float az);
edge_set rotate_figure(edge_set es, float ax, float ay, float az);

#endif // GRAPHICS_H_

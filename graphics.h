#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <cstring>
#include <string>
#include <cmath>
#include <tuple>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <functional>

#define XRES 500
#define YRES 500
#define MAX_COLOR 255

#define X 0
#define Y 1
#define Z 2
#define W 3

#define PI 3.14159265359

#define DEFAULT_INC 0.01

// I <3 macro hacks
#define GET_X(p) std::get<0>(p)
#define GET_Y(p) std::get<1>(p)
#define GET_Z(p) std::get<2>(p)
#define GET_W(p) std::get<3>(p)

#define PT(x, y, z) std::make_tuple(x, y, z, 1)
#define EDGE(pt1, pt2) std::make_pair(pt1, pt2)
#define ADD_TO_EDGE_SET(es, edge) es.push_back(edge)
#define CONCAT_EDGE_SETS(es1, es2) es1.insert(es1.end(), es2.begin(), es2.end())
#define ADD_TO_POINT_SET(ps, x, y, z) ps.push_back(PT(x, y, z))

typedef struct pixel {
    int r;
    int g;
    int b;
} color;

typedef std::pair<int, int> coor_2d;
typedef std::tuple<float, float, float, float> point;
typedef std::pair<point, point> edge;
typedef std::vector<edge> edge_set;
typedef std::vector<point> point_set;

typedef std::function<float(float)> param_t;

// located in canvas.cpp
class Canvas {
        int xres, yres, max_color;
        color *screen;
    public:
        Canvas();
        Canvas(int init_xres, int init_yres, int max_color);

        void clear_screen();

        void plot(color c, int x, int y);
        void plot(color c, point p);

        void draw_line(color c, int x0, int y0, int x1, int y1);
        void draw_line(color c, coor_2d init, coor_2d finish);
        void draw_line(color c, point i, point f);
        void draw_edge(color c, edge e);
        void draw_edge_set(color c, edge_set es);

        void draw_point_set(color c, point_set ps);

        void display();
        void save_ppm(const char *file);
};

// general utilities, located in util.cpp
edge_set to_edge_set(point_set ps);

// parsing program data, located in parser.cpp
void parse_file(char *filename, Canvas *screen, float A[4][4], edge_set *es);

// linear algebra, located in transformation.cpp
void gen_identity_matrix_4(float A[4][4]);

void print_matrix_4(float A[4][4]);

float dot_product(float v1[4], float v2[4]);
void transpose_4(float A[4][4]);
void matrix_multiply_4(float result[4][4], float first[4][4], float second[4][4]);
void matrix_multiply_scalar(float result[4][4], float matrix[4][4], float scalar);
void matrix_multiply_vector(float result[4], float matrix[4][4], float vec[4]);
void duplicate_matrix(float result[4][4], float src[4][4]);

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

// curve generation, located in curves.cpp
edge_set generate_edge_set(param_t func_x, param_t func_y, float t_0 = 0, float t_1 = 1, float inc = DEFAULT_INC);
edge_set circle(float x0, float y0, float r, float inc = DEFAULT_INC);
edge_set hermite_curve(float x0, float y0,
                       float x1, float y1,
                       float x2, float y2,
                       float x3, float y3,
                       float inc = DEFAULT_INC);
edge_set bezier_curve(float x0, float y0,
                      float x1, float y1,
                      float x2, float y2,
                      float x3, float y3,
                      float inc = DEFAULT_INC);

// 3d images located in 3d.cpp
edge_set box(float x, float y, float z, float dx, float dy, float dz);
point_set generate_sphere(float cx, float cy, float cz, float r, float inc = DEFAULT_INC);
point_set generate_torus(float cx, float cy, float cz, float r1, float r2, float inc = DEFAULT_INC);

#endif // GRAPHICS_H_

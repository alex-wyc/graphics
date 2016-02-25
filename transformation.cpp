/*******************************************************************************
 * linear algebra transformation library written for graphics class            *
 *                                                                             *
 * Authors                                                                     *
 *  Yicheng Wang                                                               *
 *                                                                             *
 * Description                                                                 *
 *  This file handles all the linear transformations in homogeneous            *
 *  coordinates used in computer graphics class, all matrices used here are    *
 *  ROW-MAJOR, i.e. the indices represent [ROW][COLUMN]                        *
 *                                                                             *
 ******************************************************************************/

#include "graphics.h"

#define PI 3.1415926535

float dot_product(float v1[4], float v2[4]) {
    float product = 0;
    for (int i = 0 ; i < 4 ; i++) {
        product += v1[i] * v2[i];
    }
    return product;
}

point transform(point v, float A[4][4]) {
    float v_f[] = {GET_X(v), GET_Y(v), GET_Z(v), GET_W(v)};
    return std::make_tuple(dot_product(v_f, A[0]),
                           dot_product(v_f, A[1]),
                           dot_product(v_f, A[2]),
                           dot_product(v_f, A[3]));
}

float[4][4] generate_dilation_matrix(float sx, float sy, float sz) {
    float A[4][4] = {
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0 ,0, 1}
    };
    return A;
}

point dilate(point v, float sx, float sy, float sz) {
    return transform(v, generate_dilation_matrix(sx, sy, sz));
}

edge dilate(edge e, float sx, float sy, float sz) {
    float A[4][4] = generate_dilation_matrix(sx, sy, sz);
    return EDGE(transform(e.first, A), transform(e.second, A));
}

edge_set dilate_figure(edge_set es, float sx, float sy, float sz) {
    float A[4][4] = generate_dilation_matrix(sx, sy, sz);
    
    size_t s = es.size();
    edge_set to_return(s);

    for (int i = 0 ; i < s ; i++) {
        to_return[i] = EDGE(transform(es.at(i).first, A), transform(es.at(i).second, A));
    }
    return to_return;
}

float[4][4] generate_translation_matrix(float dx, float dy, float dz) {
    float A[4][4] = {
        {1, 0, 0, dx},
        {0, 1, 0, dy},
        {0, 0, 1, dz},
        {0, 0, 0, 1}
    };
    return A;
}

point translate(point v, float dx, float dy, float dz) {
    return transform(v, generate_translation_matrix(dx, dy, dz));
}

edge translate(edge e, float dx, float dy, float dz) {
    float A[4][4] = generate_translation_matrix(dx, dy, dz);
    return EDGE(transform(e.first, A), transform(e.second, A));
}

edge_set translate_figure(edge_set es, float dx, float dy, float dz) {
    float A[4][4] = generate_translation_matrix(dx, dy, dz);

    size_t s = es.size();
    edge_set to_return(s);

    for (int i = 0 ; i < s ; i++) {
        to_return[i] = EDGE(transform(es.at(i).first, A), transform(es.at(i).second, A));
    }
    return to_return;
}

float[4][4] generate_rotation_matrix(int axis, float angle) {
    float a_radian = angle * PI / 180.0;
    float A[4][4];
    switch(axis) {
        case X: // y->z is positive
            A[4][4] = {
                {1, 0, 0, 0},
                {0, cos(a_radian), -1 * sin(a_radian), 0},
                {0, sin(a_radian), cos(a_radian), 0},
                {0, 0, 0, 1}
            };
            break;
        case Y: // x->z is positive
            A[4][4] = {
                {cos(a_radian), 0, -1 * sin(a_radian), 0},
                {0, 1, 0, 0},
                {sin(a_radian), 0, cos(a_radian), 0},
                {0, 0, 0, 1}
            };
            break;
        case Z: // x->y is positive
            A[4][4] = {
                {cos(a_radian), -1 * sin(a_radian), 0, 0},
                {sin(a_radian), cos(a_radian), 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}
            };
            break;
    }
    return A;
}

point rotate(point v, int axis, float angle) {
    return transform(v, generate_rotation_matrix(axis, angle));
}

edge rotate(edge e, int axis, float angle) {
    float A[4][4] = generate_rotation_matrix(axis, angle);
    return EDGE(transform(e.first, A), transform(e.second, A));
}

edge_set rotate_figure(edge_set es, int axis, int angle) {
    float A[4][4] = generate_rotation_matrix(axis, angle);

    size_t s = es.size();
    edge_set to_return(s);
    
    for (int i = 0 ; i < s ; i++) {
        to_return[i] = EDGE(transform(es.at(i).first, A), transform(es.at(i).second, A));
    }

    return to_return;
}

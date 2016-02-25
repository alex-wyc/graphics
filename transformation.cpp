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

point dilate(point v, float sx, float sy, float sz) {
    float A[4][4] = {
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0 ,0, 1}
    };
    return transform(v, A);
}

edge dilate(edge e, float sx, float sy, float sz) {
    float A[4][4] = {
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0 ,0, 1}
    };

    return make_pair(transform(e.first, A), transform(e.second, A));
}

edge_set dilate_figure(edge_set es, float sx, float sy, float sz) {
    size_t s = es.size();
    edge_set to_return(s);

    float A[4][4] = {
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0 ,0, 1}
    };

    for (int i = 0 ; i < s ; i++) {
        to_return[i] = make_pair(transform(es.at(i).first, A), transform(es.at(i).second, A));
    }
    return to_return;
}

point translate(point v, float dx, float dy, float dz) {
    float A[4][4] = {
        {1, 0, 0, dx},
        {0, 1, 0, dy},
        {0, 0, 1, dz},
        {0, 0, 0, 1}
    };
    return transform(v, A);
}

edge translate(edge e, float dx, float dy, float dz) {
    float A[4][4] = {
        {1, 0, 0, dx},
        {0, 1, 0, dy},
        {0, 0, 1, dz},
        {0, 0, 0, 1}
    };
    return make_pair(transform(e.first, A), transform(e.second, A));
}

edge_set translate_figure(edge_set es, float dx, float dy, float dz) {
    size_t s = es.size();
    edge_set to_return(s);

    float A[4][4] = {
        {1, 0, 0, dx},
        {0, 1, 0, dy},
        {0, 0, 1, dz},
        {0, 0, 0, 1}
    };

    for (int i = 0 ; i < s ; i++) {
        to_return[i] = make_pair(transform(es.at(i).first, A), transform(es.at(i).second, A));
    }
    return to_return;
}

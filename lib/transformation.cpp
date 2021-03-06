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

void gen_identity_matrix_4(float A[4][4]) {
    A[0][0] = 1; A[0][1] = 0; A[0][2] = 0; A[0][3] = 0;
    A[1][0] = 0; A[1][1] = 1; A[1][2] = 0; A[1][3] = 0;
    A[2][0] = 0; A[2][1] = 0; A[2][2] = 1; A[2][3] = 0;
    A[3][0] = 0; A[3][1] = 0; A[3][2] = 0; A[3][3] = 1;
}

void print_matrix_4(float A[4][4]) {
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void transpose_4(float A[4][4]) {
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = i + 1 ; j < 4 ; j++) {
            std::swap(A[i][j], A[j][i]);
        }
    }
}

void matrix_multiply_4(float result[4][4], float first[4][4], float second[4][4]) {
    float tmp1[4][4], tmp2[4][4]; // so you can apply the thing to the same goddamn matrix
    duplicate_matrix(tmp1, first);
    duplicate_matrix(tmp2, second);
    transpose_4(tmp2);
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            result[i][j] = dot_product(tmp1[i], tmp2[j]);
        }
    }
}

void matrix_multiply_scalar(float result[4][4], float matrix[4][4], float scalar) {
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            result[i][j] = scalar * matrix[i][j];
        }
    }
}

void matrix_multiply_vector(float result[4], float matrix[4][4], float vec[4]) {
    result[0] = dot_product(vec, matrix[0]);
    result[1] = dot_product(vec, matrix[1]);
    result[2] = dot_product(vec, matrix[2]);
    result[3] = dot_product(vec, matrix[3]);
}

void duplicate_matrix(float result[4][4], float src[4][4]) {
    std::memcpy(result, src, sizeof(float) * 4 * 4);
}

point transform(point v, float A[4][4]) {
    float v_f[] = {GET_X(v), GET_Y(v), GET_Z(v), GET_W(v)};
    return std::make_tuple(dot_product(v_f, A[0]),
                           dot_product(v_f, A[1]),
                           dot_product(v_f, A[2]),
                           dot_product(v_f, A[3]));
}

edge transform(edge e, float A[4][4]) {
    return EDGE(transform(e.first, A), transform(e.second, A));
}

polygon transform(polygon p, float A[4][4]) {
    return POLYGON(transform(GET_X(p), A),
                   transform(GET_Y(p), A),
                   transform(GET_Z(p), A));
}

edge_set transform_figure(edge_set es, float A[4][4]) {
    size_t s = es.size();
    edge_set to_return(s);

    for (int i = 0 ; i < s ; i++) {
        to_return[i] = EDGE(transform(es.at(i).first, A), transform(es.at(i).second, A));
    }
    return to_return;
}

polygon_set transform_figure(polygon_set ps, float A[4][4]) {
    size_t s = ps.size();
    polygon_set to_return(s);

    for (int i = 0 ; i < s ; i++) {
        to_return[i] = POLYGON(transform(std::get<0>(ps.at(i)), A),
                               transform(std::get<1>(ps.at(i)), A),
                               transform(std::get<2>(ps.at(i)), A));
    }

    return to_return;
}

void generate_dilation_matrix(float A[4][4], float sx, float sy, float sz) {
    A[0][0] = sx; A[0][1] = 0; A[0][2] = 0; A[0][3] = 0;
    A[1][0] = 0; A[1][1] = sy; A[1][2] = 0; A[1][3] = 0;
    A[2][0] = 0; A[2][1] = 0; A[2][2] = sz; A[2][3] = 0;
    A[3][0] = 0; A[3][1] = 0; A[3][2] = 0; A[3][3] = 1;
}

point dilate(point v, float sx, float sy, float sz) {
    float A[4][4];
    generate_dilation_matrix(A, sx, sy, sz);
    return transform(v, A);
}

edge dilate(edge e, float sx, float sy, float sz) {
    float A[4][4];
    generate_dilation_matrix(A, sx, sy, sz);
    return EDGE(transform(e.first, A), transform(e.second, A));
}

edge_set dilate_figure(edge_set es, float sx, float sy, float sz) {
    float A[4][4];
    generate_dilation_matrix(A, sx, sy, sz);
    
    size_t s = es.size();
    edge_set to_return(s);

    for (int i = 0 ; i < s ; i++) {
        to_return[i] = EDGE(transform(es.at(i).first, A), transform(es.at(i).second, A));
    }
    return to_return;
}

void generate_translation_matrix(float A[4][4], float dx, float dy, float dz) {
    A[0][0] = 1; A[0][1] = 0; A[0][2] = 0; A[0][3] = dx;
    A[1][0] = 0; A[1][1] = 1; A[1][2] = 0; A[1][3] = dy;
    A[2][0] = 0; A[2][1] = 0; A[2][2] = 1; A[2][3] = dz;
    A[3][0] = 0; A[3][1] = 0; A[3][2] = 0; A[3][3] = 1;
}

point translate(point v, float dx, float dy, float dz) {
    float A[4][4];
    generate_translation_matrix(A, dx, dy, dz);
    return transform(v, A);
}

edge translate(edge e, float dx, float dy, float dz) {
    float A[4][4];
    generate_translation_matrix(A, dx, dy, dz);
    return EDGE(transform(e.first, A), transform(e.second, A));
}

edge_set translate_figure(edge_set es, float dx, float dy, float dz) {
    float A[4][4];
    generate_translation_matrix(A, dx, dy, dz);

    size_t s = es.size();
    edge_set to_return(s);

    for (int i = 0 ; i < s ; i++) {
        to_return[i] = EDGE(transform(es.at(i).first, A), transform(es.at(i).second, A));
    }
    return to_return;
}

void generate_rotation_matrix(float A[4][4], int axis, float angle) {
    float a_radian = angle * PI / 180.0;

    switch(axis) {
        case X: // y->z is positive
            A[0][0] = 1; A[0][1] = 0; A[0][2] = 0; A[0][3] = 0;
            A[1][0] = 0; A[1][1] = cos(a_radian); A[1][2] = -1 * sin(a_radian); A[1][3] = 0;
            A[2][0] = 0; A[2][1] = sin(a_radian); A[2][2] = cos(a_radian); A[2][3] = 0;
            A[3][0] = 0; A[3][1] = 0; A[3][2] = 0; A[3][3] = 1;
            break;

        case Y: // x->z is positive
            A[0][0] = cos(a_radian); A[0][1] = 0; A[0][2] = -1 * sin(a_radian); A[0][3] = 0;
            A[1][0] = 0; A[1][1] = 1; A[1][2] = 0; A[1][3] = 0;
            A[2][0] = sin(a_radian); A[2][1] = 0; A[2][2] = cos(a_radian); A[2][3] = 0;
            A[3][0] = 0; A[3][1] = 0; A[3][2] = 0; A[3][3] = 1;
            break;

        case Z: // x->y is positive
            A[0][0] = cos(a_radian); A[0][1] = -1 * sin(a_radian); A[0][2] = 0; A[0][3] = 0;
            A[1][0] = sin(a_radian); A[1][1] = cos(a_radian); A[1][2] = 0; A[1][3] = 0;
            A[2][0] = 0; A[2][1] = 0; A[2][2] = 1; A[2][3] = 0;
            A[3][0] = 0; A[3][1] = 0; A[3][2] = 0; A[3][3] = 1;
            break;
    }
}

point rotate(point v, int axis, float angle) {
    float A[4][4];
    generate_rotation_matrix(A, axis, angle);
    return transform(v, A);
}

edge rotate(edge e, int axis, float angle) {
    float A[4][4];
    generate_rotation_matrix(A, axis, angle);
    return EDGE(transform(e.first, A), transform(e.second, A));
}

edge_set rotate_figure(edge_set es, int axis, float angle) {
    float A[4][4];
    generate_rotation_matrix(A, axis, angle);

    size_t s = es.size();
    edge_set to_return(s);
    
    for (int i = 0 ; i < s ; i++) {
        to_return[i] = EDGE(transform(es.at(i).first, A), transform(es.at(i).second, A));
    }

    return to_return;
}

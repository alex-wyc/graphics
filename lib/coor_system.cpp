#include "graphics.h"

Coor_system::Coor_system() {
    master[0][0] = 1; master[0][1] = 0; master[0][2] = 0; master[0][3] = 0;
    master[1][0] = 0; master[1][1] = 1; master[1][2] = 0; master[1][3] = 0;
    master[2][0] = 0; master[2][1] = 0; master[2][2] = 1; master[2][3] = 0;
    master[3][0] = 0; master[3][1] = 0; master[3][2] = 0; master[3][3] = 1;
}

void Coor_system::set_master(float A[4][4]) {
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            master[i][j] = A[i][j];
        }
    }
}

Coor_system Coor_system::duplicate() {
    Coor_system to_ret = Coor_system();
    to_ret.set_master(master);
    return to_ret;
}

void Coor_system::translate(float dx, float dy, float dz) {
    float A[4][4];
    generate_translation_matrix(A, dx, dy, dz);
    matrix_multiply_4(master, A, master);
}

void Coor_system::dilate(float dx, float dy, float dz) {
    float A[4][4];
    generate_dilation_matrix(A, dx, dy, dz);
    matrix_multiply_4(master, A, master);
}

void Coor_system::rotate(int axis, float angle) {
    float A[4][4];
    generate_rotation_matrix(A, axis, angle);
    matrix_multiply_4(master, A, master);
}

edge_set Coor_system::transform(edge_set es) {
    return transform_figure(es, master);
}

polygon_set Coor_system::transform(polygon_set ps) {
    return transform_figure(ps, master);
}

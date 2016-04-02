#include "graphics.h"

point_set genera_box(float x, float y, float z, float dx, float dy, float dz) {
    point_set ps;
    //
    //      B          C
    //      /----------/
    //     /|         /|
    //   A/ |      D / |         /-- +x
    //   /----------/  |        /|
    //   |  |F      |  |G     +z |
    //   |  /-------|--/        +y
    //   | /        | /
    //   |/         |/
    //  E|----------/H
    
    // A
    ADD_TO_POINT_SET(ps, x, y, z + dz);
    // B
    ADD_TO_POINT_SET(ps, x, y, z);
    // C
    ADD_TO_POINT_SET(ps, x + dx, y, z);
    // D
    ADD_TO_POINT_SET(ps, x + dx, y, z + dz);
    // E
    ADD_TO_POINT_SET(ps, x, y + dy, z + dz);
    // F
    ADD_TO_POINT_SET(ps, x, y + dy, z);
    // G
    ADD_TO_POINT_SET(ps, x + dx, y + dy, z);
    // H
    ADD_TO_POINT_SET(ps, x + dx, y + dy, z + dz);

    return ps;
}

polygon_set box(point_set box) {
    polygon_set ps;
    
}

point_set generate_sphere(float cx, float cy, float cz, float r, float inc) {
    float x, y, z;
    point_set ps;
    for (float p = 0 ; p < 1 ; p += inc) {
        for (float t = 0 ; t < 1 ; t += inc) {
            x = r * cos(t * PI) + cx;
            y = r * sin(t * PI) * cos(p * 2 * PI) + cy; 
            z = r * sin(t * PI) * sin(p * 2 * PI) + cz;
            ADD_TO_POINT_SET(ps, x, y, z);
        }
    }

    return ps;
}

point_set generate_torus(float cx, float cy, float cz, float r1, float r2, float inc) {
    float x, y, z;
    point_set ps;
    for (float p = 0 ; p < 1 ; p += inc) {
        for (float t = 0 ; t < 1 ; t += inc) {
            x = r1 * cos(t * 2 * PI) + cx;
            y = cos(p * 2 * PI) * (r1 * sin(t * 2 * PI) + r2) + cy;
            z = sin(p * 2 * PI) * (r1 * sin(t * 2 * PI) + r2) + cz;
            ADD_TO_POINT_SET(ps, x, y, z);
        }
    }

    return ps;
}

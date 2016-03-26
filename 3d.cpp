#include "graphics.h"

edge_set box(float x, float y, float z, float dx, float dy, float dz) {
    edge_set es;
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
       
    // BA
    ADD_TO_EDGE_SET(es, EDGE(PT(x, y, z),
                             PT(x, y, z + dz)));
    // BC
    ADD_TO_EDGE_SET(es, EDGE(PT(x, y, z),
                             PT(x + dx, y, z)));
    // BF
    ADD_TO_EDGE_SET(es, EDGE(PT(x, y, z),
                             PT(x, y + dy, z)));
    // AD
    ADD_TO_EDGE_SET(es, EDGE(PT(x, y, z + dz),
                             PT(x + dx, y, z + dz)));
    // CD
    ADD_TO_EDGE_SET(es, EDGE(PT(x + dx, y, z),
                             PT(x + dx, y, z + dz)));
    // DH
    ADD_TO_EDGE_SET(es, EDGE(PT(x + dx, y, z + dz),
                             PT(x + dx, y + dy, z + dz)));
    // FE
    ADD_TO_EDGE_SET(es, EDGE(PT(x, y + dy, z),
                             PT(x, y + dy, z + dz)));
    // EH
    ADD_TO_EDGE_SET(es, EDGE(PT(x, y + dy, z + dz),
                             PT(x + dx, y + dy, z + dz)));
    // FG
    ADD_TO_EDGE_SET(es, EDGE(PT(x, y + dy, z),
                             PT(x + dx, y + dy, z)));
    // HG
    ADD_TO_EDGE_SET(es, EDGE(PT(x + dx, y + dy, z + dz),
                             PT(x + dx, y + dy, z)));
    // AE
    ADD_TO_EDGE_SET(es, EDGE(PT(x, y, z + dz),
                             PT(x, y + dy, z + dz)));
    // CG
    ADD_TO_EDGE_SET(es, EDGE(PT(x + dx, y, z),
                             PT(x + dx, y + dy, z)));

    return es;
}

point_set generate_sphere(float cx, float cy, float cz, float r, float inc) {
    float x, y, z;
    point_set ps;
    for (float p = 0 ; p < 1 + inc ; p += inc) {
        for (float t = 0 ; t < 1 + inc ; t += inc) {
            x = r * cos(t * PI);
            y = r * sin(t * PI) * cos(p * 2 * PI);
            z = r * sin(t * PI) * sin(p * 2 * PI);
            ADD_TO_POINT_SET(ps, x, y, z);
        }
    }

    return ps;
}

point_set generate_torus(float cx, float cy, float cz, float r1, float r2, float inc) {
    float x, y, z;
    point_set ps;
    for (float p = 0 ; p < 1 + inc ; p += inc) {
        for (float t = 0 ; t < 1 + inc ; t += inc) {
            x = r1 * cos(t * 2 * PI);
            y = cos(p * 2 * PI) * (r1 * sin(t * 2 * PI) + r2);
            z = sin(p * 2 * PI) * (r1 * sin(t * 2 * PI) + r2);
            ADD_TO_POINT_SET(ps, x, y, z);
        }
    }

    return ps;
}

#include "graphics.h"

point_set generate_box(float x, float y, float z, float dx, float dy, float dz) {
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

// XXX IMPORTANT: this assumes that the box is generated by the generate-box
// function as defined above
polygon_set get_box_mesh(point_set box) {
    polygon_set ps;
    ADD_TO_POLYGON_SET(ps, POLYGON(box.at(0), box.at(4), box.at(7)));
    ADD_TO_POLYGON_SET(ps, POLYGON(box.at(0), box.at(7), box.at(3)));
    ADD_TO_POLYGON_SET(ps, POLYGON(box.at(3), box.at(7), box.at(6)));
    ADD_TO_POLYGON_SET(ps, POLYGON(box.at(3), box.at(6), box.at(2)));
    ADD_TO_POLYGON_SET(ps, POLYGON(box.at(2), box.at(6), box.at(5)));
    ADD_TO_POLYGON_SET(ps, POLYGON(box.at(2), box.at(5), box.at(1)));
    ADD_TO_POLYGON_SET(ps, POLYGON(box.at(1), box.at(5), box.at(4)));
    ADD_TO_POLYGON_SET(ps, POLYGON(box.at(1), box.at(4), box.at(0)));
    ADD_TO_POLYGON_SET(ps, POLYGON(box.at(7), box.at(4), box.at(5)));
    ADD_TO_POLYGON_SET(ps, POLYGON(box.at(7), box.at(5), box.at(6)));
    ADD_TO_POLYGON_SET(ps, POLYGON(box.at(2), box.at(1), box.at(0)));
    ADD_TO_POLYGON_SET(ps, POLYGON(box.at(2), box.at(0), box.at(3)));

    return ps;
}

point_set generate_sphere(float cx, float cy, float cz, float r, float inc) {
    float x, y, z;
    point_set ps;
    for (float p = 0 ; p < 1 + inc ; p += inc) {
        for (float t = 0 ; t < 1 + inc; t += inc) {
            x = r * cos(t * PI) + cx;
            y = r * sin(t * PI) * cos(p * 2 * PI) + cy; 
            z = r * sin(t * PI) * sin(p * 2 * PI) + cz;
            ADD_TO_POINT_SET(ps, x, y, z);
        }
    }

    return ps;
}

polygon_set get_sphere_mesh(point_set sphere) {
    size_t sz = sphere.size();
    int n = (int) sqrt(sz);
    polygon_set ps;
    for (int j = 0 ; j < sz ; j = j + n) {
        for (int i = 0 ; i < n - 1 ; i++) {
            ADD_TO_POLYGON_SET(ps, POLYGON(sphere[(j + i) % sz],
                                           sphere[(j + n + ((i + 1) % n)) % sz],
                                           sphere[(j + i + n) % sz]));
            ADD_TO_POLYGON_SET(ps, POLYGON(sphere[(j + i) % sz],
                                           sphere[(j + ((i + 1) % n)) % sz],
                                           sphere[(j + n + ((i + 1) % n)) % sz]));
        }
    }
    return ps;
}

point_set generate_torus(float cx, float cy, float cz, float r1, float r2, float inc) {
    float x, y, z;
    point_set ps;
    for (float p = 0 ; p < 1 + inc ; p += inc) {
        for (float t = 0 ; t < 1 + inc ; t += inc) {
            x = r1 * cos(t * 2 * PI) + cx;
            y = cos(p * 2 * PI) * (r1 * sin(t * 2 * PI) + r2) + cy;
            z = sin(p * 2 * PI) * (r1 * sin(t * 2 * PI) + r2) + cz;
            ADD_TO_POINT_SET(ps, x, y, z);
        }
    }

    return ps;
}

polygon_set get_torus_mesh(point_set torus) { // FIXME
    size_t sz = torus.size();
    //n += sz % n;
    //std::cout << sz % n << '\n';
    //getchar();
    int n = (int) sqrt(sz);
    polygon_set ps;
    for (int j = 0 ; j < sz ; j = j + n) {
        for (int i = 0 ; i < n ; i++) {
            ADD_TO_POLYGON_SET(ps, POLYGON(torus[(j + i) % sz],
                                           torus[(j + n + ((i + 1) % n)) % sz],
                                           torus[(j + i + n) % sz]));
            ADD_TO_POLYGON_SET(ps, POLYGON(torus[(j + i) % sz],
                                           torus[(j + ((i + 1) % n)) % sz],
                                           torus[(j + n + ((i + 1) % n)) % sz]));
        }
    }

    return ps;
}

#include "graphics.h"

edge_set to_edge_set(point_set ps) {
    size_t sz = ps.size();
    edge_set es;
    for(int i = 0 ; i < sz ; i++) {
        ADD_TO_EDGE_SET(es, EDGE(ps.at(i), ps.at(i)));
    }
    return es;
}

edge_set to_edge_set(polygon_set ps) {
    size_t sz = ps.size();
    edge_set es;
    for (int i = 0 ; i < sz ; i++) {
        ADD_TO_EDGE_SET(es, EDGE(std::get<0>(ps.at(i)), std::get<1>(ps.at(i))));
        ADD_TO_EDGE_SET(es, EDGE(std::get<1>(ps.at(i)), std::get<2>(ps.at(i))));
        ADD_TO_EDGE_SET(es, EDGE(std::get<2>(ps.at(i)), std::get<0>(ps.at(i))));

    }
    return es;
}

float dot_product(float v1[4], float v2[4]) {
    float product = 0;
    for (int i = 0 ; i < 4 ; i++) {
        product += v1[i] * v2[i];
    }
    return product;
}

void cross_product(float res[4], float v1[4], float v2[4], float v3[4]) {
    float vec1[4] = {v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2], 1};
    float vec2[4] = {v3[0] - v2[0], v3[1] - v2[1], v3[2] - v3[2], 1};
    res[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    res[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
    res[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
    res[3] = 1;
}

float *to_array(point p) {
    float *arr = (float *)malloc(4 * sizeof(float));
    arr[0] = GET_X(p);
    arr[1] = GET_Y(p);
    arr[2] = GET_Z(p);
    arr[3] = GET_W(p);
    return arr;
}

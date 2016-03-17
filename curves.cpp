#include <assert.h>

#include "graphics.h"

edge_set generate_edge_set(param_t func_x, param_t func_y,
                           float t0, float t1, float inc = DEFAULT_INC) {
    assert((t1 > t0 && inc > 0) || (t1 < t0 && inc < 0));
    edge_set es;
    float x0 = func_x(t0);
    float y0 = func_y(t0);
    float x, y;

    for (float t = t0 ; t < t1 ; t += inc) {
        x = func_x(t);
        y = func_y(t);
        ADD_TO_EDGE_SET(es, EDGE(PT(x0, y0, 0), PT(x, y, 0)));
        x0 = x;
        y0 = y;
    }

    return es;
}

edge_set hermite_curve(float x0, float y0, float dx0, float dy0,
                       float x1, float y1, float dx1, float dy1,
                       float inc = DEFAULT_INC) {
    float given_x[4] = {x0, dx0, x1, dx1};
    float given_y[4] = {y0, dy0, y1, dy1};

    float inverse[4][4] = {
        {2, -2, 1, 1},
        {-3, 3, -2, -1},
        {0, 0, 1, 0},
        {1, 0, 0, 0}
    };

    float res_x[4], res_y[4];
    matrix_multiply_vector(res_x, inverse, given_x);
    matrix_multiply_vector(res_y, inverse, given_y);

    std::function<float(float)> func_x = [res_x](float t) {
        return res_x[0] * pow(t, 3) + res_x[1] * pow(t, 2) + res_x[2] * t + res_x[3];
    };

    std::function<float(float)> func_y = [res_y](float t) {
        return res_y[0] * pow(t, 3) + res_y[1] * pow(t, 2) + res_y[2] * t  + res_y[3];
    };

    return generate_edge_set(func_x, func_y, 0, 1, inc);
}

edge_set bezier_curve(float x0, float y0,
                      float x1, float y1,
                      float x2, float y2,
                      float x3, float y3,
                      float inc = DEFAULT_INC) {

    std::function<float(float)> func_x = [x0, x1, x2, x3] (float t) {
        return x0 * pow((1 - t), 3) + 3 * x1 * pow((1 - t), 2) * t + 3 * x2 * (1 - t) * pow(t, 2) + x3 * pow(t, 3);
    };

    std::function<float(float)> func_y = [y0, y1, y2, y3] (float t) {
        return y0 * pow((1 - t), 3) + 3 * y1 * pow((1 - t), 2) * t + 3 * y2 * (1 - t) * pow(t, 2) + y3 * pow(t, 3);
    };

    return generate_edge_set(func_x, func_y, 0, 1, inc);
}

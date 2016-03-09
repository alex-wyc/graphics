#include <assert.h>

#include "graphics.h"

edge_set generate_edge_set(param_t func_x, param_t func_y,
                           float t0, float t1, float inc) {
    assert((t1 > t0 && inc > 0) || (t1 < t0 && inc < 0));
    edge_set es;
    float x0 = func_x(t0);
    float y0 = func_y(t0);
    float x, y;

    for (float t = t0 ; t < t1 ; t += inc) {
        x = func_x(t);
        y = func_y(t);
        std::cout << x << ',';
        std::cout << y << '\n';
        ADD_TO_EDGE_SET(es, EDGE(PT(x0, y0, 0), PT(x, y, 0)));
        x0 = x;
        y0 = y;
    }

    return es;
}

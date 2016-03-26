#include "graphics.h"

edge_set to_edge_set(point_set ps) {
    size_t sz = ps.size();
    edge_set es;
    for(int i = 0 ; i < sz ; i++) {
        ADD_TO_EDGE_SET(es, EDGE(ps.at(i), ps.at(i)));
    }
    return es;
}

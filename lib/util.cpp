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

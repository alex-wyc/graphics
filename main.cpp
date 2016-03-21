#include <cstdlib>
#include <iostream>

#include "graphics.h"

int main(int argc, char *argv[]) {
    Canvas *screen = new Canvas();
    float A[4][4];
    edge_set es;
    if (argc == 2) {
        parse_file(argv[1], screen, A, &es);
    }
    return 0;
}

#include <cstdlib>
#include <iostream>

#include "graphics.h"

int main(int argc, char *argv[]) {
    if (argc == 2) {
        parse_file(argv[1]);
    }
    return 0;
}

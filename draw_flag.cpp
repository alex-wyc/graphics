#include "graphics.h"

int main(int argc, char *argv[]) {

    color red;
    red.r = 255;
    red.g = red.b = 0;

    color yellow;
    yellow.r = yellow.g = 255;
    yellow.b = 0;

    Canvas screen(600, 400, 255);
    screen.clear_screen();
    for (int x = 0 ; x < 600 ; x++) {
        for (int y = 0 ; y < 400 ; y++) {
            screen.plot(red, x, y);
        }
    }

    edge_set star;
    float rotate_36[4][4];
    generate_rotation_matrix(rotate_36, Z, 36);

    edge e = EDGE(PT(0, 0, 0), PT(120,0,0));
    ADD_TO_EDGE_SET(star, e);

    e = transform(e, rotate_36);
    ADD_TO_EDGE_SET(star, e);

    e = transform(e, rotate_36);
    ADD_TO_EDGE_SET(star, translate(e, 60, -42, 0));

    e = transform(e, rotate_36);
    ADD_TO_EDGE_SET(star, translate(e, 60, -42, 0));

    e = transform(e, rotate_36);
    ADD_TO_EDGE_SET(star, translate(e, 120, 0, 0));

    star = translate_figure(star, -63, -19.4, 0);

    edge_set tmp = dilate_figure(star, 0.97, 0.97, 1);
    star.insert(star.end(), tmp.begin(), tmp.end());

    tmp = dilate_figure(star, 0.95, 0.95, 1);
    star.insert(star.end(), tmp.begin(), tmp.end());

    tmp = dilate_figure(star, 0.9, 0.9, 1);
    star.insert(star.end(), tmp.begin(), tmp.end());

    tmp = dilate_figure(star, 0.85, 0.85, 1);
    star.insert(star.end(), tmp.begin(), tmp.end());

    tmp = dilate_figure(star, 0.75, 0.75, 1);
    star.insert(star.end(), tmp.begin(), tmp.end());

    tmp = dilate_figure(star, 0.5, 0.5, 1);
    star.insert(star.end(), tmp.begin(), tmp.end());

    tmp = dilate_figure(star, 0.2, 0.2, 1);
    star.insert(star.end(), tmp.begin(), tmp.end());

    screen.draw_edge_set(yellow, translate_figure(star, 100, 100, 0));

    tmp = dilate_figure(star, 0.33, 0.33, 1);

    float A[4][4];
    generate_rotation_matrix(A, Z, 18);

    tmp = transform_figure(tmp, A);

    screen.draw_edge_set(yellow, translate_figure(tmp, 200, 40, 0));

    tmp = rotate_figure(tmp, Z, 36);

    screen.draw_edge_set(yellow, translate_figure(tmp, 240, 80, 0));

    tmp = rotate_figure(tmp, Z, 18);

    screen.draw_edge_set(yellow, translate_figure(tmp, 240, 140, 0));

    tmp = rotate_figure(tmp, Z, 18);

    screen.draw_edge_set(yellow, translate_figure(tmp, 200, 180, 0));

    screen.save_ppm("chinese_flag.ppm");
    return 0;
}

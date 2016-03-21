#include "graphics.h"

/* line: add a line to the point matrix -  takes 6 arguemnts (x0, y0, z0, x1, y1, z1)
 *
 * circle: adds a circle to the edge matrix - takes 3 parameters (cx, cy, r)
 *
 * hermite: adds a hermite curve to the edge matrix - takes 8 parameters (x0, y0, dx0, dy0, x1, y1, dx1, dy1)
 * remember the curve is between points (x0, y0) and (x1, y1).
 * (dx0, dy0) and (dx1, dy1) are the rates of change at the endpoints
 *
 * b: adds a bezier curve to the edge matrix - takes 8 parameters (x0, y0, x1, y1, x2, y2, x3, y3)
 * This curve is drawn between (x0, y0) and (x3, y3)
 *
 * ident: set the transform matrix to the identity matrix
 *
 * scale: create a scale matrix, then multiply the transform matrix by the scale matrix -  takes 3 arguments (sx, sy, sz)
 *
 * translate: create a translation matrix, then multiply the transform matrix by the translation matrix - takes 3 arguments (tx, ty, tz)
 *
 * xrotate: create an x-axis rotation matrix, then multiply the transform matrix by the rotation matrix - takes 1 argument (theta)
 *
 * yrotate: create an y-axis rotation matrix, then multiply the transform matrix by the rotation matrix - takes 1 argument (theta)
 *
 * zrotate: create an z-axis rotation matrix, then multiply the transform matrix by the rotation matrix - takes 1 argument (theta)
 *
 * apply: apply the current transformation matrix to the edge matrix
 *
 * display: draw the lines of the point matrix to the screen, display the screen
 *
 * save: draw the lines of the point matrix to the screen/frame save the screen/frame to a file - takes 1 argument (file name)
 */
void parse_file(char *file, Canvas *screen, float A[4][4], edge_set *es) {
    char command[256];
    float args[8] = {0};
    edge_set tmp;
    float current[4][4];
    color c;
    c.r = c.g = c.b = 255;

    // FIXME add ability to read from term
    std::ifstream fin(file);

    while (!fin.eof()) {
        fin >> command;
        switch (command[0]) {
            case 'l': // line
                for (int i = 0 ; i < 6 ; i++) {
                    fin >> args[i];
                }
                es->push_back(EDGE(PT(args[0], args[1], args[2]),
                                   PT(args[3], args[4], args[5])));

                break;

            case 'c': // circle
                fin >> args[0] >> args[1] >> args[2];
                tmp = circle(args[0], args[1], args[2]);
                es->insert(es->end(), tmp.begin(), tmp.end());
                break;

            case 'h': // hermite
                for (int i = 0 ; i < 8 ; i++) {
                    fin >> args[i];
                }
                tmp = hermite_curve(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
                es->insert(es->end(), tmp.begin(), tmp.end());
                break;

            case 'b': // bezier
                for (int i = 0 ; i < 8 ; i++) {
                    fin >> args[i];
                }
                tmp = bezier_curve(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
                es->insert(es->end(), tmp.begin(), tmp.end());
                break;

            case 'i': // ident
                gen_identity_matrix_4(A);
                break;

            case 's': // scale
                if (command[1] == 'c') { // scale
                    fin >> args[0] >> args[1] >> args[2];
                    generate_dilation_matrix(current, args[0], args[1], args[2]);
                    matrix_multiply_4(A, current, A);
                }
                else if (command[1] == 'a') { // save
                    fin >> command; // filename
                    screen->clear_screen();
                    screen->draw_edge_set(c, *es);
                    screen->save_ppm(command);
                }
                break;

            case 't': // translate
                fin >> args[0] >> args[1] >> args[2];
                generate_translation_matrix(current, args[0], args[1], args[2]);
                matrix_multiply_4(A, current, A);
                break;

            case 'x': // xrotate
                fin >> args[0];
                generate_rotation_matrix(current, X, args[0]);
                matrix_multiply_4(A, current, A);
                break;

            case 'y': // yrotate
                fin >> args[0];
                generate_rotation_matrix(current, Y, args[0]);
                matrix_multiply_4(A, current, A);
                break;

            case 'z': // zrotate
                fin >> args[0];
                generate_rotation_matrix(current, Z, args[0]);
                matrix_multiply_4(A, current, A);
                break;

            case 'a': // apply
                tmp = transform_figure(*es, A);
                es = &tmp;
                break;

            case 'd': // display
                screen->clear_screen();
                screen->draw_edge_set(c, *es);
                screen->display();
                break;

            case 'q': //quit
                return;
                break;
        }
    }
}

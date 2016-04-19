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
void parse_file(char *file, int debug) {
    Canvas screen;
    char command[256];
    float args[8] = {0};
    edge_set es, tmp;
    polygon_set ps, tmp_p;
    color c;
    c.r = c.g = c.b = 255;
    size_t sz;
    float inc = DEFAULT_INC;

    std::stack<Coor_system> origins;

    Coor_system ident;
    origins.push(ident);

    // FIXME add ability to read from term
    std::ifstream fin(file);

    while (!fin.eof()) {
        //getchar();
        fin >> command;
        if (debug) {
            std::cout << ":" << command << ":\n";
            //std::cout << origins.size() << '\n';
        }
        switch (command[0]) {
            case '#': // comment -- do nothing, scan next
                fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            
            // {{{ push and pop
            case 'p': // push or pop
                if (command[1] == 'u') { // push
                    Coor_system dup_cs = origins.top().duplicate();
                    origins.push(dup_cs);
                }
                else if (command[1] == 'o') { // pop
                    origins.pop();
                }
                break;
            // }}}
            // {{{ line
            case 'l': // line
                for (int i = 0 ; i < 6 ; i++) {
                    fin >> args[i];
                }
                es.push_back(EDGE(PT(args[0], args[1], args[2]),
                                   PT(args[3], args[4], args[5])));
                tmp = origins.top().transform(es);
                screen.draw_edge_set(c, tmp);
                es.clear();
                tmp.clear();

                break;
            // }}}
            // {{{ circle or clear
            case 'c': // circle or clear
                if (command[1] == 'i') { // circle
                    fin >> args[0] >> args[1] >> args[2];
                    tmp = circle(args[0], args[1], args[2]);
                    sz = tmp.size();
                    for (int i = 0 ; i < sz ; i++) {
                        es.push_back(tmp.at(i));
                    }
                    tmp = origins.top().transform(es);
                    screen.draw_edge_set(c, tmp);
                    es.clear();
                    tmp.clear();
                }
                else if (command[1] == 'l') { // clear
                    screen.clear_screen();
                }
                break;
            // }}}
            // {{{ hermite
            case 'h': // hermite
                for (int i = 0 ; i < 8 ; i++) {
                    fin >> args[i];
                }
                tmp = hermite_curve(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
                sz = tmp.size();
                for (int i = 0 ; i < sz ; i++) {
                    es.push_back(tmp.at(i));
                }
                tmp = origins.top().transform(es);
                screen.draw_edge_set(c, tmp);
                es.clear();
                tmp.clear();
                break;
            // }}}
            // {{{ bezier or box
            case 'b': // bezier or box
                if (command[1] == 'e') { // bezier
                    for (int i = 0 ; i < 8 ; i++) {
                        fin >> args[i];
                    }
                    tmp = bezier_curve(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
                    sz = tmp.size();
                    for (int i = 0 ; i < sz ; i++) {
                        es.push_back(tmp.at(i));
                    }
                    tmp = origins.top().transform(es);
                    screen.draw_edge_set(c, tmp);
                    es.clear();
                    tmp.clear();
                }
                else if (command[1] == 'o') { // box
                    for (int i = 0 ; i < 6 ; i++) {
                        fin >> args[i];
                    }
                    tmp_p = get_box_mesh(generate_box(args[0], args[1], args[2], args[3], args[4], args[5]));
                    sz = tmp_p.size();
                    for (int i = 0 ; i < sz ; i++) {
                        ps.push_back(tmp_p.at(i));
                    }
                    tmp_p = origins.top().transform(ps);
                    screen.draw_polygon_set(c, tmp_p);
                    ps.clear();
                    tmp_p.clear();
                }
                break;
            // }}}
            // {{{ scale/save/sphere/set
            case 's': // scale or save or sphere or set
                if (command[1] == 'c') { // scale
                    fin >> args[0] >> args[1] >> args[2];
                    origins.top().dilate(args[0], args[1], args[2]);
                }
                else if (command[1] == 'a') { // save
                    fin >> command; // filename
                    screen.save_ppm(command);
                }
                else if (command[1] == 'p') { // sphere
                    fin >> args[0] >> args[1] >> args[2] >> args[3];
                    tmp_p = get_sphere_mesh(generate_sphere(args[0], args[1], args[2], args[3], inc));
                    sz = tmp_p.size();
                    for (int i = 0 ; i < sz ; i++) {
                        ps.push_back(tmp_p.at(i));
                    }
                    tmp_p = origins.top().transform(ps);
                    screen.draw_polygon_set(c, tmp_p);
                    ps.clear();
                    tmp_p.clear();
                }
                else if (command[1] == 'e') { // set
                    fin >> command; // color or increment
                    switch (command[0]) {
                        case 'c': // color
                            fin >> c.r >> c.g >> c.b;
                            break;
                        case 'i': // increment
                            fin >> inc;
                            printf("%f\n", inc);
                            break;
                    }
                }
                break;
            // }}}
            // {{{ translate or torus
            case 't': // translate or torus
                if (command[1] == 'r') {
                    fin >> args[0] >> args[1] >> args[2];
                    origins.top().translate(args[0], args[1], args[2]);
                }
                else if (command[1] == 'o') { // torus TODO
                    fin >> args[0] >> args[1] >> args[2] >> args[3] >> args[4];
                    tmp_p = get_torus_mesh(generate_torus(args[0], args[1], args[2], args[3], args[4], inc));
                    sz = tmp_p.size();
                    for (int i = 0 ; i < sz ; i++) {
                        ps.push_back(tmp_p.at(i));
                    }
                    tmp_p = origins.top().transform(ps);
                    screen.draw_polygon_set(c, tmp_p);
                    ps.clear();
                    tmp_p.clear();
                }
                break;
            // }}}
            // {{{ xrotate/yrotate/zrotate
            case 'x': // xrotate
                fin >> args[0];
                origins.top().rotate(X, args[0]);
                break;

            case 'y': // yrotate
                fin >> args[0];
                origins.top().rotate(Y, args[0]);
                break;

            case 'z': // zrotate
                fin >> args[0];
                origins.top().rotate(Z, args[0]);
                break;
            // }}}
            // {{{ display
            case 'd': // display
                screen.display();
                break;
            // }}}
            // {{{ quit
            case 'q': //quit
                return;
                break;
            // }}}

            default:
                std::cout << "Parser error:\ncommand not found: " << command << '\n';
                return;
        }
    }
}

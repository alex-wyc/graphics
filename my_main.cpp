/*========== my_main.c ==========

  This is the only file you need to modify in order
  to get a working mdl project (for now).

  my_main.c will serve as the interpreter for mdl.
  When an mdl script goes through a lexer and parser, 
  the resulting operations will be in the array op[].

  Your job is to go through each entry in op and perform
  the required action from the list below:

push: push a new origin matrix onto the origin stack
pop: remove the top matrix on the origin stack

move/scale/rotate: create a transformation matrix 
based on the provided values, then 
multiply the current top of the
origins stack by it.

box/sphere/torus: create a solid object based on the
provided values. Store that in a 
temporary matrix, multiply it by the
current top of the origins stack, then
call draw_polygons.

line: create a line based on the provided values. Store 
that in a temporary matrix, multiply it by the
current top of the origins stack, then call draw_lines.

save: call save_extension with the provided filename

display: view the image live

jdyrlandweaver
=========================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "lib/parser.h"
#include "lib/symtab.h"
#include "y.tab.h"

#include "lib/graphics.h"

void my_main( int polygons ) {

    Canvas screen;
    std::stack<Coor_system> origins;
    color c;
    edge_set es, tmp;
    polygon_set ps, tmp_p;

    float inc = DEFAULT_INC;

    Coor_system ident;
    origins.push(ident);

    screen.clear_screen();

    size_t sz;

    for (int i = 0 ; i < lastop ; i++) {  
        switch (op[i].opcode) {
            case SET:
                break;

            case PUSH:
                {
                    Coor_system dup_cs = origins.top().duplicate();
                    origins.push(dup_cs);
                    break;
                }

            case POP:
                {
                    origins.pop();
                    break;
                }

            case MOVE:
                {
                    origins.top().translate(op[i].op.move.d[0],
                            op[i].op.move.d[1],
                            op[i].op.move.d[2]);
                    break;
                }

            case ROTATE:
                {
                    origins.top().rotate(op[i].op.rotate.axis, op[i].op.rotate.degrees);
                    break;
                }

            case SCALE:
                {
                    origins.top().dilate(op[i].op.scale.d[0],
                            op[i].op.scale.d[1],
                            op[i].op.scale.d[2]);
                    break;
                }

            case BOX:
                {
                    tmp_p = get_box_mesh(generate_box(op[i].op.box.d0[0],
                                op[i].op.box.d0[1],
                                op[i].op.box.d0[2],
                                op[i].op.box.d1[0],
                                op[i].op.box.d1[1],
                                op[i].op.box.d1[2]));
                    sz = tmp_p.size();
                    for (int i = 0 ; i < sz ; i++) {
                        ps.push_back(tmp_p.at(i));
                    }
                    tmp_p = origins.top().transform(ps);
                    screen.draw_polygon_set(c, tmp_p);
                    ps.clear();
                    tmp_p.clear();
                    break;
                }

            case SPHERE:
                {
                    tmp_p = get_sphere_mesh(generate_sphere(op[i].op.sphere.d[0],
                                op[i].op.sphere.d[1],
                                op[i].op.sphere.d[2],
                                op[i].op.sphere.r,
                                inc));
                    sz = tmp_p.size();
                    for (int i = 0 ; i < sz ; i++) {
                        ps.push_back(tmp_p.at(i));
                    }
                    tmp_p = origins.top().transform(ps);
                    screen.draw_polygon_set(c, tmp_p);
                    ps.clear();
                    tmp_p.clear();
                    break;
                }

            case TORUS:
                {
                    tmp_p = get_torus_mesh(generate_torus(op[i].op.torus.d[0],
                                op[i].op.torus.d[1],
                                op[i].op.torus.d[2],
                                op[i].op.torus.r0,
                                op[i].op.torus.r1,
                                inc));
                    sz = tmp_p.size();
                    for (int i = 0 ; i < sz ; i++) {
                        ps.push_back(tmp_p.at(i));
                    }
                    tmp_p = origins.top().transform(ps);
                    screen.draw_polygon_set(c, tmp_p);
                    ps.clear();
                    tmp_p.clear();
                    break;
                }

            case LINE:
                {
                    es.push_back(EDGE(PT(op[i].op.line.p0[0], op[i].op.line.p0[1], op[i].op.line.p0[2]),
                                PT(op[i].op.line.p1[0], op[i].op.line.p1[1], op[i].op.line.p1[2])));
                    tmp = origins.top().transform(es);
                    screen.draw_edge_set(c, tmp);
                    es.clear();
                    tmp.clear();
                    break;
                }

            case SAVE:
                {
                    screen.save_ppm(op[i].op.save.p->name);
                    break;
                }

            case DISPLAY:
                {
                    screen.display();
                    break;
                }
        }
    }
}

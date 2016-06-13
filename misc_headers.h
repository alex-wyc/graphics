#ifndef MISC_HEADERS_H
#define MISC_HEADERS_H

#include "ml6.h"

int num_frames;
char name[128];
color g;
struct constants *k;

struct vary_node {
  
  char name[128];
  double value;
  struct vary_node *next;
};

void import_mesh(struct matrix *dest, char *filepath);
void my_main();
void print_knobs();
void process_knobs();
void first_pass();
struct vary_node ** second_pass();

#endif

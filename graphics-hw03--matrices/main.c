#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {
  
  // GENERAL MATRIX DEMO
  
  struct matrix *a;
  a = new_matrix(2,2);
  ident(a);
  (a->m)[0][1] = 1;
  (a->m)[1][0] = 2;
  printf("\nMATRIX A:\n");
  print_matrix(a);
  
  struct matrix *b;
  b = new_matrix(2,3);
  (b->m)[0][0] = 1;
  (b->m)[0][1] = 2;
  (b->m)[0][2] = 3;
  (b->m)[1][0] = 4;
  (b->m)[1][1] = 5;
  (b->m)[1][2] = 6;
  b->lastcol = 3;
  printf("\nMATRIX B:\n");
  print_matrix(b);

  printf("\n\nMATRIX A * MATRIX B:\n");
  matrix_mult(a, b);
  print_matrix(b);

  free_matrix(a);
  free_matrix(b);


  
  // GRAPHICS MATRIX DEMO
  screen s;
  clear_screen(s);
  color c;
  
  struct matrix *redPrism;
  redPrism = new_matrix(4, 4);
  c.red = 255;
  c.green = 0;
  c.blue = 0;
  
  add_edge(redPrism, 260, 50, 0, 50, 413, 0);
  add_edge(redPrism, 297, 71, 0, 260, 50, 0);
  add_edge(redPrism, 260, 50, 0, 50, 171, 0);
  add_edge(redPrism, 50, 171, 0, 50, 413, 0);
  add_edge(redPrism, 50, 413, 0, 169, 479, 0);
  add_edge(redPrism, 169, 479, 0, 210, 410, 0);

  printf("\n\nredPrism:\n");
  print_matrix(redPrism);
  draw_lines(redPrism, s, c);


  
  struct matrix *greenPrism;
  greenPrism = new_matrix(4, 4);
  c.red = 0;
  c.green = 255;
  c.blue = 0;

  add_edge(greenPrism, 130, 362, 0, 250, 430, 0);
  add_edge(greenPrism, 250, 430, 0, 428, 326, 0);
  add_edge(greenPrism, 428, 326, 0, 428, 118, 0);
  add_edge(greenPrism, 428, 118, 0, 310, 50, 0);
  add_edge(greenPrism, 310, 50, 0, 130, 362, 0);
  add_edge(greenPrism, 130, 362, 0, 310, 258, 0);
  add_edge(greenPrism, 428, 326, 0, 310, 258, 0);
  add_edge(greenPrism, 310, 258, 0, 310, 50, 0);
  
  printf("\n\ngreenPrism:\n");
  print_matrix(greenPrism);
  draw_lines(greenPrism, s, c);

  
  display(s);
  save_extension(s, "matrix.png");

  free_matrix( redPrism );
  free_matrix( greenPrism );
}  




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"

int main(int argc, char **argv) {

  screen s;
  struct matrix * edges;
  struct matrix * transform;

  edges = new_matrix(4, 4);
  transform = new_matrix(4, 4);

  /* print_matrix(make_rotX(M_PI/4)); */
  /* printf("\n"); */
  /* print_matrix(make_rotY(M_PI/4)); */
  /* printf("\n"); */
  /* print_matrix(make_rotZ(M_PI/4)); */
  /* printf("\n"); */
  
  if ( argc == 2 )
    parse_file( argv[1], transform, edges, s );
  else
    parse_file( "stdin", transform, edges, s );
  

  /* DUMB GIF MAKING VERSION
  int counter = 0;
  int d_theta = 3;
  char fileName[20];
  color c;
  c.red = 255;
  c.green = 255;
  //  c.blue = 255;

  struct matrix * tmp;
  fileName[19] = '\0';
  
  for (; counter <= 360/d_theta; counter++) {
    edges = new_matrix(4, 4);
    if ( argc == 2 )
      parse_file( argv[1], transform, edges, s );
    else
      parse_file( "stdin", transform, edges, s );

    //translate then rotate
    ident(transform);
    clear_screen(s);
    
    tmp = make_translate( -250, 0, 0 );
    matrix_mult(tmp, transform);
    tmp = make_rotY( counter*d_theta * M_PI / 180 );
    //    printf("theta: %f\n", counter*d_theta*M_PI/180);
    matrix_mult(tmp, transform);
    tmp = make_translate( 250, 0, 0 );
    matrix_mult(tmp, transform);
    matrix_mult(transform, edges); //apply

    draw_lines(edges, s, c);
    sprintf(fileName, "anim/anim%d.png", counter);
    save_extension(s, fileName);
    //    printf("finished anim%d\n", counter);
  }
  */
  
  free_matrix( edges );
  free_matrix( transform );
}  

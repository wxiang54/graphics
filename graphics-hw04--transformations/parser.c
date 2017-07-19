#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"


/*======== void parse_file () ==========
Inputs:   char * filename 
          struct matrix * transform, 
          struct matrix * pm,
          screen s
Returns: 

Goes through the file named filename and performs all of the actions listed in that file.
The file follows the following format:
     Every command is a single character that takes up a line
     Any command that requires arguments must have those arguments in the second line.
     The commands are as follows:
         line: add a line to the edge matrix - 
	    takes 6 arguemnts (x0, y0, z0, x1, y1, z1)
	 ident: set the transform matrix to the identity matrix - 
	 scale: create a scale matrix, 
	    then multiply the transform matrix by the scale matrix - 
	    takes 3 arguments (sx, sy, sz)
	 move: create a translation matrix, -
	    then multiply the transform matrix by the translation matrix - 
	    takes 3 arguments (tx, ty, tz)
	 translate: create a translation matrix, 
	    then multiply the transform matrix by the translation matrix - 
	    takes 3 arguments (tx, ty, tz)
	 rotate: create an rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 2 arguments (axis, theta) axis should be x y or z
	 apply: apply the current transformation matrix to the 
	    edge matrix
	 display: draw the lines of the edge matrix to the screen
	    display the screen
	 save: draw the lines of the edge matrix to the screen
	    save the screen to a file -
	    takes 1 argument (file name)
	 quit: end parsing

See the file script for an example of the file format


IMPORTANT MATH NOTE:
the trig functions int math.h use radian mesure, but us normal
humans use degrees, so the file will contain degrees for rotations,
be sure to convert those degrees to radians (M_PI is the constant
for PI)
====================*/
void parse_file ( char * filename, 
                  struct matrix * transform, 
                  struct matrix * edges,
                  screen s) {
  
  FILE *f;
  char line[256];
  char args[256];
  clear_screen(s);

  if ( strcmp(filename, "stdin") == 0 ) 
    f = stdin;
  else
    f = fopen(filename, "r");
  
  while ( fgets(line, 255, f) != NULL ) {
    line[strlen(line)-1]='\0'; //remove trailing whitespace

    if ( strcmp(line, "line") == 0 ) {
      fgets(args, 255, f);
      args[strlen(args)-1]='\0'; //remove trailing whitespace
      char *s = args;
      int argList[6];
      int i;
      for (i = 0; i < 6; i++) {
	argList[i] = strtol(s, &s, 10);
      }
      add_edge(edges, argList[0], argList[1], argList[2], argList[3], argList[4], argList[5]);
    }
    
    else if ( strcmp(line, "ident") == 0 ) {
      ident(transform);
    }
    
    else if ( strcmp(line, "scale") == 0 ) {
      fgets(args, 255, f);
      args[strlen(args)-1]='\0'; //remove trailing whitespace
      char *s = args;
      int argList[3];
      int i;
      for (i = 0; i < 3; i++) {
	argList[i] = strtol(s, &s, 10);
      }
      matrix_mult( make_scale( argList[0], argList[1], argList[2] ) , transform);
    }
    
    else if ( strcmp(line, "move") == 0 ) {
      fgets(args, 255, f);
      args[strlen(args)-1]='\0'; //remove trailing whitespace
      char *s = args;
      int argList[3];
      int i;
      for (i = 0; i < 3; i++) {
	argList[i] = strtol(s, &s, 10);
      }
      matrix_mult( make_translate( argList[0], argList[1], argList[2] ) , transform);
    }
    
    else if ( strcmp(line, "rotate") == 0 ) {
      fgets(args, 255, f);
      args[strlen(args)-1]='\0'; //remove trailing whitespace
      char *s = args + 2;
      double theta = strtod(s, &s);
      if (args[0] == 'x') {
	matrix_mult( make_rotX( theta ), transform);
      }
      else if (args[0] == 'y') {
	matrix_mult( make_rotY( theta ), transform);
      }
      else { //assume z
	matrix_mult( make_rotZ( theta ), transform);
      }
    }
    
    else if ( strcmp(line, "apply") == 0 ) {
      matrix_mult(transform, edges);
    }
    
    else if ( strcmp(line, "display") == 0 ) {
      clear_screen(s);
      color c;
      c.red = 255;
      c.green = 0;
      c.blue = 0;
      draw_lines(edges, s, c);
      display(s);
    }
    
    else if ( strcmp(line, "save") == 0 ) {
      fgets(args, 255, f);
      args[strlen(args)-1]='\0';
      save_extension(s, args);
    }
    
    
    else {
      printf("Not a valid command: ");
    }
    
    printf(":%s:\n",line);
  }
}
  

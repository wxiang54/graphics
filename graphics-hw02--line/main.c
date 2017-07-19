#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

void drawRadial( int start_x, int start_y, int radius, double theta_0, double theta_1, double d_theta, screen s, color c ) {
  //polar to cartesian
  double theta = theta_0; //in rads
  while (theta <= theta_1) {
    int x = start_x + (int)(radius * cos(theta));
    int y = start_y + (int)(radius * sin(theta));
    draw_line(start_x, start_y, x, y, s, c);
    theta += d_theta;
  }
}

void drawRect( int x0, int y0, int x1, int y1, screen s, color c ) {
  if (y1 < y0) {
    y0 = y0^y1;
    y1 = y0^y1;
    y0 = y0^y1;
  }
  int y = y0;
  while (y < y1) {
    draw_line(x0, y, x1, y, s, c);
    y++;
  }
}

int main() {
  screen s;
  color c;
  clear_screen(s);

  /************************
        THE REAL DEMO
  *************************/
  int radius = (int)(XRES/2 * pow(2.0, 0.5));
  double d_theta = M_PI / 96;

  //BLUE Lines from bottom-left corner displays: Oct 1, Oct 2
  c.red = 1;
  c.green = 164;
  c.blue = 239;
  drawRadial( 0, 0, radius, 0, M_PI/2, d_theta, s, c );

  //YELLOW Lines from bottom-right corner displays: Oct 3, Oct 4
  c.red = 255;
  c.green = 185;
  c.blue = 1;
  drawRadial( XRES, 0, radius, M_PI/2, M_PI, d_theta, s, c );

  //GREEN Lines from top-right corner displays: Oct 5, Oct 6
  c.red = 127;
  c.green = 186;
  c.blue = 0;
  drawRadial( XRES, YRES, radius, M_PI, 3*M_PI/2, d_theta, s, c );
  
  //BLUE Lines from top-left corner displays: Oct 7, Oct 8
  c.red = 242;
  c.green = 80;
  c.blue = 34;
  drawRadial( 0, YRES, radius, 3*M_PI/2, 2*M_PI, d_theta, s, c );

  //Lines to demonstrate zero and n/a slope
  c.red = 255;
  c.green = 255;
  c.blue = 255;
  draw_line(0, YRES/2, XRES, YRES/2, s, c);
  draw_line(XRES/2, 0, XRES/2, YRES, s, c);

  
  /* STRAIGHT LINES
  c.red = 255;
  c.green = 255;
  c.blue = 255;
  int radius = (int)(XRES/2 * pow(2.0, 0.5)); //make sure it covers entire screen
  drawRadial( XRES/2, YRES/2, radius, M_PI/12, M_PI - M_PI/12, M_PI/24, s, c );
  drawRadial( XRES/2, YRES/2, radius, M_PI + M_PI/12, 2*M_PI - M_PI/12, M_PI/24, s, c );
  drawRect( 0, YRES/2 + 65, XRES, YRES/2 + 75, s, c );
  drawRect( 0, YRES/2 - 65, XRES, YRES/2 - 75, s, c );
  */

  /*
  // MORE STRAIGHT LINES
  int x0, y0, y1, x;
  c.red = 255;
  c.green = 255;
  c.blue = 255;
  x0 = XRES/2;
  y0 = YRES-100;
  y1 = YRES/2;
  x = -100;
  while (x <= XRES + 100) {
    draw_line(x0, y0, x, y1, s, c);
    x += 25;
  }
  
  x0 = XRES/2;
  y0 = 100;
  y1 = YRES/2;
  x = -100;
  while (x <= XRES + 100) {
    draw_line(x0, y0, x, y1, s, c);
    x += 25;
  }
  drawRect( 0, YRES/2 + 40, XRES, YRES/2 + 47, s, c );
  drawRect( 0, YRES/2 - 40, XRES, YRES/2 - 47, s, c );
  */
   
  display(s);
  save_extension(s, "lines.png");
}  

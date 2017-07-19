#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

/************************************************
Algorithm (assuming octant 1 only):
d is the distance from next midpoint
A = Δy, B = -Δx
2d = 2A + B
if 2d < 0, then below line -> color bottom pixel
if 2d > 0, then above line -> color top pixel
if 2d = 0, then do either -> color bottom pixel
*************************************************/
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  if (x0 > x1) { //octant 3-6 => SWAP start/end points
    //swap x
    x0 = x0^x1;
    x1 = x0^x1;
    x0 = x0^x1;

    //swap y
    y0 = y0^y1;
    y1 = y0^y1;
    y0 = y0^y1;
  }

  int A = y1 - y0; // ∆y
  int B = x0 - x1; // -∆x
  int x = x0;
  int y = y0;
  
  if (A > 0) { //y1 > y0
    if (-B > A) { //OCTANT 1
      //Midpoint: (x+1, y+1/2)
      int D = 2*A + B;
      while (x < x1) {
	plot(s, c, x, y);
	if (D > 0) { //y too low => color top pix
	  y++;
	  D += 2 * B;
	}
	x++;
	D += 2 * A;
      }
    }
    else { //OCTANT 2
      //Midpoint: (x0 + 1/2, y0 + 1)
      int D = A + 2*B;
      while (y < y1) {
	plot(s, c, x, y);
	if (D < 0) { //x too low => color right pix
	  x++;
	  D += 2 * A;
	}
	y++;
	D += 2 * B;
      }
    }
  }

  else { //y1 < y0
    if (B < A) { //OCTANT 8
      //Midpoint: (x+1, y-1/2)
      //A becomes negative, B still negative but subtracting
      int D = 2*A - B;
      while (x < x1) {
	plot(s, c, x, y);
	if (D < 0) { //y too low => color top pix
	  y--;
	  D -= 2 * B;
	}
	x++;
	D += 2 * A;
      }
    }
    else { //OCTANT 7
      //Midpoint: (x0 + 1/2, y0 - 1)
      //A becomes negative, B still negative but subtracting
      int D = A - 2*B;
      while (y > y1) {
	plot(s, c, x, y);
	if (D > 0) { //too little x => color right pix
	  x++;
	  D += 2 * A;
	}
	y--;
	D -= 2 * B;
      }
    }
  }
}

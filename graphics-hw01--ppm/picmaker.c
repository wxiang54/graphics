
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>



//rgb_init and rgb_final are arrays of 3 ints representing RGBs
//xy_init and xy_final are arrays of 2 ints representing xy coords
void addVerticalGradient( char ** pic, int max_width, int xy_init[2], int xy_final[2], int rgb_init[3], int rgb_final[3] ) {
  int row, col, r, g, b;
  int height = abs(xy_final[1] - xy_init[1]);
  int width = abs(xy_final[0] - xy_init[0]);
  int len_pixel_max = 4; //3 #s max for RGB + space
  int len_line = max_width * 3 * len_pixel_max; //length of one line
  
  char buf[len_line];
  for (row = xy_init[1]; row < xy_final[1]; row++) {
    for (col = xy_init[0]; col < xy_final[0]; col++) {
      r = ((row - xy_init[1]) * (rgb_final[0] - rgb_init[0]) / height) + rgb_init[0];
      g = ((row - xy_init[1]) * (rgb_final[1] - rgb_init[1]) / height) + rgb_init[1];
      b = ((row - xy_init[1]) * (rgb_final[2] - rgb_init[2]) / height) + rgb_init[2];
      snprintf(buf, sizeof(buf), "%03d %03d %03d ", r, g, b);

      int pixelPosToReplace = (row * len_line) + (col * 3 * len_pixel_max);
      strncpy( *pic + pixelPosToReplace, buf, strlen(buf) );
    }
    //    printf("row %d rgb: [%d %d %d]\n", row, r, g, b);
  }
}



//change xy coord sets to top right half, and return area
int halvePartition( int xy_init[2], int xy_final[2] ) {
  int height = abs(xy_final[1] - xy_init[1]);
  int width = abs(xy_final[0] - xy_init[0]);
  
  if (height >= width) { //if taller than wide, cut horizontally
    height /= 2;
    xy_final[1] -= height; //move bound up
  } else { //wider than tall
    width /= 2;
    xy_init[0] += width; //move bound left
  }
  
  return height * width;
}



//resize partition from all sides, and return area
int padPartition( int xy_init[2], int xy_final[2], int padding ) {
  xy_init[0] += padding;
  xy_init[1] += padding;
  xy_final[0] -= padding;
  xy_final[1] -= padding;
  return (xy_final[1] - xy_init[1]) * (xy_final[0] - xy_init[0]);
}



void genRandomRGB ( int rgb[3] ) {
  int fd_urandom = open("/dev/urandom", O_RDONLY, 0644);
  int i;
  for (i = 0; i < 3; i++) {
    read( fd_urandom, &(rgb[i]), sizeof(int) );
    rgb[i] = abs(rgb[i]) % 256;
  }
  close(fd_urandom);
}



int main() {
  int height = 500;
  int width = 500;
  
  char line[100];
  int fd_pic = open("pic.ppm", O_CREAT | O_WRONLY | O_TRUNC, 0644);
  snprintf(line, sizeof(line), "P3 %d %d 255\n", width, height);
  write(fd_pic, line, strlen(line));

  char * buf = (char *) malloc(height * width * 12 + 1); //12 bc "RGB " x 3 = 12 chars
  buf[height * width * 9] = '\0'; //term null
  char ** pic = &buf;

  int xy_init[2] = {0, 0};
  int xy_final[2] = {width, height};
  int rgb_init[3];
  int rgb_final[3];

  while (1) {
    genRandomRGB(rgb_init);
    genRandomRGB(rgb_final);
    addVerticalGradient(pic, width, xy_init, xy_final, rgb_init, rgb_final);
    
    // PATTERN 1: "infinitesimal" (uncomment the next line)
    //    if ( halvePartition(xy_init, xy_final) <= 1 ) break; //no gradient possible w/ 1 pix

    // PATTERN 2: "1:29 AM"
    if ( padPartition(xy_init, xy_final, 25) <= 1 ) break; //no gradient possible w/ 1 pix
  }

  
  write(fd_pic, *pic, strlen(*pic));  
  close(fd_pic);
}

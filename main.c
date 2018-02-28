#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {
  printf("Creating [matrix]... \n");
  struct matrix *matrix;
  matrix = new_matrix(4,4);

  printf("\nAdding points to [matrix]... \n");
  add_point(matrix, 0.0,0.0,0.0);
  add_point(matrix, 10.0,0.0,0.0);
  add_point(matrix, 10.0,10.0,0.0);
  add_point(matrix, 0.0,10.0,0.0);

  printf("\nPrinting [matrix]... \n");
  print_matrix(matrix);

  printf("\nTurning [matrix] into identity matrix... \n");
  ident(matrix);

  printf("\nPrinting [matrix]... \n");
  print_matrix(matrix);

  printf("\nCreating [mult]... \n");
  struct matrix *mult;
  mult = new_matrix(4,1);

  printf("\nAdding points to [mult]... \n");
  add_point(mult, 1.0, 2.0, 3.0);

  printf("\nPrinting [mult]... \n");
  print_matrix(mult);

  printf("\nCreating [edges]... \n");
  struct matrix *edges;
  edges = new_matrix(4, 4);


  printf("\nAdding edges to [edges]... \n");
  add_edge(edges, 100.0,100.0,0.0,50.0,100.0,0.0);
  add_edge(edges, 100.0,50.0,0.0,50.0,50.0,0.0);

  printf("\nPrinting [edges]... \n");
  print_matrix(edges);

  printf("\nMultiplying [edges] and [mult]... \n");
  matrix_mult(edges, mult);

  printf("\nPrinting [mult]... \n");
  print_matrix(mult);

  printf("\nMultiplying [matrix] and [mult]... \n");
  matrix_mult(matrix, mult);

  printf("\nPrinting [mult]... \n");
  print_matrix(mult);

  printf("\nGenerating an image... \n");

  screen s;
  clear_screen(s);

  //white
  color c;
  c.red = 255;
  c.green = 255;
  c.blue = 255;

  //grid
  struct matrix * grid = new_matrix(12,12);

  //x
  for (int i = 0; i < 500; i+=50) {
    add_edge(grid,0.0,i,0.0,500.0,i,0.0);
  }

  //y
  for (int i = 0; i < 500; i+=50) {
    add_edge(grid,i,0.0,0.0,i,500.0,0.0);
  }

  //top cat eye
  for (int i = 500; i > 0; i-=1.0) {
    add_edge(grid,0.0,i,0.0,i,500.0,0.0);
  }

  //bottom cat eye
  for (int i = 0; i < 500; i+=1.0) {
    add_edge(grid,i,0.0,0.0,500.0,i,0.0);
  }

  draw_lines(grid, s, c);

  save_extension(s, "image.jpg");

  display(s);

  free_matrix(edges);
  free_matrix(mult);
  free_matrix(matrix);
  free_matrix(grid);
}

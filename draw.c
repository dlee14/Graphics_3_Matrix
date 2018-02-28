#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
int x
int y
int z
Returns:
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
	if (points->lastcol == points->cols - 1) {
		grow_matrix(points, points->cols + 20);
	}
	points->m[0][points->lastcol] = x;
	points->m[1][points->lastcol] = y;
	points->m[2][points->lastcol] = z;
	points->m[3][points->lastcol] = 1;
	points->lastcol ++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
int x0, int y0, int z0, int x1, int y1, int z1
Returns:
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, double x0, double y0, double z0, double x1, double y1, double z1) {
	add_point(points, x0, y0, z0);
	add_point(points, x1, y1, z1);
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
screen s
color c
Returns:
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
	for (int i = 0; i < points->lastcol; i += 2) {
	    draw_line(points->m[0][i], points->m[1][i],
		      points->m[0][i + 1], points->m[1][i + 1], s, c);
	  }
}

void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
	int x, y, A, B, d;

	if (x0 > x1) { //switch order of points
		draw_line(x1, y1, x0, y0, s, c);
	}
	x = x0;
	y = y0;
	B = -1 * (x1 - x);
	A = y1 - y;
	d = 2 * A + B;

	// Octant I & V
	if (A >= 0 && (-1 * B) >= A) {
		while (x <= x1) {
			plot(s, c, x, y);
			if (d > 0) {
				y ++;
				d += (2 * B);
			}
			x ++;
			d += (2 * A);
		}
	}

	// Octant II & VI
	else if (A >= 0 && (-1 * B) <= A) {
		while (y <= y1) {
			plot(s, c, x, y);
			if (d < 0) {
				x ++;
				d += (2 * A);
			}
			y ++;
			d += (2 * B);
		}
	}

	// Octant III & VII
	else if (A < 0 && B >= A) {
		while (y >= y1) {
			plot(s, c, x, y);
			if (d < 0) {
				x ++;
				d -= (2 * A);
			}
			y --;
			d += (2 * B);
		}
	}

	// Octant IV & VIII
	else if (A < 0 && B <= A) {
		while (x <= x1) {
			plot(s, c, x, y);
			if (d > 0) {
				y --;
				d += (2 * B);
			}
			x ++;
			d -= (2 * A);
		}
	}


} //end draw_line

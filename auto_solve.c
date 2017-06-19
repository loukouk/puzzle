#include "auto_solve.h"

int move_x_y(struct grid_info *puzzle, int x, int y)
{
	if (x > 0)
		for ( ; x > 0; x--) { 
			if (move_left(puzzle))
				return 1;
	}
	else
		for ( ; x < 0; x++) {
			if (move_right(puzzle))
				return 1;
	}
	

	if (y < 0)
		for ( ; y < 0; y++) { 
			if (move_down(puzzle))
				return 1;
	}
	else
		for ( ; y > 0; y--) { 
			if (move_up(puzzle))
				return 1;
	}

	return 0;
}

int move_tile_down(struct grid_info *puzzle, int xsrc, int ysrc)
{
	int x, y;

	if (ysrc == 0)
		return 1;

	if (puzzle->xpos == puzzle->szx-1)
		move_right(puzzle);
	if (puzzle->ypos == puzzle->szy-1)
		move_down(puzzle);

	x = xsrc - puzzle->xpos;
	y = ysrc-1 - puzzle->ypos;

	if (x == 0 && y < -1) {
		if (move_right(puzzle)) {
			move_left(puzzle);
			x--;
		}
		else
			x++;
	}
	
	move_x_y(puzzle, x, y);
	move_up(puzzle);
	return 0;
}

int move_tile_up(struct grid_info *puzzle, int xsrc, int ysrc)
{
	int x, y;

	if (ysrc == puzzle->szy-1)
		return 1;

	if (puzzle->xpos == puzzle->szx-1)
		move_right(puzzle);
	if (puzzle->ypos == puzzle->szy-1)
		move_down(puzzle);

	x = xsrc - puzzle->xpos;
	y = ysrc+1 - puzzle->ypos;

	if (x == 0 && y > 1) {
		if (move_right(puzzle)) {
			move_left(puzzle);
			x--;
		}
		else
			x++;
	}

	move_x_y(puzzle, x, y);
	move_down(puzzle);
	return 0;
}

int move_tile_right(struct grid_info *puzzle, int xsrc, int ysrc)
{
	int x, y;

	if (xsrc == 0)
		return 1;

	if (puzzle->xpos == puzzle->szx-1)
		move_right(puzzle);
	if (puzzle->ypos == puzzle->szy-1)
		move_down(puzzle);

	x = xsrc-1 - puzzle->xpos;
	y = ysrc - puzzle->ypos;

	if (y == 0 && x < -1) {
		if (move_down(puzzle)) {
			move_up(puzzle);
			y--;
		}
		else
			y++;
	}

	move_x_y(puzzle, x, y);
	move_left(puzzle);
	return 0;
}

int move_tile_left(struct grid_info *puzzle, int xsrc, int ysrc)
{
	int x, y;

	if (xsrc == puzzle->szx-1)
		return 1;

	if (puzzle->xpos == puzzle->szx-1)
		move_right(puzzle);
	if (puzzle->ypos == puzzle->szy-1)
		move_down(puzzle);

	x = xsrc+1 - puzzle->xpos;
	y = ysrc - puzzle->ypos;

	if (y == 0 && x > 1) {
		if (move_down(puzzle)) {
			move_up(puzzle);
			y--;
		}
		else
			y++;
	}

	move_x_y(puzzle, x, y);
	move_right(puzzle);
	return 0;
}

void move_tile_src_dst(struct grid_info *puzzle, int xsrc, int ysrc, int xdst, int ydst)
{
	int x = xdst-xsrc, y = ydst-ysrc;

	if (y < 0 && x > 0) {
		for ( ; y < 0; y++) { move_tile_down(puzzle, xsrc, ysrc); }
		for ( ; x > 0; x--) { move_tile_left(puzzle, xsrc, ysrc); }
	}
	else if (x < 0) {
		for ( ; x < 0; x++) { move_tile_right(puzzle, xsrc, ysrc); }
		if (y < 0)
			for ( ; y < 0; y++) { move_tile_down(puzzle, xsrc, ysrc); }
		else
			for ( ; y > 0; y--) { move_tile_up(puzzle, xsrc, ysrc); }
	}
	else {
		for ( ; y > 0; y--) { move_tile_up(puzzle, xsrc, ysrc); }
		for ( ; x > 0; x--) { move_tile_left(puzzle, xsrc, ysrc); }
	}	
		

}

/*
 * Function: auto_solve_3x3
 * ------------------------
 *
 * AI that will solve the puzzle by itself.
 * This function is only meant to solve 3x3 puzzles.
 * It is a stepping stone to implementing auto_solve().
 *
 * puzzle: Pointer to structure containing puzzle to be solved.
 */
void auto_solve_3x3(struct grid_info *puzzle)
{
	struct search_info *search;
	int val, a=-1, b=-1, c =-1;

	while(a != 0 || b !=0 || c!= 0) {
	val = 7;
	search = init_search(&val, 1);
	apply_search(puzzle, search);
	move_tile_src_dst(puzzle, search->x[0], search->y[0], 2, 2);

	val = 6;
	search = init_search(&val, 1);
	apply_search(puzzle, search);
	move_tile_src_dst(puzzle, search->x[0], search->y[0], 1, 2);

	val = 8;
	search = init_search(&val, 1);
	apply_search(puzzle, search);
	move_tile_src_dst(puzzle, search->x[0], search->y[0], 2, 1);

	printf("Checking tiles: %d %d %d\n",
	a = check_tile(puzzle, 7, 2, 2),
	b = check_tile(puzzle, 6, 1, 2),
	c = check_tile(puzzle, 8, 2, 1));
	}
//	while (!move_right(puzzle)) {}
//	while (!move_up(puzzle)) {}
//	while (!move_left(puzzle)) {}
//	while (!move_down(puzzle)) {}
}

/*
 * Function: auto_solve
 * --------------------
 *
 * Will eventually solve any puzzle that is passed in to the function
 * reguardless of the size of the grid. Ideally, this will also work
 * with non-square grids. For now, it only calls auto_solve_3x3().
 *
 * puzzle: Pointer to structure containing puzzle to be solved.
 */
void auto_solve(struct grid_info *puzzle)
{
	if (puzzle->szx != 3 || puzzle->szy != 3) {
		printf("AI solve for grid different than 3x3 not yet supported\n");
		exit(EXIT_FAILURE);
	}

	auto_solve_3x3(puzzle);
}


// OLD
/*
int move_tile_down(struct grid_info *puzzle, int xsrc, int ysrc)
{
	

	if (puzzle->xpos == xsrc)
		if (move_right(puzzle))
			move_left(puzzle);

	while (puzzle->ypos != ysrc-1) {
		if (puzzle->ypos < ysrc-1)
			move_up(puzzle);
		else
			move_down(puzzle);
	}

	while (puzzle->xpos != xsrc) {
		if (puzzle->xpos < (xsrc))
			move_left(puzzle);
		else
			move_right(puzzle);
	}

	move_up(puzzle);
	return 0;
}

int move_tile_up(struct grid_info *puzzle, int xsrc, int ysrc)
{
	if (puzzle->xpos == xsrc)
		if (move_right(puzzle))
			move_left(puzzle);

	while (puzzle->ypos != ysrc+1) {
		if (puzzle->ypos < ysrc+1)
			move_up(puzzle);
		else
			move_down(puzzle);
	}

	while (puzzle->xpos != (xsrc)) {
		if (puzzle->xpos < (xsrc))
			move_left(puzzle);
		else
			move_right(puzzle);
	}

	move_down(puzzle);
	return 0;
}

int move_tile_right(struct grid_info *puzzle, int xsrc, int ysrc)
{
	if (puzzle->ypos == ysrc)
		if (move_down(puzzle))
			move_up(puzzle);

	while (puzzle->xpos != (xsrc)-1) {
		if (puzzle->xpos < (xsrc)-1)
			move_left(puzzle);
		else
			move_right(puzzle);
	}

	while (puzzle->ypos != (ysrc)) {
		if (puzzle->ypos < (ysrc))
			move_up(puzzle);
		else
			move_down(puzzle);
	}

	move_left(puzzle);
	return 0;
}

int move_tile_left(struct grid_info *puzzle, int xsrc, int ysrc)
{
	if (puzzle->ypos == ysrc)
		if (move_down(puzzle))
			move_up(puzzle);

	while (puzzle->xpos != xsrc+1) {
		if (puzzle->xpos < xsrc+1)
			move_left(puzzle);
		else
			move_right(puzzle);
	}

	while (puzzle->ypos != ysrc) {
		if (puzzle->ypos < ysrc)
			move_up(puzzle);
		else
			move_down(puzzle);
	}

	move_right(puzzle);
	return 0;
}

void move_tile_src_dst(struct grid_info *puzzle, int xsrc, int ysrc, int xdst, int ydst)
{
	while (xsrc != xdst) {
		if (xsrc > xdst) {
			if (!move_tile_right(puzzle, xsrc, ysrc))
				xsrc--;
		}
		else {
			if (!move_tile_left(puzzle, xsrc, ysrc))
				xsrc++;
		}
	}

	while (ysrc != ydst) {
		if (ysrc > ydst) {
			if (!move_tile_down(puzzle, xsrc, ysrc))
				ysrc--;
		}
		else {
			if (!move_tile_up(puzzle, xsrc, ysrc))
				ysrc++;
		}
	}
}
*/

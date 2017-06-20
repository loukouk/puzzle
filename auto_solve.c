#include "auto_solve.h"

/*
 * Function: move_x_y
 * ------------------
 * 
 * Moves the hole first in the x direction for a number
 * of moves and the in the y direction for a number of moves.
 * The x and y values determine how many moves are to be done
 * and which direction they are in.
 *
 * puzzle: Pointer to structure containing puzzle to be solved.
 * x: number of moves to be made in x direction.
 *    + is left direction, - is right
 * y: number of moves to be made in y direction.
 *    + is up, - is down
 *
 * returns 1 if any moves fail, and 0 success
 */
int move_x_y(struct grid_info *puzzle, int x, int y)
{
	printf("Entering move_x_y: x=%d y=%d\n", x, y);
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

/*
 * Function: move_y_x
 * ------------------
 * 
 * Moves the hole first in the y direction for a number
 * of moves and the in the x direction for a number of moves.
 * The y and x values determine how many moves are to be done
 * and which direction they are in.
 *
 * puzzle: Pointer to structure containing puzzle to be solved.
 * y: number of moves to be made in y direction.
 *    + is up, - is down
 * x: number of moves to be made in x direction.
 *    + is left direction, - is right
 *
 * returns 1 if any moves fail, and 0 on success
 */
int move_y_x(struct grid_info *puzzle, int y, int x)
{
	printf("Entering move_y_x: y=%d x=%d\n", y, x);

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
	
	return 0;
}

/*
 * Function: move_tile_down
 * ------------------------
 *
 * "Moves" a tile down. This is achieved by moving the
 * hole below the tile using a series of moves, and
 * the calling the move_up() function.
 *
 * puzzle: Pointer to structure containing puzzle to be solved.
 * xsrc: original x position of the tile to be moved
 * ysrc: original x postiion of the tile to be moved
 *
 * returns 1 if the tile cannot be moved, 0 on success
 */
int move_tile_down(struct grid_info *puzzle, int xsrc, int ysrc)
{
	int x, y;

	if (ysrc == 0)
		return 1;

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
	
	if (x > 1) {
		move_y_x(puzzle, 0, x-1);
		move_y_x(puzzle, y, 1);
	}
	else if (x < -1) {
		move_y_x(puzzle, 0, x+1);
		move_y_x(puzzle, y, -1);
	}
	else
		move_y_x(puzzle, y, x);

	move_up(puzzle);
	return 0;
}

/*
 * Function: move_tile_up
 * ----------------------
 *
 * "Moves" a tile up. This is achieved by moving the
 * hole above the tile using a series of moves, and
 * the calling the move_down() function.
 *
 * puzzle: Pointer to structure containing puzzle to be solved.
 * xsrc: original x position of the tile to be moved
 * ysrc: original x postiion of the tile to be moved
 *
 * returns 1 if the tile cannot be moved, 0 on success
 */
int move_tile_up(struct grid_info *puzzle, int xsrc, int ysrc)
{
	int x, y;

	if (ysrc == puzzle->szy-1)
		return 1;

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

	if (x > 1) {
		move_y_x(puzzle, 0, x-1);
		move_y_x(puzzle, y, 1);
	}
	else if (x < -1) {
		move_y_x(puzzle, 0, x+1);
		move_y_x(puzzle, y, -1);
	}
	else
		move_y_x(puzzle, y, x);

	move_down(puzzle);
	return 0;
} 

/*
 * Function: move_tile_right
 * -------------------------
 *
 * "Moves" a tile to the right. This is achieved by moving the
 * hole to the right of the tile using a series of moves, and
 * the calling the move_left() function.
 *
 * puzzle: Pointer to structure containing puzzle to be solved.
 * xsrc: original x position of the tile to be moved
 * ysrc: original x postiion of the tile to be moved
 *
 * returns 1 if the tile cannot be moved, 0 on success
 */
int move_tile_right(struct grid_info *puzzle, int xsrc, int ysrc)
{
	int x, y;

	if (xsrc == 0)
		return 1;

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

	if (y > 1) {
		move_x_y(puzzle, 0, y-1);
		move_x_y(puzzle, x, 1);
	}
	else if (y < -1){
		move_x_y(puzzle, 0, y+1);
		move_x_y(puzzle, x, -1);
	}
	else
		move_x_y(puzzle, x, y);

	move_left(puzzle);
	return 0;
}

/*
 * Function: move_tile_left
 * ------------------------
 *
 * "Moves" a tile to the left. This is achieved by moving the
 * hole to the left of the tile using a series of moves, and
 * the calling the move_right() function.
 *
 * puzzle: Pointer to structure containing puzzle to be solved.
 * xsrc: original x position of the tile to be moved
 * ysrc: original x postiion of the tile to be moved
 *
 * returns 1 if the tile cannot be moved, 0 on success
 */
int move_tile_left(struct grid_info *puzzle, int xsrc, int ysrc)
{
	int x, y;

	if (xsrc == puzzle->szx-1)
		return 1;

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

	if (y > 1) {
		move_x_y(puzzle, 0, y-1);
		move_x_y(puzzle, x, 1);
	}
	else if (y < -1){
		move_x_y(puzzle, 0, y+1);
		move_x_y(puzzle, x, -1);
	}
	else
		move_x_y(puzzle, x, y);

	move_right(puzzle);
	return 0;
}

/*
 * Function: move_tile_src_dst
 * ---------------------------
 * 
 * This function is an abstraction. It takes the tile at
 * location (xsrc, ysrc) and "moves" it to location (xdst, ydst).
 * In reality, it takes many moves to achieve that result.
 *
 * puzzle: Pointer to structure containing puzzle to be solved.
 * xsrc: original x position of tile to be moved
 * ysrc: original y position of tile to be moved
 * xdst: destination x postion of the tile
 * ydst: destination y postion of the tile
 *
 * returns 1 if the coordinates are out of bounds, 0 on success
 */
int move_tile_src_dst(struct grid_info *puzzle, int xsrc, int ysrc, int xdst, int ydst)
{
	int x = xdst-xsrc, y = ydst-ysrc;

	if (xsrc > puzzle->szx-1 || xsrc < 0)
		return 1;
	if (xdst > puzzle->szx-1 || xdst < 0)
		return 1;
	if (ysrc > puzzle->szy-1 || ysrc < 0)
		return 1;
	if (ydst > puzzle->szy-1 || ydst < 0)
		return 1;

	if (y < 0 && x > 0) {
		for ( ; y < 0; y++) { 
			if (!move_tile_down(puzzle, xsrc, ysrc))
				ysrc--;
		}
		for ( ; x > 0; x--) {
			if (!move_tile_left(puzzle, xsrc, ysrc))
				xsrc++;
		}
	}
	else if (x < 0) {
		for ( ; x < 0; x++) {
			if (!move_tile_right(puzzle, xsrc, ysrc))
				xsrc--;
		}
		if (y < 0)
			for ( ; y < 0; y++) {
				if (!move_tile_down(puzzle, xsrc, ysrc))
					ysrc--;
		}
		else
			for ( ; y > 0; y--) {
				if (!move_tile_up(puzzle, xsrc, ysrc))
					ysrc++;
		}
	}
	else {
		for ( ; y > 0; y--) {
			if (!move_tile_up(puzzle, xsrc, ysrc))
				ysrc++;
		}
		for ( ; x > 0; x--) {
			if (!move_tile_left(puzzle, xsrc, ysrc))
				xsrc++;
		}
	}	
		
	puzzle->xprev = xdst;
	puzzle->yprev = ydst;
	return 0;
}

/*
 * Function: fix_algorithm
 * -----------------------
 *
 * This function fixes the following board state automoatically
 * 		8	6	7
 * 		x	x	0
 * 		x	x	x
 * such that the top three numbers are in descending order.
 * This is useful because the method I coded cannot handle
 * this particular case.
 *
 * puzzle: Pointer to structure containing puzzle to modify.
 *
 * returns 1 if any moves fail, 0 on success
 */
int fix_algorithm(struct grid_info *puzzle)
{
	int ret = 0;
	printf("fix alg\n");

	move_x_y(puzzle, 0-(puzzle->xpos), 1-(puzzle->ypos));

	ret |= move_up(puzzle);
	ret |= move_left(puzzle);
	ret |= move_down(puzzle);
	ret |= move_right(puzzle);
	ret |= move_down(puzzle);
	ret |= move_left(puzzle);
	ret |= move_left(puzzle);
	ret |= move_up(puzzle);
	ret |= move_right(puzzle);
	ret |= move_up(puzzle);
	ret |= move_right(puzzle);
	ret |= move_down(puzzle);
	ret |= move_left(puzzle);
	ret |= move_left(puzzle);
	ret |= move_down(puzzle);
	ret |= move_right(puzzle);
	ret |= move_right(puzzle);
	ret |= move_up(puzzle);
	ret |= move_up(puzzle);
	ret |= move_left(puzzle);
	ret |= move_down(puzzle);

	return ret;
}


int solve_top_row(struct grid_info *puzzle)
{
	struct search_info *search;
	int val, a=-1, b=-1, c =-1;

	val = 8;
	search = init_search(&val, 1);
	apply_search(puzzle, search);
	move_tile_src_dst(puzzle, search->x[0], search->y[0], 2, 2);

	printf("Done 8\n");

	val = 7;
	search = init_search(&val, 1);
	apply_search(puzzle, search);
	move_tile_src_dst(puzzle, search->x[0], search->y[0], 0, 2);

	printf("Done 7\n");

	printf("Checking pos (1,2)\n");
	if (puzzle->xpos == 1 && puzzle->ypos == 2)
		move_down(puzzle);

	val = 6;
	search = init_search(&val, 1);
	apply_search(puzzle, search);
	printf("Checking for alg req\n");

	if (search->x[0] == 1 && search->y[0] == 2)
		fix_algorithm(puzzle);
	else {
		move_tile_src_dst(puzzle, search->x[0], search->y[0], 0, 1);

		printf("Done 6\n");

		move_x_y(puzzle, 1-(puzzle->xpos), 2-(puzzle->ypos));
		move_right(puzzle);
		move_down(puzzle);
	}

	printf("Checking tiles: %d %d %d\n",
	a = check_tile(puzzle, 8, 2, 2),
	b = check_tile(puzzle, 7, 1, 2),
	c = check_tile(puzzle, 6, 0, 2));

	if (!a && !b && !c)
		return 0;
	else
		return 1;

}

int solve_final(struct grid_info *puzzle)
{
	if (puzzle->szy != 2 || puzzle->szx != 2)
		return 1;

	int cnt = 0;

	move_x_y(puzzle, 0-(puzzle->xpos), 0-(puzzle->ypos));

	while (!is_win(puzzle)) {
		move_up(puzzle);
		move_left(puzzle);
		move_down(puzzle);
		move_right(puzzle);
		cnt++;
		if (cnt >= 4)
			return 1;
	}
	return 0;
}

int solve_left_col(struct grid_info *puzzle)
{
	struct search_info *search;
	int vals[2] = {5, 2};

	search = init_search(vals, 2);
	apply_search(puzzle, search);

	move_tile_src_dst(puzzle, search->x[1], search->y[1], 2, 1);
	printf("Done 5\n");


	if (puzzle->xpos == 2 && puzzle->ypos == 0)
		move_right(puzzle);

	apply_search(puzzle, search);

	if (search->x[0] == 2 && search->y[0] == 0)
		printf("second alg\n");
	else {
		move_tile_src_dst(puzzle, search->x[0], search->y[0], 1, 1);

		printf("Done 2\n");

		move_y_x(puzzle, 2-(puzzle->xpos), 0-(puzzle->ypos));
		move_up(puzzle);
		move_right(puzzle);
	}

	if (check_tile(puzzle, 5, 2, 1) || check_tile(puzzle, 2, 2, 0))
		return 1;

	return 0;
}

/*
 * Function: auto_solve
 * --------------------
 *
 * Will eventually solve any puzzle that is passed in to the function
 * reguardless of the size of the grid. Ideally, this will also work
 * with non-square grids.
 *
 * puzzle: Pointer to structure containing puzzle to be solved.
 *
 * returns 0 if solved and 1 if the program failed to solve the puzzle
 */
int auto_solve(struct grid_info *puzzle)
{
	if (puzzle->szx != 3 || puzzle->szy != 3) {
		printf("AI solve for grid different than 3x3 not yet supported\n");
		exit(EXIT_FAILURE);
	}

	int szx, szy, ret;
	szx = puzzle->szx;
	szy = puzzle->szy;

	while (puzzle->szy > 2) {
		if (solve_top_row(puzzle))
			return 1;

		puzzle->szy--;
	}

	while (puzzle->szx > 3) {
		if (solve_left_col(puzzle))
			return 1;

		puzzle->szx--;
	}

	ret = solve_final(puzzle);
	puzzle->szx = szx;
	puzzle->szy = szy;
	return ret;
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

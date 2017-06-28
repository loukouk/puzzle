#include "auto_solve.h"


/*
 * Function: move_auto
 * -------------------
 * 
 * Moves the hole by a number of tiles specified by the x and y
 * values. This function prioritizes movement in the following
 * ways: DOWN, RIGHT, LEFT, UP
 *
 * puzzle: Pointer to structure containing puzzle to be solved.
 * x: number of moves to be made in x direction.
 *    + is left direction, - is right
 * y: number of moves to be made in y direction.
 *    + is up, - is down
 *
 * returns 1 if any moves fail, and 0 success
 */
int move_auto(struct grid_info *puzzle, int x, int y)
{
	#if PUZZLE_PRINT_DEBUG==1
	printf("Entering move_auto: x=%d y=%d\n", x, y);
	#endif

/* DOES NOT WORK
	// Check if the hole is going to move through already solved tiles
	if (puzzle->num_solved >= (puzzle->szx)-(puzzle->xpos) && puzzle->szy-1 == puzzle->ypos + y) {
		move_down(puzzle);
		move_right(puzzle);
		move_right(puzzle);
	}
*/

	if (y <= 0) {
		for ( ; y < 0; y++) { 
			if (move_down(puzzle))
				return 1;
		}
	}

	if (x <= 0) {
		for ( ; x < 0; x++) {
			if (move_right(puzzle))
				return 1;
		}
	}
	else {
		for ( ; x > 0; x--) { 
			if (move_left(puzzle))
				return 1;
		}
	}
	

	if (y > 0) {
		for ( ; y > 0; y--) { 
			if (move_up(puzzle))
				return 1;
		}
	}

	return 0;
}

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
	#if PUZZLE_PRINT_DEBUG==1
	printf("Entering move_x_y: x=%d y=%d\n", x, y);
	#endif

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
	#if PUZZLE_PRINT_DEBUG == 1
	printf("Entering move_y_x: y=%d x=%d\n", y, x);
	#endif

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

	if (x == 0 && y == -1)
		return 1;

	if (y < -1 && x == 0) {
		move_y_x(puzzle, y+2, 0);
		if (move_right(puzzle)) {
			move_left(puzzle);
			x--;
		}
		else
			x++;
		move_y_x(puzzle, 2, x);
	}
	else if (y < 0 && x > 0) {
		move_auto(puzzle, x-1, y);
		move_left(puzzle);
	}
	else if (y < 0 && x < 0) {
		move_auto(puzzle, x+1, y);
		move_right(puzzle);
	}
	else
		move_auto(puzzle, x, y);


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

	if (x == 0 && y == 1)
		return 1;

	//TODO insert fix here for:
	//	o	dst	x	x
	//	(0,0)	src	x	x
	//	x	x	x	x

	if (y > 1 && x == 0) {
		move_y_x(puzzle, y-2, 0);
		if (move_right(puzzle)) {
			move_left(puzzle);
			x--;
		}
		else
			x++;
		move_y_x(puzzle, 2, x);
	}
	else if (y > 0 && x > 0) {
		move_auto(puzzle, x-1, y);
		move_left(puzzle);
	}
	else if (y > 0 && x < 0) {
		move_auto(puzzle, x+1, y);
		move_right(puzzle);
	}
	else
		move_auto(puzzle, x, y);


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

	if (x == -1 && y == 0)
		return 1;

	if (x < -1 && y == 0) {
		move_x_y(puzzle, x+2, 0);
		if (move_down(puzzle)) {
			move_up(puzzle);
			y--;
		}
		else
			y++;
		move_x_y(puzzle, -2, y);
	}
	else if (x < 0 && y > 0) {
		move_auto(puzzle, x, y-1);
		move_up(puzzle);
	}
	else if (x < 0 && y < 0) {
		move_auto(puzzle, x, y+1);
		move_down(puzzle);
	}
	else
		move_auto(puzzle, x, y);


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

	if (x == 1 && y == 0)
		return 1;

	if (x > 1 && y == 0) {
		move_x_y(puzzle, x-2, 0);
		if (move_down(puzzle)) {
			move_up(puzzle);
			y--;
		}
		else
			y++;
		move_x_y(puzzle, 2, y);
	}
	else if (x > 0 && y > 0) {
		move_auto(puzzle, x, y-1);
		move_up(puzzle);
	}
	else if (x > 0 && y < 0) {
		move_auto(puzzle, x, y+1);
		move_down(puzzle);
	}
	else
		move_auto(puzzle, x, y);


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
		
	return 0;
}

/*
 * Function: fix_algorithm1
 * ------------------------
 *
 * This function fixes the following board state automoatically
 * 		(2,2)	(0,2)	(1,2)
 * 		x	x	0
 * 		x	x	x
 * This is useful because the method I coded cannot handle
 * this particular case.
 *
 * puzzle: Pointer to structure containing puzzle to modify.
 *
 * returns 1 if any moves fail, 0 on success
 */
int fix_algorithm1(struct grid_info *puzzle)
{
	int ret = 0;
	#if PUZZLE_PRINT_DEBUG == 1
	printf("fix alg1\n");
	#endif

	move_x_y(puzzle, 0-(puzzle->xpos), (puzzle->szy-2)-(puzzle->ypos));

	if (puzzle->szy >= 2 && puzzle->szx >= 3) {
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
	}
	else if (puzzle->szy >= 3 && puzzle->szx >= 2) {
		ret |= move_up(puzzle);
		ret |= move_left(puzzle);
		ret |= move_down(puzzle);
		ret |= move_right(puzzle);
		ret |= move_down(puzzle);
		ret |= move_left(puzzle);
		ret |= move_up(puzzle);
		ret |= move_right(puzzle);
		ret |= move_up(puzzle);
		ret |= move_left(puzzle);
		ret |= move_down(puzzle);
		ret |= move_right(puzzle);
		ret |= move_up(puzzle);
		ret |= move_left(puzzle);
		ret |= move_down(puzzle);
		ret |= move_down(puzzle);
		ret |= move_right(puzzle);
		ret |= move_up(puzzle);
		ret |= move_up(puzzle);
		ret |= move_left(puzzle);
		ret |= move_down(puzzle);
	}
	else
		return 1;

	return ret;
}

/*
 * Function: fix_algorithm2
 * ------------------------
 *
 * This function fixes the following board state automoatically
 * 		o	o	o
 * 		(2,0)	0	x
 * 		(2,1)	x	x
 * such that the two bottom left tiles are flipped back into
 * their correct positions without disturbing the top row.
 * This method will always handle this particular case.
 *
 * puzzle: Pointer to structure containing puzzle to modify.
 *
 * returns 1 if any moves fail, 0 on success
 */
int fix_algorithm2(struct grid_info *puzzle)
{
	int ret = 0;
	#if PUZZLE_PRINT_DEBUG == 1
	printf("fix alg2\n");
	#endif

	move_x_y(puzzle, (puzzle->szx-2)-(puzzle->xpos), 1-(puzzle->ypos));

	ret |= move_left(puzzle);
	ret |= move_down(puzzle);
	ret |= move_right(puzzle);
	ret |= move_up(puzzle);
	ret |= move_right(puzzle);
	ret |= move_down(puzzle);
	ret |= move_left(puzzle);
	ret |= move_up(puzzle);
	ret |= move_left(puzzle);
	ret |= move_down(puzzle);
	ret |= move_right(puzzle);
	ret |= move_up(puzzle);
	ret |= move_left(puzzle);
	ret |= move_down(puzzle);
	ret |= move_right(puzzle);
	ret |= move_right(puzzle);
	ret |= move_up(puzzle);
	ret |= move_left(puzzle);
	ret |= move_left(puzzle);
	ret |= move_down(puzzle);
	ret |= move_right(puzzle);

	return ret;
}

/*
 * Function: solve_top_row
 * -----------------------
 *
 * This method solves the top row of the puzzle.
 *
 * puzzle: Pointer to structure containing puzzle to modify.
 *
 * returns 0 on success (checks the result)
 * returns 1 when the check failed
 */
int solve_top_row(struct grid_info *puzzle)
{
	struct search_info *search;
	struct tile val;

	puzzle->num_solved = 0;
	val.y = puzzle->szy-1;
	for (int i = puzzle->szx-1; i > 1; i--) {
		val.x = i;
		search = init_search(&val, 1);
		apply_search(puzzle, search);
		move_tile_src_dst(puzzle, search->pos[0].x, search->pos[0].y, val.x, val.y);
		puzzle->num_solved++;
	}
	#if PUZZLE_PRINT_DEBUG == 1
	printf("Top row loop end\n");
	#endif

	val.x = 1;
	search = init_search(&val, 1);
	apply_search(puzzle, search);
	move_tile_src_dst(puzzle, search->pos[0].x, search->pos[0].y, 0, val.y);

	if (puzzle->xpos == 1 && puzzle->ypos == val.y)
		move_down(puzzle);

	val.x = 0;
	search = init_search(&val, 1);
	apply_search(puzzle, search);

	#if PUZZLE_PRINT_DEBUG == 1
	printf("Checking for alg1 requirement\n");
	#endif
	if (search->pos[0].x == 1 && search->pos[0].y == val.y)
		fix_algorithm1(puzzle);
	else {
		move_tile_src_dst(puzzle, search->pos[0].x, search->pos[0].y, 0, val.y-1);

		move_x_y(puzzle, 1-(puzzle->xpos), (val.y)-(puzzle->ypos));
		move_right(puzzle);
		move_down(puzzle);
	}

	for (int i = 0; i < puzzle->szx; i++) {
		if (check_tile(puzzle, i, val.y))
			return 1;
	}
	return 0;

}

/*
 * Function: solve_left_col
 * ------------------------
 *
 * This method solves the left column of the puzzle.
 * It is designed to solve it when there are only
 * two rows left. First reduce the puzzle using
 * the solve_top_row function. Execution not 
 * guaranteed if there are more than 2 rows.
 *
 * puzzle: Pointer to structure containing puzzle to modify.
 *
 * returns 0 on success (checks the result)
 * returns 1 when the check failed
 */
int solve_left_col(struct grid_info *puzzle)
{
	struct search_info *search;
	struct tile val;

	val.x = puzzle->szx-1;
	val.y = 0;
	search = init_search(&val, 1);
	apply_search(puzzle, search);

	move_tile_src_dst(puzzle, search->pos[0].x, search->pos[0].y, val.x, 1);

	if (puzzle->xpos == val.x && puzzle->ypos == 0)
		move_right(puzzle);

	val.x = puzzle->szx-1;
	val.y = 1;
	search = init_search(&val, 1);
	apply_search(puzzle, search);

	#if PUZZLE_PRINT_DEBUG == 1
	printf("Checking for alg2 requirement\n");
	#endif

	if (search->pos[0].x == val.x && search->pos[0].y == 0)
		fix_algorithm2(puzzle);
	else {
		move_tile_src_dst(puzzle, search->pos[0].x, search->pos[0].y, val.x-1, 1);

		move_y_x(puzzle, 0-(puzzle->ypos), (val.x)-(puzzle->xpos));
		move_up(puzzle);
		move_right(puzzle);
	}
	if (check_tile(puzzle, val.x, 1) || check_tile(puzzle, val.x, 0))
		return 1;

	return 0;
}

/*
 * Function: solve_final
 * ---------------------
 *
 * This method solves the remaining four tiles of a
 * puzzle. Designed for finishing a 2x2 reduced puzzle.
 *
 * puzzle: Pointer to structure containing puzzle to modify.
 *
 * returns 0 on success (the puzzle is solved)
 * returns 1 when unable to solve the puzzle
 */
int solve_final(struct grid_info *puzzle)
{
	struct tile t;
	if (puzzle->szy != 2 || puzzle->szx != 2)
		return 1;

	move_x_y(puzzle, 0-(puzzle->xpos), 0-(puzzle->ypos));
	if (is_win(puzzle))
		return 0;

	t.x = puzzle->grid[1][0].x;
	t.y = puzzle->grid[1][0].y;

	if (t.x == 1 && t.y == 1) {
		move_up(puzzle);
		move_left(puzzle);
		move_down(puzzle);
		move_right(puzzle);
	}
	else if (t.x == 0 && t.y == 1) {
		move_left(puzzle);
		move_up(puzzle);
		move_right(puzzle);
		move_down(puzzle);
	}

	if (is_win(puzzle))
		return 0;

	return 1;
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
	int szx, szy, ret;
	szx = puzzle->szx;
	szy = puzzle->szy;

	#if PUZZLE_PRINT_DEBUG == 1
	printf("Starting to solve top rows\n");
	#endif

	while (puzzle->szy > 2) {
		if (solve_top_row(puzzle))
			return 1;

		puzzle->szy--;
	}

	#if PUZZLE_PRINT_DEBUG == 1
	printf("Staring to solve left columns\n");
	#endif

	while (puzzle->szx > 2) {
		if (solve_left_col(puzzle))
			return 1;

		puzzle->szx--;
	}

	#if PUZZLE_PRINT_DEBUG == 1
	printf("Starting final solve step\n");
	#endif

	ret = solve_final(puzzle);
	puzzle->szx = szx;
	puzzle->szy = szy;
	return ret;
}

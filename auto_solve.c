#include "auto_solve.h"

void move_tile_down(struct grid_info *puzzle, int *xsrc, int *ysrc)
{
	if (puzzle->xpos == *xsrc)
		if (move_right(puzzle))
			move_left(puzzle);

	while (puzzle->ypos != (*ysrc)+1) {
		if (puzzle->ypos < (*ysrc)+1)
			move_up(puzzle);
		else
			move_down(puzzle);
	}

	while (puzzle->xpos != (*xsrc)) {
		if (puzzle->xpos < (*xsrc))
			move_left(puzzle);
		else
			move_right(puzzle);
	}

	move_up(puzzle);
	(*ysrc)++;
}

void move_tile_up(struct grid_info *puzzle, int *xsrc, int *ysrc)
{
	if (puzzle->xpos == *xsrc)
		if (move_right(puzzle))
			move_left(puzzle);

	while (puzzle->ypos != (*ysrc)-1) {
		if (puzzle->ypos < (*ysrc)-1)
			move_up(puzzle);
		else
			move_down(puzzle);
	}

	while (puzzle->xpos != (*xsrc)) {
		if (puzzle->xpos < (*xsrc))
			move_left(puzzle);
		else
			move_right(puzzle);
	}

	move_down(puzzle);
	(*ysrc)--;
}

void move_tile_right(struct grid_info *puzzle, int *xsrc, int *ysrc)
{
	if (puzzle->ypos == *ysrc)
		if (move_down(puzzle))
			move_up(puzzle);

	while (puzzle->xpos != (*xsrc)+1) {
		if (puzzle->xpos < (*xsrc)+1)
			move_left(puzzle);
		else
			move_right(puzzle);
	}

	while (puzzle->ypos != (*ysrc)) {
		if (puzzle->ypos < (*ysrc))
			move_up(puzzle);
		else
			move_down(puzzle);
	}

	move_left(puzzle);
	(*xsrc)++;
}

void move_tile_left(struct grid_info *puzzle, int *xsrc, int *ysrc)
{
	if (puzzle->ypos == *ysrc)
		if (move_down(puzzle))
			move_up(puzzle);

	while (puzzle->xpos != (*xsrc)-1) {
		if (puzzle->xpos < (*xsrc)-1)
			move_left(puzzle);
		else
			move_right(puzzle);
	}

	while (puzzle->ypos != (*ysrc)) {
		if (puzzle->ypos < (*ysrc))
			move_up(puzzle);
		else
			move_down(puzzle);
	}

	move_right(puzzle);
	(*xsrc)--;
}

void move_tile_src_dst(struct grid_info *puzzle, int xsrc, int ysrc, int xdst, int ydst)
{
	while (xsrc != xdst) {
		if (xsrc > xdst)
			move_tile_right(puzzle, &xsrc, &ysrc);
		else
			move_tile_left(puzzle, &xsrc, &ysrc);
	}

	while (ysrc != ydst) {
		if (ysrc > ydst)
			move_tile_down(puzzle, &xsrc, &ysrc);
		else
			move_tile_up(puzzle, &xsrc, &ysrc);
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
	int val = 7;

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

	while (!move_right(puzzle)) {}
	while (!move_up(puzzle)) {}
	while (!move_left(puzzle)) {}
	while (!move_down(puzzle)) {}
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


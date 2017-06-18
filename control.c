#include "control.h"

/*
 * Function: move_right
 * --------------------
 * 
 * Moves the tile to the right of the hole into the hole
 * Hole appears to move to the right one space
 *
 * puzzle: The structure that holds the tiles to be moved
 *
 * returns 1 if user called for an illigal move
 * returns 0 on success
 */
int move_right(struct grid_info *puzzle)
{
	int x = puzzle->xpos;
	int y = puzzle->ypos;

	if (x == puzzle->sz-1) {
		return 1;
	}

	puzzle->grid[x][y] = puzzle->grid[x+1][y];
	puzzle->grid[x+1][y] = 0;
	puzzle->xpos++;

	return 0;	
}

/*
 * Function: move_left
 * -------------------
 * 
 * Moves the tile to the left of the hole into the hole
 * Hole appears to move to the left one space
 *
 * puzzle: The structure that holds the tiles to be moved
 *
 * returns 1 if user called for an illigal move
 * returns 0 on success
 */
int move_left(struct grid_info *puzzle)
{
	int x = puzzle->xpos;
	int y = puzzle->ypos;

	if (x == 0) {
		return 1;
	}

	puzzle->grid[x][y] = puzzle->grid[x-1][y];
	puzzle->grid[x-1][y] = 0;
	puzzle->xpos--;

	return 0;	
}

/*
 * Function: move_down
 * -------------------
 * 
 * Moves the tile below the hole into the hole
 * Hole appears to move down one space
 *
 * puzzle: The structure that holds the tiles to be moved
 *
 * returns 1 if user called for an illigal move
 * returns 0 on success
 */
int move_down(struct grid_info *puzzle)
{
	int x = puzzle->xpos;
	int y = puzzle->ypos;

	if (y == puzzle->sz-1) {
		return 1;
	}

	puzzle->grid[x][y] = puzzle->grid[x][y+1];
	puzzle->grid[x][y+1] = 0;
	puzzle->ypos++;

	return 0;	
}

/*
 * Function: move_up
 * -----------------
 * 
 * Moves the tile above the hole into the hole
 * Hole appears to move up one space
 *
 * puzzle: The structure that holds the tiles to be moved
 *
 * returns 1 if user called for an illigal move
 * returns 0 on success
 */
int move_up(struct grid_info *puzzle)
{
	int x = puzzle->xpos;
	int y = puzzle->ypos;

	if (y == 0) {
		return 1;
	}

	puzzle->grid[x][y] = puzzle->grid[x][y-1];
	puzzle->grid[x][y-1] = 0;
	puzzle->ypos--;

	return 0;	
}

/*
 * Function: print_grid
 * --------------------
 *
 * Prints the tiles as a table to stdout
 *
 * puzzle: structure containing tiles to be printed
 */
void print_grid(struct grid_info *puzzle)
{
	for (int j = 0; j < puzzle->sz; j++) {
		for (int i = 0; i < puzzle->sz; i++) {
			printf("%d\t", puzzle->grid[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/*
 * Function: init_grid
 * -------------------
 *
 * Initializes a grid_info structure.
 * It allocates memory for the 2d array (grid)
 * and sets other variables to default values
 *
 * sz: Size of the grid to be initialized (if sz=3, grid is 3x3)
 *
 * returns a pointer to the initialized structure
 */
struct grid_info *init_grid(int sz)
{
	struct grid_info *puzzle = malloc(sizeof(struct grid_info));

	puzzle->sz = sz;
	puzzle->xpos = sz-1;
	puzzle->ypos = sz-1;
	puzzle->grid = malloc(sz*sizeof(int *));
	for (int i = 0; i < sz; i++) {
		puzzle->grid[i] = malloc(sz*sizeof(int));
		for (int j = 0; j < sz; j++)
			puzzle->grid[i][j] = (sz-i-1) + (sz-1-j)*sz;
	}

	return puzzle;
}

/*
 * Function: scramble_grid
 * -----------------------
 *
 * Scrambles the tiles in a grid randomly by calling
 * the move_up/down/right/left functions at random
 *
 * puzzle: Structure containing grid to be scrambled
 */
void scramble_grid(struct grid_info *puzzle, int num)
{

	for (int i = 0; i < num; i++) {
		int val = rand() % 4;
		switch(val) {
			case 0:	move_up(puzzle); break;
			case 1:	move_down(puzzle); break;
			case 2:	move_left(puzzle); break;
			case 3:	move_right(puzzle); break;
		}
	}
}

/*
 * Function: is_win
 * ----------------
 *
 * Checks if the puzzle has been solved by comparing
 * the values of all tiles to the initial state
 *
 * puzzle: Structure containing tiles to be checked
 *
 * returns 1 if all tiles match the initial state setup
 * returns 0 if even a single tile is out of place
 */
int is_win(struct grid_info *puzzle)
{
	int sz = puzzle->sz;
	
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < sz; j++)
			if (puzzle->grid[i][j] != (sz-i-1) + (sz-1-j)*sz)
				return 0;
	}
	return 1;
}

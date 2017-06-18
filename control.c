#include "control.h"

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

#ifndef PUZZLE_CONTROL_H
#define PUZZLE_CONTROL_H

#include <stdio.h>
#include <stdlib.h>

//define to 1 to print debug statements at runtime
#define PUZZLE_PRINT_DEBUG 0

//indexes for moves array in struct grid_info
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define STATE_INIT -2
#define STATE_SCRAMBLE -1
#define STATE_SOLVE 0

struct grid_info {
	struct tile **grid;	//grid of tiles that make up puzzle
	int szx;		//width of puzzle
	int szy;		//height of puzzle
	int xpos;		//x position of the hole (0,0)
	int ypos;		//y position of the hole
	int moves[4];		//numbers of moves done on the puzzle
	int state;		//state (solving, scrambling, done)
};

struct tile {
	int x;
	int y;
};

int move_right(struct grid_info *puzzle);
int move_left(struct grid_info *puzzle);
int move_up(struct grid_info *puzzle);
int move_down(struct grid_info *puzzle);
int check_tile(struct grid_info *puzzle, int x, int y);

struct grid_info *init_grid(int szx, int szy);

void print_grid(struct grid_info *puzzle);
void scramble_grid(struct grid_info *puzzle, int num);
void del_grid(struct grid_info *puzzle);

int is_win(struct grid_info *puzzle);
#endif

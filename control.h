#ifndef PUZZLE_CONTROL_H
#define PUZZLE_CONTROL_H

#include <stdio.h>
#include <stdlib.h>

#define STEP_BY_STEP_PRINT 1

struct grid_info {
	int ** grid;
	int szx;
	int szy;
	int xpos;
	int ypos;
};

int move_right(struct grid_info *puzzle);
int move_left(struct grid_info *puzzle);
int move_up(struct grid_info *puzzle);
int move_down(struct grid_info *puzzle);
int check_tile(struct grid_info *puzzle, int val, int xpos, int ypos);

struct grid_info *init_grid(int szx, int szy);

void print_grid(struct grid_info *puzzle);
void scramble_grid(struct grid_info *puzzle, int num);

int is_win(struct grid_info *puzzle);

#endif

#ifndef PUZZLE_CONTROL_H
#define PUZZLE_CONTROL_H

#include <stdio.h>
#include <stdlib.h>

struct grid_info {
	int ** grid;
	int sz;
	int xpos;
	int ypos;
};

int move_right(struct grid_info *puzzle);
int move_left(struct grid_info *puzzle);
int move_up(struct grid_info *puzzle);
int move_down(struct grid_info *puzzle);

struct grid_info *init_grid(int sz);

void print_grid(struct grid_info *puzzle);
void scramble_grid(struct grid_info *puzzle, int num);

int is_win(struct grid_info *puzzle);

#endif

#ifndef PUZZLE_SEARCH_H
#define PUZZLE_SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "control.h"

struct search_info {
	int *vals;
	int *x;
	int *y;
	int sz;
};

struct search_info *init_search(int *vals, int sz);

int search_grid(struct grid_info *puzzle, struct search_info *search);

void search_print(struct search_info *search);

#endif

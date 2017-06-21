#ifndef PUZZLE_SEARCH_H
#define PUZZLE_SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "control.h"

struct search_info {
	struct tile *pos;
	struct tile *vals;
	int sz;
};

struct search_info *init_search(struct tile *vals, int sz);

int apply_search(struct grid_info *puzzle, struct search_info *search);

void print_search(struct search_info *search);

#endif

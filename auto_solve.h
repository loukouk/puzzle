#ifndef PUZZLE_AUTO_SOLVE_H
#define PUZZLE_AUTO_SOLVE_H

#include "control.h"
#include "search.h"

void auto_solve_3x3(struct grid_info *puzzle);
void auto_solve(struct grid_info *puzzle);

#endif

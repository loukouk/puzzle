#ifndef PUZZLE_MAIN_H
#define PUZZLE_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "control.h"
#include "search.h"

void usage();
void user_solve(struct grid_info *puzzle);
void auto_solve_3x3(struct grid_info *puzzle);
void auto_solve(struct grid_info *puzzle);

#endif

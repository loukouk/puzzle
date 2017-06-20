#ifndef PUZZLE_MAIN_H
#define PUZZLE_MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "auto_solve.h"

void usage();
void user_solve(struct grid_info *puzzle);

extern char *optarg;
#endif

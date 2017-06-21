#include "control.h"
#include "search.h"
#include <time.h>

int main() {

	int    srch=8;
	struct grid_info *puzzle;
	struct search_info *search;
	struct tile *vals = malloc(srch*sizeof(struct tile));

	puzzle = init_grid(8, 5);
	print_grid(puzzle);

	vals[0].x =  1;
	vals[1].x = -2;
	vals[2].x =  0;
	vals[3].x =  4;
	vals[4].x =  5;
	vals[5].x =  7;
	vals[6].x =  3;
	vals[7].x =  5;
	vals[0].y =  4;
	vals[1].y =  3;
	vals[2].y = 11;
	vals[3].y =  2;
	vals[4].y =  1;
	vals[5].y = -2;
	vals[6].y =  0;
	vals[7].y =  7;

	search = init_search(vals, srch);
	printf("Search Results: %d items not found\n", apply_search(puzzle, search));
	print_search(search);

	srand(time(NULL));
	scramble_grid(puzzle, 1000);
	print_grid(puzzle);

	printf("Search Results: %d items not found\n", apply_search(puzzle, search));
	print_search(search);
}


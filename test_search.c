#include "control.h"
#include "search.h"
#include <time.h>

int main() {

	int  srch=6;
	struct grid_info *puzzle;
	puzzle = init_grid( 8, 4);

	print_grid(puzzle);

	struct search_info *search;
	
	int *vals = malloc(srch*sizeof(int));
	vals[0] = 11;
	vals[1] = 17;
	vals[2] = 2;
	vals[3] = 6;
	vals[4] = 35;
	vals[5] = -2;

	search = init_search(vals, srch);
	printf("Search Results: %d items not found\n", apply_search(puzzle, search));
	print_search(search);

	srand(time(NULL));
	scramble_grid(puzzle, 1000);
	print_grid(puzzle);

	printf("Search Results: %d items not found\n", apply_search(puzzle, search));
	print_search(search);
}


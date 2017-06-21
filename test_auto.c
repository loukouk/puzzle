#include "auto_solve.h"
#include <time.h>
#include <string.h>

#define NUM_TEST 10000

int main(int argc, char ** argv)
{
	int szx = 3, szy = 3;
	struct grid_info *puzzle[NUM_TEST];
	int fail_ids[NUM_TEST+1], ind = 0;
	int i;

	memset(fail_ids, 0, (NUM_TEST+1)*sizeof(int));
	srand(time(NULL));

	for (i = 0; i < NUM_TEST; i++) {
		puzzle[i] = init_grid(szx, szy);

		printf("PUZZLE %d: Scrambling...\n", i + 1);
		scramble_grid(puzzle[i], 200);
		print_grid(puzzle[i]);
	
		printf("PUZZLE %d: Scramble Done. Solving...\n", i + 1);
		if (auto_solve(puzzle[i])) {
			fail_ids[ind] = i+1;
			ind++;
		}
		printf("PUZZLE %d: Solving Done.\n", i + 1);
	}

	i = 0;
	printf("FAILURES:");
	while (fail_ids[i] != 0) {
		printf(" %d", fail_ids[i]);
		i++;
	}
	
	return EXIT_SUCCESS;
}

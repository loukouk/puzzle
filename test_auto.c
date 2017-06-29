#include "auto_solve.h"
#include <time.h>
#include <string.h>

#define NUM_TEST 1000

int main(int argc, char ** argv)
{
	int szx = 2, szy = 2;
	struct grid_info *puzzle[NUM_TEST];
	int fail_ids[NUM_TEST+1], ind = 0;
	int i, a, b, c, d;

	memset(fail_ids, 0, (NUM_TEST+1)*sizeof(int));
	srand(time(NULL));

	for (i = 0; i < NUM_TEST; i++) {
		puzzle[i] = init_grid(szx, szy);

		printf("PUZZLE %d: Scrambling...\n", i + 1);
		scramble_grid(puzzle[i], 1000);
		print_grid(puzzle[i]);
	
		printf("PUZZLE %d: Scramble Done. Solving...\n", i + 1);
		if (auto_solve(puzzle[i])) {
			fail_ids[ind] = i+1;
			ind++;
		}
		a = puzzle[i]->moves[UP];
		b = puzzle[i]->moves[DOWN];
		c = puzzle[i]->moves[LEFT];
		d = puzzle[i]->moves[RIGHT];
		printf("PUZZLE %d: Solving Done. UP:%d DOWN:%d LEFT:%d RIGHT:%d TOTAL:%d\n",i + 1, a, b, c, d, a+b+c+d);
	}

	i = 0;
	printf("%d FAILURES:", ind);
	while (fail_ids[i] != 0) {
		printf(" %d", fail_ids[i]);
		i++;
	}
	
	return EXIT_SUCCESS;
}

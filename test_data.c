#include "auto_solve.h"
#include <time.h>
#include <string.h>

#define NUM_TEST 1000

int main(int argc, char ** argv)
{
	struct grid_info *puzzle;
	int i, j, k, r=0;

	srand(time(NULL));

	printf("XxY\t3xY\tXx3\n");

	for (j = 2; j <= 51; j++) {

		for (i = 0; i < NUM_TEST; i++) {
			//TEST 1
			r=0;
			puzzle = init_grid(j,j);
			scramble_grid(puzzle, 100*j*j);
		
			if (auto_solve(puzzle)) {
				printf("FAIL %dx%d\n", j, j);
				exit(0);
			}

			for (k = 0; k < 4; k++) r+=puzzle->moves[k];

			printf("%d\t", r);
			free(puzzle);



			//TEST 2
			r=0;
			puzzle = init_grid(3,j);
			scramble_grid(puzzle, 300*j);
		
			if (auto_solve(puzzle)) {
				printf("FAIL 3x%d\n", j);
				exit(0);
			}

			for (k = 0; k < 4; k++) r+=puzzle->moves[k];

			printf("%d\t", r);

			free(puzzle);



			//TEST 3
			r=0;
			puzzle = init_grid(j,3);
			scramble_grid(puzzle, 300*j);
		
			if (auto_solve(puzzle)) {
				printf("FAIL %dx3\n", j);
				exit(0);
			}

			for (k = 0; k < 4; k++) r+=puzzle->moves[k];

			printf("%d\n", r);

			free(puzzle);
		}
	}


	return EXIT_SUCCESS;
}

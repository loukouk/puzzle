#include <stdio.h>
#include <stdlib.h>

struct grid_info puzzle {
	int ** grid;
	int sz;
	int xpos;
	int ypos;
};

int move_top(struct grid_info puzzle)
{
	
}

int **init_grid(int sz)
{
	struct grid_info *puzzle = malloc(sizeof(struct grid_info));

	puzzle->grid = malloc(sz*sizeof(int *));
	for (int i = 0; i < sz; i++) {
		puzzle->grid[i] = malloc(sz*sizeof(int));
		for (int j = 0; j < sz; j++)
			puzzle->grid[i][j] = (sz-i-1)*sz + (sz-1-j);
	}

	return puzzle;
}

void scramble_grid(struct grid_info *grid, int num)
{

}

void print_grid(struct grid_info *puzzle)
{
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < sz; j++) {
			printf("%d\t", puzzle->grid[i][j]);
		}
		printf("\n");
	}

}

void usage()
{
	printf("Usage: ./puzzle <grid size>\n\tGrid must be min 3x3.\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char ** argv)
{
	int sz = 3;
	struct grid_info puzzle;

	if (argc > 2)
		usage();
	else if (argc == 2) {
		sz = atoi(argv[1]);
		if (sz < 3)
			usage();
	}

	puzzle = init_grid(sz);
	print_grid(&grid);

	return EXIT_SUCCESS;
}

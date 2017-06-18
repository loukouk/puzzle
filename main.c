#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct grid_info {
	int ** grid;
	int sz;
	int xpos;
	int ypos;
};

int move_right(struct grid_info *puzzle)
{
	int x = puzzle->xpos;
	int y = puzzle->ypos;

	if (x == puzzle->sz-1) {
		return 1;
	}

	puzzle->grid[x][y] = puzzle->grid[x+1][y];
	puzzle->grid[x+1][y] = 0;
	puzzle->xpos++;

	return 0;	
}

int move_left(struct grid_info *puzzle)
{
	int x = puzzle->xpos;
	int y = puzzle->ypos;

	if (x == 0) {
		return 1;
	}

	puzzle->grid[x][y] = puzzle->grid[x-1][y];
	puzzle->grid[x-1][y] = 0;
	puzzle->xpos--;

	return 0;	
}

int move_down(struct grid_info *puzzle)
{
	int x = puzzle->xpos;
	int y = puzzle->ypos;

	if (y == puzzle->sz-1) {
		return 1;
	}

	puzzle->grid[x][y] = puzzle->grid[x][y+1];
	puzzle->grid[x][y+1] = 0;
	puzzle->ypos++;

	return 0;	
}

int move_up(struct grid_info *puzzle)
{
	int x = puzzle->xpos;
	int y = puzzle->ypos;

	if (y == 0) {
		return 1;
	}

	puzzle->grid[x][y] = puzzle->grid[x][y-1];
	puzzle->grid[x][y-1] = 0;
	puzzle->ypos--;

	return 0;	
}

void print_grid(struct grid_info *puzzle)
{
	for (int j = 0; j < puzzle->sz; j++) {
		for (int i = 0; i < puzzle->sz; i++) {
			printf("%d\t", puzzle->grid[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

struct grid_info *init_grid(int sz)
{
	struct grid_info *puzzle = malloc(sizeof(struct grid_info));

	puzzle->sz = sz;
	puzzle->xpos = sz-1;
	puzzle->ypos = sz-1;
	puzzle->grid = malloc(sz*sizeof(int *));
	for (int i = 0; i < sz; i++) {
		puzzle->grid[i] = malloc(sz*sizeof(int));
		for (int j = 0; j < sz; j++)
			puzzle->grid[i][j] = (sz-i-1) + (sz-1-j)*sz;
	}

	return puzzle;
}

void scramble_grid(struct grid_info *puzzle, int num)
{

	for (int i = 0; i < num; i++) {
		int val = rand() % 4;
		switch(val) {
			case 0:	move_up(puzzle); break;
			case 1:	move_down(puzzle); break;
			case 2:	move_left(puzzle); break;
			case 3:	move_right(puzzle); break;
		}
	}
}

void test_grid(struct grid_info *puzzle)
{
	move_up(puzzle);
	print_grid(puzzle);
	move_up(puzzle);
	print_grid(puzzle);
	move_up(puzzle);
	print_grid(puzzle);
	move_up(puzzle);
	print_grid(puzzle);
	move_left(puzzle);
	print_grid(puzzle);
	move_left(puzzle);
	print_grid(puzzle);
	move_left(puzzle);
	print_grid(puzzle);
	move_left(puzzle);
	print_grid(puzzle);
	move_left(puzzle);
	print_grid(puzzle);
	move_down(puzzle);
	print_grid(puzzle);
	move_down(puzzle);
	print_grid(puzzle);
	move_down(puzzle);
	print_grid(puzzle);
	move_down(puzzle);
	print_grid(puzzle);
	move_down(puzzle);
	print_grid(puzzle);
	move_right(puzzle);
	print_grid(puzzle);
	move_right(puzzle);
	print_grid(puzzle);
	move_right(puzzle);
	print_grid(puzzle);
	move_right(puzzle);
	print_grid(puzzle);
	move_right(puzzle);
	print_grid(puzzle);
}

void usage()
{
	printf("Usage: ./puzzle <grid size>\n\tGrid must be min 3x3.\n");
	exit(EXIT_FAILURE);
}

int is_win(struct grid_info *puzzle)
{
	int sz = puzzle->sz;
	
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < sz; j++)
			if (puzzle->grid[i][j] != (sz-i-1) + (sz-1-j)*sz)
				return 0;
	}
	return 1;
}

void user_solve(struct grid_info *puzzle)
{
	char c;

	while(1) {
		print_grid(puzzle);
		while ((c = getchar()) != '\n' && c != EOF) {
			switch(c) {
				case 'u':	move_up(puzzle); break;
				case 'd':	move_down(puzzle); break;
				case 'l':	move_left(puzzle); break;
				case 'r':	move_right(puzzle); break;
			}
		}

		if(is_win(puzzle))
			break;
	}

	printf("YOU WIN :D\n");
}

void auto_solve(struct grid_info *puzzle)
{
	//Write AI here
}

int main(int argc, char ** argv)
{
	int sz = 3, player = 1;
	struct grid_info *puzzle;

	if (argc > 2)
		usage();
	else if (argc == 2) {
		sz = atoi(argv[1]);
		if (sz < 3)
			usage();
	}

	srand(time(NULL));

	puzzle = init_grid(sz);
	scramble_grid(puzzle, 5);
//	print_grid(puzzle);

	if (player)
		user_solve(puzzle);
	else
		auto_solve(puzzle);

	return EXIT_SUCCESS;
}

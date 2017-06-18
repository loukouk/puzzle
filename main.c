#include "main.h"

void usage()
{
	printf("Usage: ./puzzle <grid size>\n\tGrid must be min 3x3.\n");
	exit(EXIT_FAILURE);
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


void auto_solve_3x3(struct grid_info *puzzle)
{
	
}

void auto_solve(struct grid_info *puzzle)
{
	if (puzzle->sz > 3) {
		printf("AI solve for grid greater than 3x3 not yet supported\n");
		exit(EXIT_FAILURE);
	}

	auto_solve_3x3(puzzle);
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

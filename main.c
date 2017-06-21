#include "main.h"

/*
 * Function: usage
 * ---------------
 *
 * Prints instructions on how to use program from the 
 * command line and exits
 */
void usage()
{
	printf( "\nUsage: ./puzzle [-hp] [-x x_size] [-y y_size]\n"
		"Grid must be size 2x2 minimum.\n\n");
	exit(EXIT_SUCCESS);
}

void print_help()
{
	printf( "\nThis program is an implementation of the 15 puzzle game. "
		"The goal of the program is to be able to create an AI that can solve the puzzle "
		"reguardless of the size of the grid. That does include non-square grids. "
		"Eventually, a performance analysis of the AI algorithm will be done to try "
		"finding methods of improving runtime for large grids.\n\n"
		"Command-line arguments:\n"
		"\t-h\n"
		"\t\tPrints the help message, as well as the usage string.\n\n"
		"\t-p\n"
		"\t\tLets the user solve the puzzle instead of solving it by itself.\n\n"
		"\t-x\n"
		"\t\tLets the user specify the width of the grid to be used for the puzzle.\n\n"
		"\t-y\n"
		"\t\tLets the user specify the height of the grid to be used for the puzzle.\n\n");
}

/*
 * Function: user_solve
 * --------------------
 *
 * Takes input from the user and applies the user's commands to
 * the grid being modified. This function only exits once the user
 * has solved the puzzle
 *
 * puzzle: Pointer to structure containing the grid the user is playing with
 */
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


/*
 * Function: main
 * --------------
 *
 * Interprets command line arguments to change grid sizes.
 * Calls initilization methods and gives control of the
 * puzzle to the user or to the AI
 *
 * argc: number of command line arguments
 * argv: Array of strings representing command line args
 *
 * returns EXIT_SUCCESS on program's successful exit
 * returns EXIT_FAILURE or error code otherwise
 */
int main(int argc, char ** argv)
{
	int player = 0, szx = 3, szy = 3;
	struct grid_info *puzzle;
	char c;

	while ((c = getopt (argc, argv, "hpx:y:")) != -1) {
		switch(c) {
			case 'h':
				print_help();	
				usage();
				break;
			case 'p':
				player = 1;
				break;
			case 'x':	
				szx = atoi(optarg);
				if (szx < 2)
					usage();
				break;
			case 'y':
				szy = atoi(optarg);
				if (szy < 2)
					usage();
				break;
			default:
				usage();
		}
	}

	srand(time(NULL));

	puzzle = init_grid(szx, szy);
	scramble_grid(puzzle, szx*szy*20);
	print_grid(puzzle);
	printf("Scramble Done\n");

	if (player)
		user_solve(puzzle);
	else
		auto_solve(puzzle);

	return EXIT_SUCCESS;
}

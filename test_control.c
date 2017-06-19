#include <time.h>
#include "control.h"

void test_grid(struct grid_info *puzzle)
{
	print_grid(puzzle);

	for (int i = 0; i <= puzzle->szx; i++) {
		move_left(puzzle);
		print_grid(puzzle);
	}
	for (int i = 0; i <= puzzle->szy; i++) {
		move_up(puzzle);
		print_grid(puzzle);
	}
	for (int i = 0; i <= puzzle->szx; i++) {
		move_right(puzzle);
		print_grid(puzzle);
	}
	for (int i = 0; i <= puzzle->szy; i++) {
		move_down(puzzle);
		print_grid(puzzle);
	}
}

int main() {

	struct grid_info *puzzle = init_grid(4, 6);
	test_grid(puzzle);

	srand(time(NULL));
	scramble_grid(puzzle, 1000);
	test_grid(puzzle);

}


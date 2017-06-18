#include "control.h"

void test_grid(struct grid_info *puzzle)
{
	print_grid(puzzle);

	for (int i = 0; i <= puzzle->sz; i++) {
		move_left(puzzle);
		print_grid(puzzle);
	}
	for (int i = 0; i <= puzzle->sz; i++) {
		move_down(puzzle);
		print_grid(puzzle);
	}
	for (int i = 0; i <= puzzle->sz; i++) {
		move_right(puzzle);
		print_grid(puzzle);
	}
	for (int i = 0; i <= puzzle->sz; i++) {
		move_up(puzzle);
		print_grid(puzzle);
	}
}

int main() {

}


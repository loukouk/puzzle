#include "search.h"

void search_print(struct search_info *search)
{
	for (int i = 0; i < search->sz; i++) {
		printf("Value %d at (%d, %d)\n", search->vals[i], search->x[i], search->y[i]);
	}
}

struct search_info *init_search(int *vals, int sz)
{
	struct search_info *search = malloc(sizeof(struct search_info));
	search->vals = vals;
	search->sz = sz;
	search->x = malloc(sz*sizeof(int));
	search->y = malloc(sz*sizeof(int));

	return search;
}

int search_grid(struct grid_info *puzzle, struct search_info *search)
{
	int cnt = search->sz;
	for (int i = 0; i < cnt; i++) {
		search->x[i] = -1;
		search->y[i] = -1;
	}

	for (int i = 0; i < puzzle->sz; i++) {
		for (int j = 0; j < puzzle->sz; j++) {
			for (int k = 0; k < search->sz; k++) {
				if (puzzle->grid[i][j] == search->vals[k]) {
					search->x[k] = i;
					search->y[k] = j;
					cnt--;
					if (!cnt)
						return 0;
				}
			}
		}
	}
	return cnt;
}

#include "search.h"

/*
 * Function: print_search
 * ----------------------
 *
 * Prints the searched values and their location in the grid if found.
 * If a value was not found, its coordinates will be (-1, -1).
 *
 * search: Pointer to structure containing the searched values and results
 */
void print_search(struct search_info *search)
{
	for (int i = 0; i < search->sz; i++) {
		printf("Tile (%d,%d) is at (%d,%d)\n", search->vals[i].x, search->vals[i].y, search->pos[i].x, search->pos[i].y);
	}
}

/*
 * Function: init_search
 * ---------------------
 *
 * Initializes a search_info structure.
 * It will allocate memory for the structure itself and the arrays within
 * it, except for the vals array. The user must create the vals array and
 * make it contain the values to be searched.
 *
 * vals: Array of values to be searched
 * sz: size of vals array, number of values to be searched
 *
 * returns a pointer to the initialized search_info structure
 */
struct search_info *init_search(struct tile *vals, int sz)
{
	struct search_info *search = malloc(sizeof(struct search_info));
	search->vals = vals;
	search->sz = sz;
	search->pos = malloc(sz*sizeof(struct tile));

	return search;
	return NULL;
}

/*
 * Function: del_search
 * --------------------
 *
 * This function deletes a search_info structure properly.
 * Using this function ensures that all memory used is 
 * properly returned to the OS for future reuse.
 *
 * search: Pointer to structure to be deleted
 */
void del_search(struct search_info * search)
{
	free(search->pos);
	free(search);
}

/*
 * Function: apply_search
 * ----------------------
 *
 * This function takes a search_info structure and a grid_info structure
 * and applies the search criteria on the chosen grid.
 *
 * puzzle: holds the grid to be searched on
 * search: holds values to be searched in vals array
 *
 * returns the number of values that were not found in the grid.
 * On success, return value should therefore be 0
 */
int apply_search(struct grid_info *puzzle, struct search_info *search)
{
	int cnt = search->sz;

	for (int i = 0; i < cnt; i++) {
		search->pos[i].x = -1;
		search->pos[i].y = -1;
	}

	for (int i = 0; i < puzzle->szx; i++) {
		for (int j = 0; j < puzzle->szy; j++) {
			for (int k = 0; k < search->sz; k++) {

				if (puzzle->grid[i][j].x == search->vals[k].x
				&&  puzzle->grid[i][j].y == search->vals[k].y) {
					search->pos[k].x = i;
					search->pos[k].y = j;
					cnt--;
					if (!cnt)
						return 0;
				}
			}
		}
	}
	return cnt;
}

#include "Board.h"
#include <time.h>

/*
 * The following function acts like a map, connecting between the 3
 * different options for board sizes and their correct amount of bombs.
 * Input: The size of the board.
 * Output: The correct amount of bombs needed for the board.
 */
static uint8_t
size_to_bombs(uint8_t size) {
	switch (size) {
		case EASY_BOARD_SIZE: return 10;
		case MEDIUM_BOARD_SIZE: return 40;
		case HARD_BOARD_SIZE: return 99;
		default: return 1;
	}
}

/*
 * The following function puts all the pointers of the cell surrounding an individual
 * single cell and returns the amount of cells around this individual cell.
 * Input: A pointer to the player's board, a pointer to the central cell and  
 * the array the surrounding cells will be stored at.
 * Output: The amount of cells around the central cell.
 */
static uint8_t
get_surrounding_cells(board_t* p_board, cell_t* center, cell_t* surroundings[MAX_SURROUNDINGS]) {
	uint8_t index = 0;
	int8_t row = center->row, column = center->column;

	if (row > 0) {
		surroundings[index++] = &p_board->matrix[row - 1][column];
		if (column > 0)
			surroundings[index++] = &p_board->matrix[row - 1][column - 1];
		if (column < p_board->size - 1)
			surroundings[index++] = &p_board->matrix[row - 1][column + 1];
	}
	if (row < p_board->size - 1) {
		surroundings[index++] = &p_board->matrix[row + 1][column];
		if (column > 0)
			surroundings[index++] = &p_board->matrix[row + 1][column - 1];
		if (column < p_board->size - 1)
			surroundings[index++] = &p_board->matrix[row + 1][column + 1];
	}
	if (column > 0)
		surroundings[index++] = &p_board->matrix[row][column - 1];
	if (column < p_board->size - 1)
		surroundings[index++] = &p_board->matrix[row][column + 1];

	return index;
}

board_t* 
create_board(uint8_t size) {
	uint8_t row, column, bombs_put = 0, cells_found, cell_index;
	cell_t* p_cell, *surroundings[MAX_SURROUNDINGS];

	/* Allocating the board */
	board_t* new_board = (board_t*)malloc(sizeof(board_t));
	if (!new_board) 
		goto allocation_error;

	/* Initializing board */
	new_board->size = size;
	new_board->bombs_amount = size_to_bombs(size);
	if (new_board->bombs_amount == 1) {
		printf("%sERROR:%s Invalid input\n", KRED, RESET);
		return NULL;
	}

	/* Allocating matrix */
	new_board->matrix = (cell_t**)calloc(size, sizeof(cell_t*));
	if (!new_board->matrix) {
		free(new_board);
		goto allocation_error;
	}

	/* Initializing matrix */
	for (row = 0; row < size; row++) {
		new_board->matrix[row] = (cell_t*)calloc(size, sizeof(cell_t));
		if (!new_board->matrix[row]) {
			for (uint8_t temp = 0; temp < row; temp++)
				free(new_board->matrix[temp]);
			free(new_board->matrix);
			free(new_board);
			goto allocation_error;
		}

		for (column = 0; column < size; column++) {
			p_cell = &new_board->matrix[row][column];

			p_cell->status = WATER;
			p_cell->hidden = true;
			p_cell->flagged = false;
			p_cell->marked = false;
			p_cell->nearby_bombs = 0;
			p_cell->row = row;
			p_cell->column = column;
		}
	}
	new_board->p_mark = &new_board->matrix[0][0];
	new_board->p_mark->marked = true;

	/* Putting bombs */
	srand((unsigned int)time(NULL)); /* Refreshing rand() function seed */
	while (bombs_put < new_board->bombs_amount) {
		p_cell = &new_board->matrix[rand() % size][rand() % size];

		if (p_cell->status == WATER) {
			p_cell->status = BOMB;
			cells_found = get_surrounding_cells(new_board, p_cell, surroundings);
			for (cell_index = 0; cell_index < cells_found; cell_index++)
				surroundings[cell_index]->nearby_bombs++;
			bombs_put++;
		}
	}

	return new_board;

allocation_error:
	printf("%sERROR:%s Memory allocation failed\n", KRED, RESET);
	return NULL;
}

void 
free_board(board_t* p_board) {
	for (uint8_t row = 0; row < p_board->size; row++)
		free(p_board->matrix[row]);
	free(p_board->matrix);
	free(p_board);
}

void 
display_board(board_t* p_board) {
	uint8_t column;

	for (uint8_t row = 0; row < p_board->size; row++) {
		for (column = 0; column < p_board->size; column++)
			display_cell(p_board->matrix[row][column]);
		printf("\n");
	}
	printf("%s", RESET);
}

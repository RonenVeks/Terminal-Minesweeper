#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"

#define EASY_BOARD_SIZE 9
#define MEDIUM_BOARD_SIZE 16
#define HARD_BOARD_SIZE 25
#define MAX_SURROUNDINGS 8

typedef struct {
	cell_t** matrix;
	uint8_t size, bombs_amount;
	cell_t* p_mark;
} board_t;

/*
 * The following function will initialize a new board according to the give size.
 * Input: The size for the board.
 * Output: A pointer to the new heap-allocated board.
 */
board_t* create_board(uint8_t size);

/*
 * The following function frees the allocation of the player's board.
 * Input: A pointer to the players board.
 * Output: None.
 */
void free_board(board_t* p_board);

/*
 * The following function prints every cell on the board with the correct color and symbol.
 * Input: A pointer to the player's board.
 * Output: None.
 */
void display_board(board_t* p_board);

#endif /* BOARD_H */

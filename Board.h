#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"

#define EASY_BOARD_SIZE 9
#define MEDIUM_BOARD_SIZE 16
#define HARD_BOARD_SIZE 25

typedef struct {
	cell_t** matrix;
	uint8_t size, bombs_amount;
	cell_t* p_mark;
} board_t;

/*
 * The following function will initialize a new board according to the give size 
 * Input: The size for the board 
 * Output: A pointer to the new heap-allocated board 
 */
board_t* create_board(uint8_t size);

#endif /* BOARD_H */

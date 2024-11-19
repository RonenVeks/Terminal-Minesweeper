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

/*
 * The following funcion changes the marked cell of the board to another location. 
 * Input: A pointer to the player's board and the row and the column of the new mark.
 * Output: None.
 */
void change_mark(board_t* p_board, uint8_t row, uint8_t column);

/*
 * The following function opens an every empty cell in a recursive way, as minesweeper
 * is supposed to do.
 * Input: A pointer to the player's board and a pointer to the clicked cell.
 * Output: None.
 */
void open_empty_cell(board_t* p_board, cell_t* p_cell);

/*
 * The following function opens a numbered cell according to it's visibility. 
 * Input: A pointer to the player's board and a pointer to the clicked cell.
 * Output: None.
 */
void open_numbered_cell(board_t* p_board, cell_t* p_cell);

#endif /* BOARD_H */

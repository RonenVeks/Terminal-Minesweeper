#include "Board.h"
#include "Cell.h"

/*
 * The following function lets the player decide what is their preferred 
 * size for the board with a nice keyboard interface. 
 * Input: None. 
 * Output: The size the players decided.
 */
static uint8_t 
get_board_size() {
	uint8_t option = 1, key;
	bool chose = false;

	while (!chose) {
		CLEAR_TERMINAL;
		printf("%sGame Modes:\n", KMAG);
		option == 1 ? printf("%s -> %s1) %s9 Cells - Easy\n", RESET, KRED, KYEL) :
			printf("    %s1) %s9 Cells - Easy\n", KRED, KYEL);
		option == 2 ? printf("%s -> %s2) %s16 Cells - Medium\n", RESET, KRED, KYEL) :
			printf("    %s2) %s16 Cells - Medium\n", KRED, KYEL);
		option == 3 ? printf("%s -> %s3) %s25 Cells - Hard\n", RESET, KRED, KYEL) :
			printf("    %s3) %s25 Cells - Hard\n", KRED, KYEL);

		key = _getch();
		if (key == UP_ARROW_ASCII && option > 1)
			option--;
		else if (key == DOWN_ARROW_ASCII && option < 3)
			option++;
		else if (key == ENTER_ASCII)
			chose = true;
	}
	switch (option) {
		case 1: return EASY_BOARD_SIZE;
		case 2: return MEDIUM_BOARD_SIZE;
		case 3: return HARD_BOARD_SIZE;
		default: return 1;
	}
}

/*
 * The following function will serve as the game loop.
 * Input: A pointer to the players board.
 * Output: None.
 */
void
game_loop(board_t* p_board) {
	bool game = true;
	uint8_t key, row, column;

	while (game) {
		CLEAR_TERMINAL;
		/* Updating the position of the mark in case of movement */
		row = p_board->p_mark->row;
		column = p_board->p_mark->column;

		display_board(p_board);
		key = _getch();

		/* Arrows movement */
		if (key == UP_ARROW_ASCII && row > 0)
			change_mark(p_board, row - 1, column);
		if (key == DOWN_ARROW_ASCII && row < p_board->size - 1)
			change_mark(p_board, row + 1, column);
		if (key == RIGHT_ARROW_ASCII && column < p_board->size - 1)
			change_mark(p_board, row, column + 1);
		if (key == LEFT_ARROW_ASCII && column > 0)
			change_mark(p_board, row, column - 1);

		if (key == ENTER_ASCII)
			game = false;
	}
}

/* Main function. */
int
main(void) {
	uint8_t board_size = get_board_size();
	board_t* p_board = create_board(board_size);
	if (!p_board)
		return EXIT_FAILURE;

	game_loop(p_board);
	free_board(p_board);
	return EXIT_SUCCESS;
}

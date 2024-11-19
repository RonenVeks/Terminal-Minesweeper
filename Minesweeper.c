#include "Board.h"

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

int
main(void) {
	printf("Hello World\n");
	return EXIT_SUCCESS;
}

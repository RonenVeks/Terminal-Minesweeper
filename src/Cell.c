#include "Cell.h"

void 
display_cell(cell_t cell, bool show) {
	if (!show && cell.marked)
		printf("%s%c", RESET, MARKED_ASCII);
	else if (!show && cell.hidden)
		cell.flagged ? printf("%sF", KRED) : printf(" ");
	else if (cell.status == WATER)
		cell.nearby_bombs == 0 ? printf("%s~", KBLU) : printf("%s%d", RESET, cell.nearby_bombs);
	else
		printf("%s#", KRED);

	printf("%s|", KYEL);
}

#ifndef CELL_H
#define CELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define CLEAR_TERMINAL system("cls");

/* Keyboard key ascii */
#define ENTER_ASCII 13
#define UP_ARROW_ASCII 72
#define DOWN_ARROW_ASCII 80
#define RIGHT_ARROW_ASCII 77
#define LEFT_ARROW_ASCII 75

/* Colors: */
#define KGRN  "\x1B[32m"
#define KWHT  "\x1B[37m"
#define KRED  "\x1B[31m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define RESET "\x1B[0m"

typedef enum { WATER, BOMB} status_t;

typedef struct {
	status_t status;
	bool hidden, flagged, marked;
	uint8_t nearby_bombs, row, column;
} cell_t;

#endif /* CELL_H */

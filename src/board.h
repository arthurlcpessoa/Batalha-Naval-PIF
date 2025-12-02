#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

typedef enum { CELL_WATER, CELL_SHIP, CELL_HIT, CELL_MISS } CellState;

typedef struct {
    CellState state;
    int ship_id;
} Cell;

typedef struct {
    int rows, cols;
    Cell *cells;
} Board;

bool board_init(Board *b, int rows, int cols);
void board_free(Board *b);
Cell* board_cell(Board *b, int r, int c);
bool board_in_bounds(Board *b, int r, int c);
void board_clear(Board *b);
void board_place_ship_cells(Board *b, int ship_id, int r, int c, int length, int orient);
void board_print_owner(Board *b);
void board_print_opponent(Board *b);

#endif

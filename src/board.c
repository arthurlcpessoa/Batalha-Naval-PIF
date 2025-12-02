#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool board_init(Board *b, int rows, int cols) {
    if (!b) return false;
    if (rows < 1 || cols < 1) return false;
    b->rows = rows;
    b->cols = cols;
    b->cells = (Cell*) malloc(sizeof(Cell) * rows * cols);
    if (!b->cells) return false;
    board_clear(b);
    return true;
}

void board_free(Board *b) {
    if (!b) return;
    if (b->cells) {
        free(b->cells);
        b->cells = NULL;
    }
    b->rows = 0;
    b->cols = 0;
}

Cell* board_cell(Board *b, int r, int c) {
    if (!b) return NULL;
    if (!board_in_bounds(b, r, c)) return NULL;
    return &b->cells[r * b->cols + c];
}

bool board_in_bounds(Board *b, int r, int c) {
    if (!b) return false;
    return (r >= 0 && r < b->rows && c >= 0 && c < b->cols);
}

void board_clear(Board *b) {
    if (!b || !b->cells) return;
    int total = b->rows * b->cols;
    for (int i = 0; i < total; ++i) {
        b->cells[i].state = CELL_WATER;
        b->cells[i].ship_id = -1;
    }
}

void board_place_ship_cells(Board *b, int ship_id, int r, int c, int length, int orient) {
    if (!b || !b->cells) return;
    for (int i = 0; i < length; ++i) {
        int rr = r + (orient ? i : 0);
        int cc = c + (orient ? 0 : i);
        if (board_in_bounds(b, rr, cc)) {
            Cell *cell = board_cell(b, rr, cc);
            cell->state = CELL_SHIP;
            cell->ship_id = ship_id;
        }
    }
}

void board_print_owner(Board *b) {
    if (!b || !b->cells) return;
    printf("   ");
    for (int c = 0; c < b->cols; ++c) printf(" %c", 'A' + c);
    printf("\n");
    for (int r = 0; r < b->rows; ++r) {
        printf("%2d ", r + 1);
        for (int c = 0; c < b->cols; ++c) {
            Cell *cell = board_cell(b, r, c);
            char ch = '~';
            if (cell->state == CELL_WATER) ch = '~';
            else if (cell->state == CELL_SHIP) ch = 'S';
            else if (cell->state == CELL_HIT) ch = 'X';
            else if (cell->state == CELL_MISS) ch = '.';
            printf(" %c", ch);
        }
        printf("\n");
    }
}

void board_print_opponent(Board *b) {
    if (!b || !b->cells) return;
    printf("   ");
    for (int c = 0; c < b->cols; ++c) printf(" %c", 'A' + c);
    printf("\n");
    for (int r = 0; r < b->rows; ++r) {
        printf("%2d ", r + 1);
        for (int c = 0; c < b->cols; ++c) {
            Cell *cell = board_cell(b, r, c);
            char ch = '~';
            if (cell->state == CELL_HIT) ch = 'X';
            else if (cell->state == CELL_MISS) ch = '.';
            else ch = '~';
            printf(" %c", ch);
        }
        printf("\n");
    }
}

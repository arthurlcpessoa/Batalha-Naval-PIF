#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "game.h"
#include "board.h"
#include "fleet.h"
#include "io.h"
#include "rnd.h"


static int can_place(Board *b, int r, int c, int length, int orient) {
for (int i = 0; i < length; i++) {
int rr = r + (orient == ORIENT_V ? i : 0);
int cc = c + (orient == ORIENT_H ? i : 0);
if (!board_in_bounds(b, rr, cc)) return 0;
Cell *cell = board_cell(b, rr, cc);
if (!cell || cell->ship_id != -1) return 0;
}
return 1;
}


static int already_shot(Board *b, int r, int c) {
Cell *cell = board_cell(b, r, c);
if (!cell) return 1;
return cell->state == CELL_HIT || cell->state == CELL_MISS;
}


void place_fleet_auto_on_board(Board *b, Fleet *f) {
for (int i = 0; i < f->count; i++) {
Ship *s = &f->ships[i];
while (1) {
int orient = rnd_int(0,1) ? ORIENT_V : ORIENT_H;
int maxr = b->rows - (orient == ORIENT_V ? s->length : 1);
int maxc = b->cols - (orient == ORIENT_H ? s->length : 1);
int r = rnd_int(0, maxr);
int c = rnd_int(0, maxc);
if (can_place(b, r, c, s->length, orient)) {
board_place_ship_cells(b, i, r, c, s->length, orient == ORIENT_H ? 0 : 1);
s->placed = 1;
s->start_r = r;
s->start_c = c;
s->orient = orient;
break;
}
}
}
}


void place_fleet_manual_on_board(Board *b, Fleet *f) {
for (int i = 0; i < f->count; i++) {
Ship *s = &f->ships[i];
int r, c, orient;
char orientChar;
while (1) {
board_print_owner(b);
printf("Posicione o navio %s (tamanho %d)\n", s->name, s->length);
printf("Digite coordenada inicial (ex.: A5): ");
char buf[16];
io_read_line(buf, sizeof(buf));
if (!io_parse_coord(buf, &r, &c, b)) {
printf("Coordenada inválida. Tente novamente.\n");
continue;
}
printf("Orientação (H)orizontal ou (V)ertical? ");
orientChar = getchar();
int ch;
while ((ch = getchar()) != '\n' && ch != EOF); // limpa stdin
orientChar = toupper((unsigned char)orientChar);
if (orientChar == 'H') orient = ORIENT_H;
else if (orientChar == 'V') orient = ORIENT_V;
else {
printf("Orientação inválida.\n");
continue;
}
if (can_place(b, r, c, s->length, orient)) {
board_place_ship_cells(b, i, r, c, s->length, orient == ORIENT_H ? 0 : 1);
s->placed = 1;
s->start_r = r;
s->start_c = c;
s->orient = orient;
break;
} else {
printf("Não é possível posicionar o navio nessa posição.\n");
}
}
}
}

void initGame(Game *g, const char *p1, const char *p2, int boardSize, char placementChoice) {
g->currentPlayer = 0;
strncpy(g->player1Name, p1, sizeof(g->player1Name)-1);
strncpy(g->player2Name, p2, sizeof(g->player2Name)-1);
g->player1Name[sizeof(g->player1Name)-1] = '\0';
g->player2Name[sizeof(g->player2Name)-1] = '\0';


board_init(&g->boards[0], boardSize, boardSize);
board_init(&g->boards[1], boardSize, boardSize);

fleet_init(&g->fleets[0]);
fleet_init(&g->fleets[1]);
fleet_add_default_ships(&g->fleets[0]);
fleet_add_default_ships(&g->fleets[1]);

if (toupper((unsigned char)placementChoice) == 'M') {
    place_fleet_manual_on_board(&g->boards[0], &g->fleets[0]);
    place_fleet_auto_on_board(&g->boards[1], &g->fleets[1]);
} else {
    place_fleet_auto_on_board(&g->boards[0], &g->fleets[0]);
    place_fleet_auto_on_board(&g->boards[1], &g->fleets[1]);
}


}


void playerTurn(Game *g) {
int activePlayer = g->currentPlayer;
Board *opponentBoard = &g->boards[1 - activePlayer];
Fleet *opponentFleet = &g->fleets[1 - activePlayer];
const char *playerName = activePlayer == 0 ? g->player1Name : g->player2Name;


int r, c;
char buf[16];

printf("\nTurno de %s\n", playerName);
board_print_owner(opponentBoard);

while (1) {
    printf("Digite coordenada do tiro (ex.: A5): ");
    io_read_line(buf, sizeof(buf));
    if (!io_parse_coord(buf, &r, &c, opponentBoard)) {
        printf("Entrada inválida. Tente novamente.\n");
        continue;
    }
    if (already_shot(opponentBoard, r, c)) {
        printf("Você já atirou nessa posição. Tente outra.\n");
        continue;
    }

    Cell *cell = board_cell(opponentBoard, r, c);
    if (cell->state == CELL_SHIP) {
        cell->state = CELL_HIT;
        int id = cell->ship_id;
        if (id >= 0 && id < opponentFleet->count) {
            opponentFleet->ships[id].hits++;
            if (opponentFleet->ships[id].hits >= opponentFleet->ships[id].length) {
                printf("AFUNDOU %s!\n", opponentFleet->ships[id].name);
            } else {
                printf("ACERTOU no %s!\n", opponentFleet->ships[id].name);
            }
        } else {
            printf("ACERTOU!\n");
        }
    } else {
        cell->state = CELL_MISS;
        printf("AGUA.\n");
    }
    break;
}

g->currentPlayer = 1 - g->currentPlayer;


}


void enemyTurn(Game *g) {
playerTurn(g);
}


int checkVictory(Game *g) {
if (fleet_all_sunk(&g->fleets[1])) return 1;
if (fleet_all_sunk(&g->fleets[0])) return 2;
return 0;
}

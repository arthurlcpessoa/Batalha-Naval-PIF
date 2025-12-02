#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "fleet.h"

typedef struct {
    char player1Name[32];
    char player2Name[32];
    Board boards[2];
    Fleet fleets[2];
    int currentPlayer;
} Game;

void initGame(Game *g, const char *p1, const char *p2, int boardSize, char placementChoice);
void playerTurn(Game *g);
int checkVictory(Game *g);

#endif

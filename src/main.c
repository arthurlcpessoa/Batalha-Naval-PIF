#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "game.h"
#include "io.h"

void clearScreen() {
#ifdef _WIN32
system("cls");
#else
system("clear");
#endif
}

int main() {
Game game;
int opcao;


while (1) {
    clearScreen();
    printf("=== BATALHA NAVAL ===\n");
    printf("1) Novo jogo\n");
    printf("2) Sair\n");
    printf("> ");
    char buf[10];
    io_read_line(buf, sizeof(buf));
    opcao = atoi(buf);

    if (opcao == 1) {
        char player1Name[32], player2Name[32];
        int boardSize;
        char placementChoice;

        printf("Informe apelido do Jogador 1: ");
        io_read_line(player1Name, sizeof(player1Name));
        printf("Informe apelido do Jogador 2: ");
        io_read_line(player2Name, sizeof(player2Name));

        do {
            printf("Tamanho do tabuleiro (6-26): ");
            io_read_line(buf, sizeof(buf));
            boardSize = atoi(buf);
        } while (boardSize < 6 || boardSize > 26);

        do {
            printf("Posicionamento (M)anual ou (A)utomático? ");
            placementChoice = getchar();
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            placementChoice = toupper((unsigned char)placementChoice);
        } while (placementChoice != 'M' && placementChoice != 'A');

        initGame(&game, player1Name, player2Name, boardSize, placementChoice);

        int winner = 0;
        while (!winner) {
            playerTurn(&game);
            winner = checkVictory(&game);
        }

        printf("\n=== Jogo terminado! ===\n");
        if (winner == 1) printf("Vencedor: %s\n", game.player1Name);
        else if (winner == 2) printf("Vencedor: %s\n", game.player2Name);

        printf("Pressione ENTER para voltar ao menu...");
        getchar(); // pausa
    } else if (opcao == 2) {
        printf("Saindo do jogo...\n");
        break;
    } else {
        printf("Opção inválida. Tente novamente.\n");
    }
}

return 0;


}

#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "tetris.h"
#include "txt.h"
#include <stdio.h>
#include <string.h>

int main() {

    screenInit(1);
    keyboardInit();
    timerInit(1000);
    initRankingSystem();

    char playerName[MAX_NAME_LENGTH] = {0};
    screenClear();
    screenGotoxy(10, 5);
    printf("Nome: (Max %d chars): ", MAX_NAME_LENGTH-1);
    screenUpdate();
 
    int i = 0;
    while (i < MAX_NAME_LENGTH - 1) {
        if (keyhit()) {
            char c = readch();
            if (c == '\n' || c == '\r') break;
            if (c == 127 && i > 0) {
                i--;
                printf("\b \b");
            } else if (c >= 32 && c <= 126) {
                playerName[i++] = c;
                printf("%c", c);
            }
            screenUpdate();
        }
    }
    playerName[i] = '\0';

    screenClear();
    displayRanking();
    screenGotoxy(10, 15);
    printf("Pressione qualquer tecla para comecar...");
    screenUpdate();
    while (!keyhit()) {}
    readch();

    TetrisGame game;
    initGame(&game);
    gameLoop(&game);

    saveScore(playerName, game.score);
    screenClear();
    displayRanking();
    screenGotoxy(10, 15);
    printf("Sua pontuacao: %d", game.score);
    screenGotoxy(10, 17);
    printf("Pressione qualquer tecla para sair...");
    screenUpdate();
    while (!keyhit()) {}
    readch();

    keyboardDestroy();
    screenDestroy();
    return 0;
}
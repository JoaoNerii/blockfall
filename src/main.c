/**
 * main.c
 * Programa principal do jogo Tetris
 */

#include "tetris.h"

int main() {

    screenInit(1);
    keyboardInit();
    timerInit(1000);
 
    TetrisGame game;
    initGame(&game);

    gameLoop(&game);
 
    screenGotoxy(SCRSTARTX, SCRSTARTY + BOARD_HEIGHT + 2);
    printf("Pressione qualquer tecla para sair...");
    screenUpdate();
    
    while (!keyhit()) {}
    readch();

    keyboardDestroy();
    screenDestroy();
    
    return 0;
}
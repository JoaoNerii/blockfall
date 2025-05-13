#include "tetris.h"

void initDisplay() {
    screenInit(1);
    keyboardInit();
    screenHideCursor();
    screenClear();
}

void drawBlock(int x, int y, int shape[4][4], int color) {
    for (int dy = 0; dy < 4; dy++) {
        for (int dx = 0; dx < 4; dx++) {
            if (shape[dy][dx]) {
                screenGotoxy(x + dx, y + dy);
                screenSetColor(color, BLACK);
                printf("%c", BOX_BLOCK);
            }
        }
    }
}

void drawBoard(GameState *game) {
    screenBoxEnable();
    for (int x = BOARD_START_X - 1; x < BOARD_START_X + BOARD_WIDTH + 1; x++) {
        screenGotoxy(x, BOARD_START_Y - 1);
        printf("%c", BOX_HLINE);
        screenGotoxy(x, BOARD_START_Y + BOARD_HEIGHT);
        printf("%c", BOX_HLINE);
    }
    
    for (int y = BOARD_START_Y; y < BOARD_START_Y + BOARD_HEIGHT; y++) {
        screenGotoxy(BOARD_START_X - 1, y);
        printf("%c", BOX_VLINE);
        screenGotoxy(BOARD_START_X + BOARD_WIDTH, y);
        printf("%c", BOX_VLINE);
    }
    
    screenGotoxy(BOARD_START_X - 1, BOARD_START_Y - 1);
    printf("%c", BOX_UPLEFT);
    screenGotoxy(BOARD_START_X + BOARD_WIDTH, BOARD_START_Y - 1);
    printf("%c", BOX_UPRIGHT);
    screenGotoxy(BOARD_START_X - 1, BOARD_START_Y + BOARD_HEIGHT);
    printf("%c", BOX_DWNLEFT);
    screenGotoxy(BOARD_START_X + BOARD_WIDTH, BOARD_START_Y + BOARD_HEIGHT);
    printf("%c", BOX_DWNRIGHT);
    screenBoxDisable();
    
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (game->board[y][x]) {
                screenGotoxy(BOARD_START_X + x, BOARD_START_Y + y);
                screenSetColor(game->board[y][x], BLACK);
                printf("%c", BOX_BLOCK);
            }
        }
    }
    
    drawBlock(BOARD_START_X + game->currentBlock.x, 
              BOARD_START_Y + game->currentBlock.y, 
              game->currentBlock.shape, 
              game->currentBlock.type + 1);
}

void drawNextBlock(GameState *game) {
    screenGotoxy(NEXT_BLOCK_X, NEXT_BLOCK_Y);
    screenSetColor(WHITE, BLACK);
    printf("Next Block:");
    
    for (int y = 1; y < 5; y++) {
        for (int x = 0; x < 6; x++) {
            screenGotoxy(NEXT_BLOCK_X + x, NEXT_BLOCK_Y + y);
            printf(" ");
        }
    }
    
    drawBlock(NEXT_BLOCK_X + 1, NEXT_BLOCK_Y + 1, game->nextBlock.shape, game->nextBlock.type + 1);
}

void drawScore(GameState *game) {
    screenGotoxy(NEXT_BLOCK_X, NEXT_BLOCK_Y + 6);
    screenSetColor(WHITE, BLACK);
    printf("Score: %d", game->score);
    
    screenGotoxy(NEXT_BLOCK_X, NEXT_BLOCK_Y + 7);
    printf("Level: %d", game->level);
}

void drawGameOver() {
    screenGotoxy(BOARD_START_X + BOARD_WIDTH/2 - 4, BOARD_START_Y + BOARD_HEIGHT/2);
    screenSetColor(RED, BLACK);
    printf("GAME OVER!");
}

void handleInput(GameState *game) {
    if (keyhit()) {
        int ch = readch();
        
        switch (ch) {
            case KEY_LEFT:
                moveBlock(game, -1, 0);
                break;
            case KEY_RIGHT:
                moveBlock(game, 1, 0);
                break;
            case KEY_DOWN:
                moveBlock(game, 0, 1);
                break;
            case KEY_ROTATE:
                rotateBlock(game);
                break;
            case KEY_PAUSE:
                while (!keyhit()) {}
                readch();
                break;
            case KEY_QUIT:
                game->gameOver = 1;
                break;
        }
    }
}

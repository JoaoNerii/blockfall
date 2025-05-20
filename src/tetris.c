/**
 * tetris.c
 * Implementação do jogo Tetris
 */

#include "tetris.h"
#include <stdlib.h>
#include <time.h>

const int SHAPES[7][4][4] = {
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
 
    {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    {
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};

const screenColor COLORS[7] = {
    CYAN,
    BLUE,
    YELLOW,
    WHITE,
    GREEN,
    MAGENTA,
    RED
};

void initGame(TetrisGame *game) {
    srand(time(NULL));
    
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            game->board[y][x] = 0;
        }
    }
    
    game->score = 0;
    game->level = 1;
    game->gameOver = 0;

    createTetromino(&game->currentPiece, rand() % 7);
    createTetromino(&game->nextPiece, rand() % 7);

    game->currentPiece.x = BOARD_WIDTH / 2 - game->currentPiece.width / 2;
    game->currentPiece.y = 0;
}

void createTetromino(Tetromino *piece, TetrominoType type) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            piece->shape[y][x] = SHAPES[type][y][x];
        }
    }

    piece->width = 0;
    piece->height = 0;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (piece->shape[y][x]) {
                if (x + 1 > piece->width) piece->width = x + 1;
                if (y + 1 > piece->height) piece->height = y + 1;
            }
        }
    }
    
    piece->color = COLORS[type];
}

void drawGame(const TetrisGame *game) {
    screenClear();
    
    drawBoard(game);
    
    drawPiece(&game->currentPiece);

    drawNextPiece(game);

    drawScore(game);
    
    screenUpdate();
}

void drawPiece(const Tetromino *piece) {
    screenSetColor(piece->color, BLACK);
    
    for (int y = 0; y < piece->height; y++) {
        for (int x = 0; x < piece->width; x++) {
            if (piece->shape[y][x]) {
                int screenX = SCRSTARTX + (piece->x + x) * BLOCK_SIZE;
                int screenY = SCRSTARTY + (piece->y + y);
                
                for (int i = 0; i < BLOCK_SIZE; i++) {
                    screenGotoxy(screenX + i, screenY);
                    printf("%c", BOX_BLOCK);
                }
            }
        }
    }
    
    screenSetColor(WHITE, BLACK);
}

void drawBoard(const TetrisGame *game) {
    screenBoxEnable();
    
    screenGotoxy(SCRSTARTX - 1, SCRSTARTY - 1);
    printf("%c", BOX_UPLEFT);
    for (int x = 0; x < BOARD_WIDTH * BLOCK_SIZE; x++) {
        printf("%c", BOX_HLINE);
    }
    printf("%c", BOX_UPRIGHT);
  
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        screenGotoxy(SCRSTARTX - 1, SCRSTARTY + y);
        printf("%c", BOX_VLINE);
        screenGotoxy(SCRSTARTX + BOARD_WIDTH * BLOCK_SIZE, SCRSTARTY + y);
        printf("%c", BOX_VLINE);
    }

    screenGotoxy(SCRSTARTX - 1, SCRSTARTY + BOARD_HEIGHT);
    printf("%c", BOX_DWNLEFT);
    for (int x = 0; x < BOARD_WIDTH * BLOCK_SIZE; x++) {
        printf("%c", BOX_HLINE);
    }
    printf("%c", BOX_DWNRIGHT);
    
    screenBoxDisable();
   
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (game->board[y][x]) {
                screenSetColor(game->board[y][x], BLACK);
                
                int screenX = SCRSTARTX + x * BLOCK_SIZE;
                int screenY = SCRSTARTY + y;
                
                for (int i = 0; i < BLOCK_SIZE; i++) {
                    screenGotoxy(screenX + i, screenY);
                    printf("%c", BOX_BLOCK);
                }
            }
        }
    }
    
    screenSetColor(WHITE, BLACK);
}

void drawNextPiece(const TetrisGame *game) {
    int infoX = SCRSTARTX + BOARD_WIDTH * BLOCK_SIZE + 5;
    int infoY = SCRSTARTY + 2;
    
    screenGotoxy(infoX, infoY++);
    printf("Próxima peça:");
 
    screenSetColor(game->nextPiece.color, BLACK);
    
    for (int y = 0; y < game->nextPiece.height; y++) {
        screenGotoxy(infoX, infoY + y);
        for (int x = 0; x < game->nextPiece.width; x++) {
            if (game->nextPiece.shape[y][x]) {
                printf("%c%c", BOX_BLOCK, BOX_BLOCK);
            } else {
                printf("  ");
            }
        }
    }
    
    screenSetColor(WHITE, BLACK);
}

void drawScore(const TetrisGame *game) {
    int infoX = SCRSTARTX + BOARD_WIDTH * BLOCK_SIZE + 5;
    int infoY = SCRSTARTY + 8;
    
    screenGotoxy(infoX, infoY++);
    printf("Pontuação: %d", game->score);
    
    screenGotoxy(infoX, infoY++);
    printf("Nível: %d", game->level);
    
    if (game->gameOver) {
        screenGotoxy(SCRSTARTX + BOARD_WIDTH * BLOCK_SIZE / 2 - 4, SCRSTARTY + BOARD_HEIGHT / 2);
        screenSetColor(RED, BLACK);
        printf("GAME OVER!");
        screenSetColor(WHITE, BLACK);
    }
}

int movePiece(TetrisGame *game, int dx, int dy) {
    game->currentPiece.x += dx;
    game->currentPiece.y += dy;
    
    if (checkCollision(game)) {
        game->currentPiece.x -= dx;
        game->currentPiece.y -= dy;
        return 0;
    }
    
    return 1;
}

void rotatePiece(TetrisGame *game) {
    Tetromino temp = game->currentPiece;
  
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            game->currentPiece.shape[x][3 - y] = temp.shape[y][x];
        }
    }
    
    game->currentPiece.width = 0;
    game->currentPiece.height = 0;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (game->currentPiece.shape[y][x]) {
                if (x + 1 > game->currentPiece.width) game->currentPiece.width = x + 1;
                if (y + 1 > game->currentPiece.height) game->currentPiece.height = y + 1;
            }
        }
    }
    
    if (checkCollision(game)) {
        game->currentPiece = temp;
    }
}

int checkCollision(const TetrisGame *game) {
    for (int y = 0; y < game->currentPiece.height; y++) {
        for (int x = 0; x < game->currentPiece.width; x++) {
            if (game->currentPiece.shape[y][x]) {
                int boardX = game->currentPiece.x + x;
                int boardY = game->currentPiece.y + y;

                if (boardX < 0 || boardX >= BOARD_WIDTH || boardY >= BOARD_HEIGHT) {
                    return 1;
                }
                
                if (boardY >= 0 && game->board[boardY][boardX]) {
                    return 1;
                }
            }
        }
    }
    
    return 0;
}

void mergePiece(TetrisGame *game) {
    for (int y = 0; y < game->currentPiece.height; y++) {
        for (int x = 0; x < game->currentPiece.width; x++) {
            if (game->currentPiece.shape[y][x]) {
                int boardX = game->currentPiece.x + x;
                int boardY = game->currentPiece.y + y;
                
                if (boardY >= 0) {
                    game->board[boardY][boardX] = game->currentPiece.color;
                }
            }
        }
    }
}

int clearLines(TetrisGame *game) {
    int linesCleared = 0;
    
    for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
        int lineComplete = 1;
    
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (!game->board[y][x]) {
                lineComplete = 0;
                break;
            }
        }

        if (lineComplete) {
            linesCleared++;
   
            for (int yy = y; yy > 0; yy--) {
                for (int x = 0; x < BOARD_WIDTH; x++) {
                    game->board[yy][x] = game->board[yy - 1][x];
                }
            }
           
            for (int x = 0; x < BOARD_WIDTH; x++) {
                game->board[0][x] = 0;
            }
            
            y++;
        }
    }
    
    if (linesCleared > 0) {
        game->score += linesCleared * linesCleared * 100 * game->level;
        
        if (game->score / 1000 > game->level - 1) {
            game->level++;
        }
    }
    
    return linesCleared;
}

void newPiece(TetrisGame *game) {
    game->currentPiece = game->nextPiece;
    
    createTetromino(&game->nextPiece, rand() % 7);
    
    game->currentPiece.x = BOARD_WIDTH / 2 - game->currentPiece.width / 2;
    game->currentPiece.y = 0;
    
    if (checkCollision(game)) {
        game->gameOver = 1;
    }
}

void gameLoop(TetrisGame *game) {
    int speed = 1000 - (game->level - 1) * 100;
    if (speed < 100) speed = 100;
    
    timerUpdateTimer(speed);
    
    while (!game->gameOver) {
        drawGame(game);
        
        if (keyhit()) {
            int ch = readch();
            
            switch (ch) {
                case 'a':
                case 'A':
                    movePiece(game, -1, 0);
                    break;
                    
                case 'd':
                case 'D':
                    movePiece(game, 1, 0);
                    break;
                    
                case 's':
                case 'S':
                    if (!movePiece(game, 0, 1)) {
                        mergePiece(game);
                        clearLines(game);
                        newPiece(game);
                    }
                    break;
                    
                case 'w':
                case 'W':
                    rotatePiece(game);
                    break;
                    
                case ' ':
                    while (movePiece(game, 0, 1)) {
                        drawGame(game);
                    }
                    mergePiece(game);
                    clearLines(game);
                    newPiece(game);
                    break;
                    
                case 'q':
                case 'Q':
                    game->gameOver = 1;
                    break;
            }
        }
        
        if (timerTimeOver()) {
            if (!movePiece(game, 0, 1)) {
                mergePiece(game);
                clearLines(game);
                newPiece(game);
            }
        }
    }
    
    drawGame(game);
}
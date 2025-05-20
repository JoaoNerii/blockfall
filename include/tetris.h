/**
 * tetris.h
 * Definições para o jogo Tetris
 */

#ifndef __TETRIS_H__
#define __TETRIS_H__

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define BLOCK_SIZE 2

typedef struct {
    int shape[4][4];
    int width;
    int height;
    int x;
    int y;
    screenColor color;
} Tetromino;

typedef struct {
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    Tetromino currentPiece;
    Tetromino nextPiece;
    int score;
    int level;
    int gameOver;
} TetrisGame;

typedef enum { I, J, L, O, S, T, Z } TetrominoType;

void initGame(TetrisGame *game);
void drawGame(const TetrisGame *game);
void drawPiece(const Tetromino *piece);
void drawBoard(const TetrisGame *game);
void drawNextPiece(const TetrisGame *game);
void drawScore(const TetrisGame *game);
int movePiece(TetrisGame *game, int dx, int dy);
void rotatePiece(TetrisGame *game);
int checkCollision(const TetrisGame *game);
void mergePiece(TetrisGame *game);
int clearLines(TetrisGame *game);
void newPiece(TetrisGame *game);
void createTetromino(Tetromino *piece, TetrominoType type);
void gameLoop(TetrisGame *game);

#endif /* __TETRIS_H__ */
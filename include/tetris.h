#ifndef __TETRIS_H__
#define __TETRIS_H__

#include "types.h"
#include "keyboard.h"

#define BOARD_START_X 10
#define BOARD_START_Y 2
#define NEXT_BLOCK_X 25
#define NEXT_BLOCK_Y 2

#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_DOWN 's'
#define KEY_ROTATE 'w'
#define KEY_PAUSE 'p'
#define KEY_QUIT 'q'

void initDisplay();
void drawBlock(int x, int y, int shape[4][4], int color);
void drawBoard(GameState *game);
void drawNextBlock(GameState *game);
void drawScore(GameState *game);
void drawGameOver();
void handleInput(GameState *game);

#endif

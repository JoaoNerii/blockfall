#ifndef TETRIS_H
#define TETRIS_H

#include "game.h"
#include <cli-lib.h>

void draw_game(const GameState *game);
void process_input(GameState *game, int key);
void run_game();

#endif

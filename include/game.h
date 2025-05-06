#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define NUM_TETROMINOES 7

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position blocks[4];
    Position rotation_center;
    int color;
    int type;
} Tetromino;

typedef struct {
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    Tetromino current_piece;
    Tetromino next_piece;
    bool game_over;
    int score;
    int level;
} GameState;

void init_game(GameState *game);
Tetromino generate_tetromino();
bool check_collision(const GameState *game, const Tetromino *piece);
bool move_piece(GameState *game, int dx, int dy);
bool rotate_piece(GameState *game);
void lock_piece(GameState *game);
int clear_lines(GameState *game);
void update_game(GameState *game);

#endif

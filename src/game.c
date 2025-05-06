#include "game.h"
#include <stdlib.h>
#include <time.h>

const int TETROMINOES[NUM_TETROMINOES][4][4][2] = {
    {
        {{0, 1}, {1, 1}, {2, 1}, {3, 1}},
        {{2, 0}, {2, 1}, {2, 2}, {2, 3}},
        {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
        {{1, 0}, {1, 1}, {1, 2}, {1, 3}}
    },
    {
        {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
        {{1, 0}, {1, 1}, {1, 2}, {0, 2}},
        {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
        {{1, 0}, {1, 1}, {1, 2}, {2, 0}}
    },
    {
        {{0, 1}, {1, 1}, {2, 1}, {2, 0}},
        {{1, 0}, {1, 1}, {1, 2}, {0, 0}},
        {{0, 1}, {1, 1}, {2, 1}, {0, 2}},
        {{1, 0}, {1, 1}, {1, 2}, {2, 2}}
    },
    {
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}}
    },
    {
        {{1, 0}, {2, 0}, {0, 1}, {1, 1}},
        {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
        {{1, 1}, {2, 1}, {0, 2}, {1, 2}},
        {{1, 0}, {1, 1}, {2, 1}, {2, 2}}
    },
    {
        {{0, 1}, {1, 1}, {2, 1}, {1, 0}},
        {{1, 0}, {1, 1}, {1, 2}, {0, 1}},
        {{0, 1}, {1, 1}, {2, 1}, {1, 2}},
        {{1, 0}, {1, 1}, {1, 2}, {2, 1}}
    },
    {
        {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
        {{1, 0}, {1, 1}, {0, 1}, {0, 2}},
        {{0, 1}, {1, 1}, {1, 2}, {2, 2}},
        {{2, 0}, {2, 1}, {1, 1}, {1, 2}}
    }
};

void init_game(GameState *game) {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            game->board[y][x] = 0;
        }
    }
    
    game->game_over = false;
    game->score = 0;
    game->level = 1;
    
    srand(time(NULL));
    
    game->current_piece = generate_tetromino();
    game->next_piece = generate_tetromino();
}

Tetromino generate_tetromino() {
    Tetromino piece;
    piece.type = rand() % NUM_TETROMINOES;
    piece.color = piece.type + 1;
    
    int start_x = BOARD_WIDTH / 2 - 2;
    int start_y = 0;
    
    for (int i = 0; i < 4; i++) {
        piece.blocks[i].x = TETROMINOES[piece.type][0][i][0] + start_x;
        piece.blocks[i].y = TETROMINOES[piece.type][0][i][1] + start_y;
    }
    
    piece.rotation_center.x = start_x + 1;
    piece.rotation_center.y = start_y + 1;
    
    return piece;
}

bool check_collision(const GameState *game, const Tetromino *piece) {
    for (int i = 0; i < 4; i++) {
        int x = piece->blocks[i].x;
        int y = piece->blocks[i].y;
        
        if (x < 0 || x >= BOARD_WIDTH || y >= BOARD_HEIGHT) {
            return true;
        }
        
        if (y >= 0 && game->board[y][x] != 0) {
            return true;
        }
    }
    return false;
}

bool move_piece(GameState *game, int dx, int dy) {
    Tetromino moved_piece = game->current_piece;
    
    for (int i = 0; i < 4; i++) {
        moved_piece.blocks[i].x += dx;
        moved_piece.blocks[i].y += dy;
    }
    moved_piece.rotation_center.x += dx;
    moved_piece.rotation_center.y += dy;
    
    if (!check_collision(game, &moved_piece)) {
        game->current_piece = moved_piece;
        return true;
    }
    
    return false;
}

bool rotate_piece(GameState *game) {
    Tetromino rotated_piece = game->current_piece;
    int cx = rotated_piece.rotation_center.x;
    int cy = rotated_piece.rotation_center.y;
    
    for (int i = 0; i < 4; i++) {
        int x = rotated_piece.blocks[i].x - cx;
        int y = rotated_piece.blocks[i].y - cy;
        
        rotated_piece.blocks[i].x = cx + y;
        rotated_piece.blocks[i].y = cy - x;
    }
    
    if (!check_collision(game, &rotated_piece)) {
        game->current_piece = rotated_piece;
        return true;
    }
    
    return false;
}

void lock_piece(GameState *game) {
    for (int i = 0; i < 4; i++) {
        int x = game->current_piece.blocks[i].x;
        int y = game->current_piece.blocks[i].y;
        
        if (y >= 0) {
            game->board[y][x] = game->current_piece.color;
        }
    }
    
    for (int i = 0; i < 4; i++) {
        if (game->current_piece.blocks[i].y < 0) {
            game->game_over = true;
            break;
        }
    }
    
    game->current_piece = game->next_piece;
    game->next_piece = generate_tetromino();
}

int clear_lines(GameState *game) {
    int lines_cleared = 0;
    
    for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
        bool line_complete = true;
        
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (game->board[y][x] == 0) {
                line_complete = false;
                break;
            }
        }
        
        if (line_complete) {
            lines_cleared++;
            
            for (int ny = y; ny > 0; ny--) {
                for (int x = 0; x < BOARD_WIDTH; x++) {
                    game->board[ny][x] = game->board[ny-1][x];
                }
            }
            
            for (int x = 0; x < BOARD_WIDTH; x++) {
                game->board[0][x] = 0;
            }
            
            y++;
        }
    }
    
    if (lines_cleared > 0) {
        game->score += lines_cleared * lines_cleared * 100 * game->level;
        
        static int total_lines = 0;
        total_lines += lines_cleared;
        game->level = total_lines / 10 + 1;
    }
    
    return lines_cleared;
}

void update_game(GameState *game) {
    if (!move_piece(game, 0, 1)) {
        lock_piece(game);
        clear_lines(game);
    }
}

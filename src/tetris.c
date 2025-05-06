#include "tetris.h"
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define BOARD_OFFSET_X 5
#define BOARD_OFFSET_Y 2
#define BLOCK_SIZE 2

void draw_game(const GameState *game) {
    cli_clear();
    
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (game->board[y][x] != 0) {
                cli_set_color(game->board[y][x]);
                cli_draw_rect(BOARD_OFFSET_X + x * BLOCK_SIZE, 
                             BOARD_OFFSET_Y + y, 
                             BLOCK_SIZE, 1, true);
                cli_reset_color();
            }
        }
    }
    
    cli_set_color(game->current_piece.color);
    for (int i = 0; i < 4; i++) {
        int x = game->current_piece.blocks[i].x;
        int y = game->current_piece.blocks[i].y;
        
        if (y >= 0) {
            cli_draw_rect(BOARD_OFFSET_X + x * BLOCK_SIZE, 
                         BOARD_OFFSET_Y + y, 
                         BLOCK_SIZE, 1, true);
        }
    }
    cli_reset_color();
    
    cli_set_color(CLI_WHITE);
    cli_draw_rect(BOARD_OFFSET_X - 1, BOARD_OFFSET_Y - 1, 
                 BOARD_WIDTH * BLOCK_SIZE + 2, BOARD_HEIGHT + 2, false);
    
    cli_move_cursor(BOARD_OFFSET_X + BOARD_WIDTH * BLOCK_SIZE + 5, BOARD_OFFSET_Y);
    printf("Score: %d", game->score);
    
    cli_move_cursor(BOARD_OFFSET_X + BOARD_WIDTH * BLOCK_SIZE + 5, BOARD_OFFSET_Y + 2);
    printf("Level: %d", game->level);
    
    cli_move_cursor(BOARD_OFFSET_X + BOARD_WIDTH * BLOCK_SIZE + 5, BOARD_OFFSET_Y + 4);
    printf("Next:");
    
    for (int i = 0; i < 4; i++) {
        int x = game->next_piece.blocks[i].x - (BOARD_WIDTH / 2 - 2);
        int y = game->next_piece.blocks[i].y + 6;
        
        cli_set_color(game->next_piece.color);
        cli_draw_rect(BOARD_OFFSET_X + BOARD_WIDTH * BLOCK_SIZE + 5 + x * BLOCK_SIZE, 
                     BOARD_OFFSET_Y + y, 
                     BLOCK_SIZE, 1, true);
    }
    cli_reset_color();
    
    cli_refresh();
}

void process_input(GameState *game, int key) {
    switch (key) {
        case 'a':
            move_piece(game, -1, 0);
            break;
        case 'd':
            move_piece(game, 1, 0);
            break;
        case 's':
            move_piece(game, 0, 1);
            break;
        case 'w':
            rotate_piece(game);
            break;
        case ' ':
            while (move_piece(game, 0, 1)) {
                game->score++;
            }
            lock_piece(game);
            clear_lines(game);
            break;
    }
}

void run_game() {
    GameState game;
    init_game(&game);
    
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
    
    cli_init();
    cli_hide_cursor();
    
    int frame_count = 0;
    int frames_per_drop = 30;
    
    while (!game.game_over) {
        int key = getchar();
        if (key != EOF) {
            process_input(&game, key);
        }
        
        if (frame_count % (frames_per_drop / game.level) == 0) {
            update_game(&game);
        }
        
        draw_game(&game);
        
        usleep(1000000 / 60);
        frame_count++;
    }
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    cli_move_cursor(BOARD_OFFSET_X + BOARD_WIDTH / 2 - 5, BOARD_OFFSET_Y + BOARD_HEIGHT / 2);
    printf("GAME OVER!");
    cli_move_cursor(BOARD_OFFSET_X + BOARD_WIDTH / 2 - 8, BOARD_OFFSET_Y + BOARD_HEIGHT / 2 + 1);
    printf("Final Score: %d", game.score);
    cli_refresh();
    
    sleep(3);
    
    cli_show_cursor();
    cli_end();
}

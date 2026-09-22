// game.c

#include "Game.h"

int** board;

// Function to initialize the board with a given size
void initialize_board() {
    board = (int**)malloc(BOARD_SIZE_X * sizeof(int*));
    for (int i = 0; i < BOARD_SIZE_X; i++) {
        board[i] = (int*)malloc(BOARD_SIZE_Y * sizeof(int));
    }
    for (int x = 0; x < BOARD_SIZE_X; ++x) {
        for (int y = 0; y < BOARD_SIZE_Y; ++y) {
            if ((x == BOARD_SIZE_X / 2 || x == BOARD_SIZE_X / 2 - 1) &&
                (y == BOARD_SIZE_Y / 2 || y == BOARD_SIZE_Y / 2 - 1)) {
                // Place initial 0 and 1
                board[x][y] = (x + y) % 2;
            } else {
                // Empty cells elsewhere
                board[x][y] = 2;
            }
        }
    }
}

void free_board() {
    for (int i = 0; i < BOARD_SIZE_X; i++) {
        free(board[i]);
    }
    free(board);
}

int isBlackStone = 1;
int black_stone_count = 0;
int white_stone_count = 0;
int player_gave_up_boolean = 0;

int winner = -1;

int all_places_occupied() {
    for (int x = 0; x < BOARD_SIZE_X; ++x) {
        for (int y = 0; y < BOARD_SIZE_Y; ++y) {
            if (board[x][y] == 2) {
                return 0;  // If any place is unoccupied, return 0
            }
        }
    }
    return 1;  // All places are occupied so return 1
}

int count_stones(int player) {
    int count = 0;
    for (int x = 0; x < BOARD_SIZE_X; ++x) {
        for (int y = 0; y < BOARD_SIZE_Y; ++y) {
            if (board[x][y] == player) {
                count++;
            }
        }
    }
    return count;
}

void determine_winner_and_check_give_up() {
    // Check if a player gave up
    if (player_gave_up_boolean == 1) {
        if (isBlackStone == 0) {
            winner = 1;  // Black wins
        } else if (isBlackStone == 1) {
            winner = 0;  // White wins
        }
    } else if (all_places_occupied() == 1) {
        // Determine the winner based on stone counts
        if (black_stone_count > white_stone_count) {
            winner = 1;  // Black wins
        } else if (black_stone_count < white_stone_count) {
            winner = 0;  // White wins
        } else {
            winner = 2;  // Draw
        }
    } else {
        winner = -1;  // Game in progress
    }
}


void checkAndUpdateBoard() {
    // Check horizontally and vertically
    for (int x = 0; x < BOARD_SIZE_X; ++x) {
        for (int y = 0; y < BOARD_SIZE_Y; ++y) {
            // Check horizontally
            if (y > 0 && y < BOARD_SIZE_Y - 2 && board[x][y] == 1 && board[x][y + 1] == 0 && board[x][y + 2] == 1) {
                board[x][y + 1] = 1;
            }

            // Check vertically
            if (x > 0 && x < BOARD_SIZE_X - 2 && board[x][y] == 1 && board[x + 1][y] == 0 && board[x + 2][y] == 1) {
                board[x + 1][y] = 1;
            }
        }
    }
    for (int x = 0; x < BOARD_SIZE_X; ++x) {
        for (int y = 0; y < BOARD_SIZE_Y; ++y) {
            // Check horizontally
            if (y > 0 && y < BOARD_SIZE_Y - 2 && board[x][y] == 0 && board[x][y + 1] == 1 && board[x][y + 2] == 0) {
                board[x][y + 1] = 0;
            }

            // Check vertically
            if (x > 0 && x < BOARD_SIZE_X - 2 && board[x][y] == 0 && board[x + 1][y] == 1 && board[x + 2][y] == 0) {
                board[x + 1][y] = 0;
            }
        }
    }
    // Check diagonally
    for (int x = 0; x < BOARD_SIZE_X; ++x) {
        for (int y = 0; y < BOARD_SIZE_Y; ++y) {
            // Check diagonally (up-left to down-right)
            if (x > 0 && y > 0 && x < BOARD_SIZE_X - 2 && y < BOARD_SIZE_Y - 2 &&
                board[x][y] == 0 && board[x + 1][y + 1] == 1 && board[x + 2][y + 2] == 0) {
                board[x + 1][y + 1] = 0;
            }

            // Check diagonally (up-right to down-left)
            if (x > 0 && y < BOARD_SIZE_Y - 2 && x < BOARD_SIZE_X - 2 && y > 0 &&
                board[x][y] == 0 && board[x + 1][y - 1] == 1 && board[x + 2][y - 2] == 0) {
                board[x + 1][y - 1] = 0;
            }
        }
    }

    // Check horizontally and vertically again for possible additional cases
    for (int x = 0; x < BOARD_SIZE_X; ++x) {
        for (int y = 0; y < BOARD_SIZE_Y; ++y) {
            // Check horizontally
            if (y > 0 && y < BOARD_SIZE_Y - 2 && board[x][y] == 0 && board[x][y + 1] == 1 && board[x][y + 2] == 0) {
                board[x][y + 1] = 0;
            }

            // Check vertically
            if (x > 0 && x < BOARD_SIZE_X - 2 && board[x][y] == 0 && board[x + 1][y] == 1 && board[x + 2][y] == 0) {
                board[x + 1][y] = 0;
            }
        }
    }

    // Check diagonally
    for (int x = 0; x < BOARD_SIZE_X; ++x) {
        for (int y = 0; y < BOARD_SIZE_Y; ++y) {
            // Check diagonally (up-left to down-right)
            if (x > 0 && y > 0 && x < BOARD_SIZE_X - 2 && y < BOARD_SIZE_Y - 2 &&
                board[x][y] == 1 && board[x + 1][y + 1] == 0 && board[x + 2][y + 2] == 1) {
                board[x + 1][y + 1] = 1;
            }

            // Check diagonally (up-right to down-left)
            if (x > 0 && y < BOARD_SIZE_Y - 2 && x < BOARD_SIZE_X - 2 && y > 0 &&
                board[x][y] == 1 && board[x + 1][y - 1] == 0 && board[x + 2][y - 2] == 1) {
                board[x + 1][y - 1] = 1;
            }
        }
    }

    // Check horizontally and vertically again for possible additional cases
    for (int x = 0; x < BOARD_SIZE_X; ++x) {
        for (int y = 0; y < BOARD_SIZE_Y; ++y) {
            // Check horizontally
            if (y > 0 && y < BOARD_SIZE_Y - 2 && board[x][y] == 1 && board[x][y + 1] == 0 && board[x][y + 2] == 1) {
                board[x][y + 1] = 1;
            }

            // Check vertically
            if (x > 0 && x < BOARD_SIZE_X - 2 && board[x][y] == 1 && board[x + 1][y] == 0 && board[x + 2][y] == 1) {
                board[x + 1][y] = 1;
            }
        }
    }
    black_stone_count = count_stones(1);
    white_stone_count = count_stones(0);

    // Determine winner (or if it's a draw)
    determine_winner_and_check_give_up();
}

// Function to save the game state
void save_game_state(const char *filename, int player_turn, int **board, int board_size_x, int board_size_y) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing: %s\n", filename);
        return;
    }

    // Write board dimensions
    fprintf(file, "%d %d\n", board_size_x, board_size_y);

    // Write player turn
    fprintf(file, "%d\n", player_turn);

    // Write board state
    for (int x = 0; x < board_size_x; ++x) {
        for (int y = 0; y < board_size_y; ++y) {
            fprintf(file, "%d", board[x][y]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
void load_game_state(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for reading: %s\n", filename);
        return;
    }

    // Read board dimensions
    fscanf(file, "%d %d", &BOARD_SIZE_X, &BOARD_SIZE_Y);

    // Read player turn
    fscanf(file, "%d", &isBlackStone);


    initialize_board();

    // Read board state
    for (int x = 0; x < BOARD_SIZE_X; ++x) {
        for (int y = 0; y < BOARD_SIZE_Y; ++y) {
            fscanf(file, "%d", &board[x][y]);
        }
    }

    fclose(file);
}



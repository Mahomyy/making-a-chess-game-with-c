#ifndef Game_H_
#define Game_H_

#include <stdio.h>
#include <stdlib.h>

/*
 * Importeert de nodige functies uit SDL2.
 */
#include <SDL2/SDL.h>


extern int isBlackStone;
extern int** board;
extern int BOARD_SIZE_X;
extern int BOARD_SIZE_Y;
extern int player_gave_up_boolean;
extern int winner;


void load_game_state(const char *filename);
void initialize_board();
void save_game_state(const char *filename, int player_turn, int **board, int board_size_x, int board_size_y);
void checkAndUpdateBoard();
void free_board();


#endif /* Game_H_ */

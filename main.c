#include "GUI.h"
#include "Game.h"
#include <SDL2/SDL.h>


int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            // Handling height argument
            if (i + 1 < argc) {
                BOARD_SIZE_Y = atoi(argv[i + 1]);
                i++;  // Move to the next argument
            } else {
                printf("Error: Missing value for height argument.\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-w") == 0) {
            // Handling width argument
            if (i + 1 < argc) {
                BOARD_SIZE_X = atoi(argv[i + 1]);
                i++;  // Move to the next argument
            } else {
                printf("Error: Missing value for width argument.\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            // Loading game state from file
            load_game_state(argv[i + 1]);
            i++;  // Move to the next argument
        } else {
            // Unknown argument
            printf("Error: Unknown argument %s.\n", argv[i]);
            return 1;
        }
    }

    initialize_board();
    initialize_gui();


    SDL_Surface *sample_image_surface = SDL_LoadBMP("Images/empty.bmp");
    if (sample_image_surface == NULL) {
        printf("Error loading image: %s\n", SDL_GetError());
        free_gui();
        return 1;
    }

    SDL_Texture *sample_image_texture = SDL_CreateTextureFromSurface(renderer, sample_image_surface);
    if (sample_image_texture == NULL) {
        printf("Error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(sample_image_surface);
        free_gui();
        return 1;

    }

    SDL_FreeSurface(sample_image_surface);


    while (should_continue) {
        save_game_state("game_state.txt", isBlackStone, board, BOARD_SIZE_X, BOARD_SIZE_Y);
        read_input();
        clear_window();
        checkAndUpdateBoard();
        draw_window();
    }


    // Free resources
    SDL_DestroyTexture(sample_image_texture);
    free_gui();
    free_board();
    return 0;
}

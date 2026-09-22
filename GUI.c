#include "GUI.h"
#include "Game.h"

// Define default board dimensions
#define DEFAULT_WIDTH 8
#define DEFAULT_HEIGHT 8

// Declare board dimensions
int BOARD_SIZE_X = DEFAULT_WIDTH;
int BOARD_SIZE_Y = DEFAULT_HEIGHT;

#define IMAGE_HEIGHT 50
#define IMAGE_WIDTH 50

#define WINDOW_HEIGHT (IMAGE_HEIGHT * BOARD_SIZE_Y)
#define WINDOW_WIDTH (IMAGE_WIDTH * BOARD_SIZE_X)

SDL_Renderer *renderer;

static SDL_Texture *black_stone_texture = NULL;
static SDL_Texture *white_stone_texture = NULL;
static SDL_Texture *empty_stone_texture = NULL;


static SDL_Window *window;

int mouse_x = 300;
int mouse_y = 250;


int should_continue = 1;

int is_relevant_event(SDL_Event *event) {
    if (event == NULL) {
        return 0;
    }
    return  (event->type == SDL_MOUSEBUTTONDOWN) ||
            (event->type == SDL_KEYDOWN) ||
            (event->type == SDL_QUIT);
}

void read_input() {
    SDL_Event event;

    while (!SDL_PollEvent(&event) || !is_relevant_event(&event)) {}

    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_o) {
            isBlackStone = !isBlackStone;
        } else if (event.key.keysym.sym == SDLK_q) {
            player_gave_up_boolean = 1;
        }
    } else if (event.type == SDL_QUIT) {
        should_continue = 0;
    } else  if (event.type == SDL_MOUSEBUTTONDOWN) {
        int clicked_x = event.button.x;
        int clicked_y = event.button.y;
        clicked_x -= clicked_x % IMAGE_WIDTH;
        clicked_y -= clicked_y % IMAGE_HEIGHT;

        // Checking if the click is within ±50 pixels horizontally or vertically
        int x_diff = abs(clicked_x - mouse_x);
        int y_diff = abs(clicked_y - mouse_y);



       // Toggling the color only if the position was empty
        if ((x_diff == IMAGE_WIDTH && y_diff == 0) ||
            (x_diff == 0 && y_diff == IMAGE_HEIGHT) ||
            (x_diff == IMAGE_WIDTH && y_diff == IMAGE_HEIGHT)) {
            // Updating the board if the clicked position is empty
            if (board[clicked_x / IMAGE_WIDTH][clicked_y / IMAGE_HEIGHT] == 2) {
                // Updating the board with the stone color (1 for black, 0 for white)
                board[clicked_x / IMAGE_WIDTH][clicked_y / IMAGE_HEIGHT] = isBlackStone ? 1 : 0;
                checkAndUpdateBoard();  // Updating the board after placing a stone
                isBlackStone = !isBlackStone;  // Toggle the color
            }
        }
// Updating the mouse position
        mouse_x = clicked_x;
        mouse_y = clicked_y;


    }}

void clear_window() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderClear(renderer);
    // Loading the image
    SDL_Surface *sample_image_surface = SDL_LoadBMP("Images/empty.bmp");
    SDL_Texture *sample_image_texture = SDL_CreateTextureFromSurface(renderer, sample_image_surface);

    SDL_FreeSurface(sample_image_surface);

    // Drawing the empty stone texture to fill the window
    draw_images_on_window(sample_image_texture, IMAGE_WIDTH, IMAGE_HEIGHT);
}


void draw_rectangle(SDL_Texture *image, int x, int y, int width, int height) {
    SDL_Rect rectangle = { x, y, width, height };
    /* Tekent de afbeelding op die plaats. */
    SDL_RenderCopy(renderer, image, NULL, &rectangle);
}

void draw_window() {
    clear_window();

    for (int x = 0; x < BOARD_SIZE_X; ++x) {
        for (int y = 0; y < BOARD_SIZE_Y; ++y) {
            if (board[x][y] == 1) {
                // Draw black stone
                draw_rectangle(black_stone_texture, x * IMAGE_WIDTH, y * IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT);
            } else if (board[x][y] == 0) {
                // Draw white stone
                draw_rectangle(white_stone_texture, x * IMAGE_WIDTH, y * IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT);
            }
            // Draw empty place
            if (board[x][y] == 2) {
                // Drawing something to represent an empty place
                SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
                draw_rectangle(empty_stone_texture, x * IMAGE_WIDTH, y * IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT);
            }
        }
    }

    // Display winner information
    if (winner == 0) {
        draw_rectangle(white_stone_texture, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    } else if (winner == 1) {
        draw_rectangle(black_stone_texture, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    } else if (winner == 2) {
        draw_rectangle(empty_stone_texture, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    }

    // Update the window
    SDL_RenderPresent(renderer);
}


void initialize_window(const char *title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error while initializing SDL: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow(title, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Error: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
}

void initialize_textures() {

    SDL_Surface *black_stone_surface = SDL_LoadBMP("Images/black.bmp");
    SDL_Surface *white_stone_surface = SDL_LoadBMP("Images/white.bmp");

    black_stone_texture = SDL_CreateTextureFromSurface(renderer, black_stone_surface);
    white_stone_texture = SDL_CreateTextureFromSurface(renderer, white_stone_surface);

    SDL_FreeSurface(black_stone_surface);
    SDL_FreeSurface(white_stone_surface);

}

void initialize_gui() {
    initialize_window("Othello");
    initialize_textures();
}

void draw_images_on_window(SDL_Texture *image, int cell_width, int cell_height) {
    for (int x = 0; x < BOARD_SIZE_X; ++x) {
        for (int y = 0; y < BOARD_SIZE_Y; ++y) {
            draw_rectangle(image, x * cell_width, y * cell_height, cell_width, cell_height);
        }
    }
}

void free_gui() {
    /* Dealloceert de ingeladen afbeelding. */
    SDL_DestroyTexture(black_stone_texture);
    /* Dealloceert de renderer. */
    SDL_DestroyRenderer(renderer);
    /* Dealloceert het venster. */
    SDL_DestroyWindow(window);
    /* Stopt SDL. */
    SDL_Quit();
}


#ifndef GUI_H_
#define GUI_H_

#include <stdio.h>
#include <stdlib.h>

/*
 * Importeert de nodige functies uit SDL2.
 */
#include <SDL2/SDL.h>

/*
 * De hoogte en breedte van het venster (in pixels).
 * Deze dimensies zijn arbitrair gekozen. Deze dimensies hangen mogelijk af van de grootte van het speelveld.
 */
#define DEFAULT_WIDTH 8
#define DEFAULT_HEIGHT 8


/*
 * De hoogte en breedte (in pixels) van de afbeeldingen voor de vakjes in het speelveld die getoond worden.
 * Als je andere afbeelding wil gebruiken in je GUI, zorg er dan voor dat deze
 * dimensies ook aangepast worden.
 */



extern SDL_Renderer *renderer;

int should_continue;
void initialize_gui();
void draw_window();
void free_gui();
void read_input();
void draw_images_on_window(SDL_Texture *image, int image_width, int image_height);
void clear_window();


#endif /* GUI_H_ */

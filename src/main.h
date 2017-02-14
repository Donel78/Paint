#ifndef MAIN_H
#define MAIN_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <pthread.h>
#include <SDL/SDL.h>

//global
extern pthread_t handler;
extern GtkToggleButton *activeButton; 
extern SDL_Surface *paint;

//paint function
void *draw();
void *rubber();

//signal function
G_MODULE_EXPORT void drawSignal (GtkToggleButton *drawButton);
G_MODULE_EXPORT void togglebutton2 (GtkToggleButton *togglebutton2);
G_MODULE_EXPORT void togglebutton2 (GtkToggleButton *rubberButton);

//sdl_function
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
#endif

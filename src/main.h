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
void *draw(void *arg);

//signal function
G_MODULE_EXPORT void drawSignal (GtkToggleButton *drawButton, GtkWidget *fenetre_principale);
G_MODULE_EXPORT void togglebutton2 (GtkToggleButton *togglebutton2, GtkWidget *fenetre_principale);

#endif

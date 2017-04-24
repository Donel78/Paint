#ifndef MAIN_H
#define MAIN_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <pthread.h>
#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <X11/Xlib.h>
#include <math.h>

//global
extern pthread_t handler;
extern GtkToggleButton *activeButton; 
extern GtkToggleButton *activeButton2; 
extern SDL_Surface *paint;
extern SDL_Surface *tabsdl[1000];
extern GdkRGBA *color;
extern int taille;
extern int nosdl;

//paint function
void  *draw();
void *rubber();
void *text();
void *filling();
void *mySelect();
void _filling(int x, int y, Uint32 mypix, Uint32 couleur);
void *load(char *image_path);
void *save(char *save_path);
void white_black();
void no_filter();
void *getcolor();

void *swag();
void *rect();
void *circle();
void *croix();
void *droite();
void *triangle();


//sdl_function
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

//stack_function
struct Stack{
  int data;
  struct Stack *previous;
};
int stack_is_empty(struct Stack *stack);
void stack_push(struct Stack **s_stack, int data);
int stack_pop(struct Stack **s_stack);
void stack_clear(struct Stack **s_stack);
#endif

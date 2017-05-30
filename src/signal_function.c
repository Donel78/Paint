#include "main.h"

GtkToggleButton *activeButton = NULL;
GtkToggleButton *activeButton2 = NULL;
pthread_t handler;
SDL_Surface *tabsdl[1000]; 
SDL_Surface *paint; 
GdkRGBA *color;
int taille = 0;
int nosdl;


void negSignal()
{
   neg_filter();
}

void rotagSignal()
{
  SDL_Rect rect;
  SDL_Surface *image = NULL;
  SDL_SaveBMP(paint,"tmpimage/rot.bmp");
  image = SDL_LoadBMP("tmpimage/rot.bmp");
  double angle = 90;
  SDL_Surface *rotation = NULL;
  SDL_FillRect(paint,NULL,SDL_MapRGB(paint->format, 255,255,255));
  rotation = rotozoomSurface(image,angle,1.0,1);
  rect.x = 400 - rotation->w / 2;
  rect.y = 200 - rotation->h / 2;
  SDL_BlitSurface(rotation,NULL,paint, &rect);
  SDL_Flip(paint);
}

void rotadSignal()
{
  SDL_Rect rect;
  SDL_Surface *image = NULL;
  SDL_SaveBMP(paint,"tmpimage/rot.bmp");
  image = SDL_LoadBMP("tmpimage/rot.bmp");
  double angle = -90;
  SDL_Surface *rotation = NULL;
  SDL_FillRect(paint,NULL,SDL_MapRGB(paint->format, 255,255,255));
  rotation = rotozoomSurface(image,angle,1.0,1);
  rect.x = 400 - rotation->w / 2;
  rect.y = 200 - rotation->h / 2;
  SDL_BlitSurface(rotation,NULL,paint, &rect);
  SDL_Flip(paint);
}

void quitSignal()
{
  gtk_main_quit();
}

void drawSignal (GtkToggleButton *drawButton)
{
  int e;
  if (gtk_toggle_button_get_active(drawButton) == 1)
  {
    if (activeButton != NULL && activeButton != drawButton) 
      gtk_toggle_button_set_active(activeButton, 0);
    activeButton = drawButton;
    e = pthread_create(&handler, NULL, draw, NULL);
    if (e != 0)
      abort();
  }
  else
  {
    pthread_cancel(handler);
  }
}

void fillingSignal (GtkToggleButton *fillingButton)
{
  int e;
  if (gtk_toggle_button_get_active(fillingButton) == 1)
  {
    if (activeButton != NULL && activeButton != fillingButton) 
      gtk_toggle_button_set_active(activeButton, 0);
    activeButton = fillingButton;
    e = pthread_create(&handler, NULL, filling, NULL);
    if (e != 0)
      abort();
  }
  else
  {
    pthread_cancel(handler);
  }
}


void textSignal (GtkToggleButton *textButton)
{
  int e;
  if (gtk_toggle_button_get_active(textButton) == 1)
  {
    if (activeButton != NULL && activeButton != textButton) 
      gtk_toggle_button_set_active(activeButton, 0);
    activeButton = textButton;
    e = pthread_create(&handler, NULL, text, NULL);
    if (e != 0)
      abort();
  }
  else
  {
       pthread_cancel(handler);
  }
}


void rubberSignal (GtkToggleButton *rubberButton)
{
  int e = 0;
  if (gtk_toggle_button_get_active(rubberButton) == 1)
  {
    if (activeButton != NULL && activeButton != rubberButton) 
      gtk_toggle_button_set_active(activeButton, 0);
    activeButton = rubberButton;
    e = pthread_create(&handler, NULL, rubber, NULL);
    if (e != 0)
      abort();
  }
  else
  {
       pthread_cancel(handler);
  }
}

void loadimageSignal(GtkFileChooserButton *loadimage)
{
  char *image_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(loadimage));
  load(image_path);
}

void saveimageSignal(gpointer data)
{

  GtkWidget *pSave=NULL;
  pSave = gtk_file_chooser_dialog_new ("Save File as ...",
      GTK_WINDOW(data),
      GTK_FILE_CHOOSER_ACTION_SAVE,
      "annuler", GTK_RESPONSE_CANCEL,
      "enregistrer", GTK_RESPONSE_ACCEPT,
      NULL);
  gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (pSave), TRUE);
  gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (pSave), "Untitled.");



  if (gtk_dialog_run (GTK_DIALOG (pSave)) == GTK_RESPONSE_ACCEPT)
  {
    char *pathname;
    pathname = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (pSave));
    save(pathname);
  }

  gtk_widget_destroy (pSave);
}
void colorSignal(GtkColorChooser *ChooserColor)
{
  color = malloc(sizeof (GdkRGBA));
  gtk_color_chooser_get_rgba(ChooserColor,color);
  color->red = color->red * 255;
  color->blue = color->blue * 255;
  color->green = color->green * 255;

}
void backSignal()
{
  SDL_Rect position;
  position.x = 0;
  position.y = 0;
  //printf("%d\n",nosdl);
  if (nosdl <= 0)
  {
    return;
  }
  else
  {
  nosdl--;
  SDL_BlitSurface(tabsdl[nosdl - 1], NULL, paint, &position);
  SDL_Flip(paint);
  }
}


void fowardSignal()
{
  SDL_Rect position;
  position.x = 0;
  position.y = 0;
//  printf("%d\n",nosdl);
  if (tabsdl[nosdl] == NULL)
  {
    return;
  }
  else
  {
  nosdl++;
  SDL_BlitSurface(tabsdl[nosdl - 1], NULL, paint, &position);
  SDL_Flip(paint);
  }
}

void selectSignal (GtkToggleButton *selectButton)
{
  int e = 0;
  if (gtk_toggle_button_get_active(selectButton) == 1)
  {
    if (activeButton != NULL && activeButton != selectButton) 
      gtk_toggle_button_set_active(activeButton, 0);
    activeButton = selectButton;
    e = pthread_create(&handler, NULL, mySelect, NULL);
    if (e != 0)
      abort();
  }
  else
  {
       pthread_cancel(handler);
  }
}

void droiteSignal (GtkToggleButton *droiteButton)
{
  int e;
  if (gtk_toggle_button_get_active(droiteButton) == 1)
  {
    if (activeButton != NULL && activeButton != droiteButton) 
      gtk_toggle_button_set_active(activeButton, 0);
    activeButton = droiteButton;
    e = pthread_create(&handler, NULL, droite, NULL);
    if (e != 0)
      abort();
  }
  else
  {
    pthread_cancel(handler);
  }
}

void swagSignal (GtkToggleButton *swagButton)
{
  int e = 0;
  if (gtk_toggle_button_get_active(swagButton) == 1)
  {
    if (activeButton != NULL && activeButton != swagButton) 
      gtk_toggle_button_set_active(activeButton, 0);
    activeButton = swagButton;
    e = pthread_create(&handler, NULL, swag, NULL);
    if (e != 0)
      abort();
  }
  else
  {
       pthread_cancel(handler);
  }
}
void rectangleSignal (GtkToggleButton *rectangleButton)
{
  int e = 0;
  if (gtk_toggle_button_get_active(rectangleButton) == 1)
  {
    if (activeButton != NULL && activeButton != rectangleButton) 
      gtk_toggle_button_set_active(activeButton, 0);
    activeButton = rectangleButton;
    e = pthread_create(&handler, NULL, rect, NULL);
    if (e != 0)
      abort();
  }
  else
  {
       pthread_cancel(handler);
  }
}

void croixSignal (GtkToggleButton *croixButton)
{
  int e = 0;
  if (gtk_toggle_button_get_active(croixButton) == 1)
  {
    if (activeButton != NULL && activeButton != croixButton) 
      gtk_toggle_button_set_active(activeButton, 0);
    activeButton = croixButton;
    e = pthread_create(&handler, NULL, croix, NULL);
    if (e != 0)
      abort();
  }
  else
  {
       pthread_cancel(handler);
  }
}


void triangleSignal (GtkToggleButton *triangleButton)
{
  int e = 0;
  if (gtk_toggle_button_get_active(triangleButton) == 1)
  {
    if (activeButton != NULL && activeButton != triangleButton) 
      gtk_toggle_button_set_active(activeButton, 0);
    activeButton = triangleButton;
    e = pthread_create(&handler, NULL, triangle, NULL);
    if (e != 0)
      abort();
  }
  else
  {
       pthread_cancel(handler);
  }
}

void rondSignal (GtkToggleButton *rondButton)
{
  int e = 0;
  if (gtk_toggle_button_get_active(rondButton) == 1)
  {
    if (activeButton != NULL && activeButton != rondButton) 
      gtk_toggle_button_set_active(activeButton, 0);
    activeButton = rondButton;
    e = pthread_create(&handler, NULL, circle, NULL);
    if (e != 0)
      abort();
  }
  else
  {
       pthread_cancel(handler);
  }
}

void pipetteSignal(GtkToggleButton *pipetteButton)
{
  int e = 0;
  if (gtk_toggle_button_get_active(pipetteButton) == 1)
  {
    if (activeButton != NULL && activeButton != pipetteButton) 
      gtk_toggle_button_set_active(activeButton, 0);
    activeButton = pipetteButton;
    e = pthread_create(&handler, NULL, getcolor, NULL);
    if (e != 0)
      abort();
  }
  else
  {
       pthread_cancel(handler);
  }

}

void l1Signal(GtkToggleButton *l1Button)
{
  if (gtk_toggle_button_get_active(l1Button) == 1)
  {
    if (activeButton2 != NULL && activeButton2 != l1Button) 
      gtk_toggle_button_set_active(activeButton2, 0);
    activeButton2 = l1Button;
    taille = 0;
  }
}
void l2Signal(GtkToggleButton *l2Button)
{
  if (gtk_toggle_button_get_active(l2Button) == 1)
  {
    if (activeButton2 != NULL && activeButton2 != l2Button) 
     gtk_toggle_button_set_active(activeButton2, 0);
    activeButton2 = l2Button;
    taille = 3;
  }
}
void l3Signal(GtkToggleButton *l3Button)
{
  if (gtk_toggle_button_get_active(l3Button) == 1)
  {
    if (activeButton2 != NULL && activeButton2 != l3Button) 
       gtk_toggle_button_set_active(activeButton2, 0);
    activeButton2 = l3Button;
    taille = 6;
  }
}
void l4Signal(GtkToggleButton *l4Button)
{
  if (gtk_toggle_button_get_active(l4Button) == 1)
  {
    if (activeButton2 != NULL && activeButton2 != l4Button) 
       gtk_toggle_button_set_active(activeButton2, 0);
    activeButton2 = l4Button;
    taille = 10;
  }
}

void b_wSignal()
{
  white_black();
}

void nofilterSignal()
{
  no_filter();
}

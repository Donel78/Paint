#include "main.h"

GtkToggleButton *activeButton = NULL;
pthread_t handler;

G_MODULE_EXPORT void drawSignal (GtkToggleButton *drawButton)
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

G_MODULE_EXPORT void togglebutton2 (GtkToggleButton *togglebutton2)
{
  if (gtk_toggle_button_get_active(togglebutton2) == 1)
  {
    if (activeButton != NULL && activeButton != togglebutton2) 
      gtk_toggle_button_set_active(activeButton, 0);
    activeButton = togglebutton2;
    printf("write\n");
    //e = pthread_create(&handler, NULL, draw, NULL);
  }
  else
  {
       //pthread_cancel(handler);
  }
}


G_MODULE_EXPORT void rubberSignal (GtkToggleButton *rubberButton)
{
  int e = 0;
  if (gtk_toggle_button_get_active(rubberButton) == 1)
  {
    if (activeButton != NULL && activeButton != rubberButton) 
      gtk_toggle_button_set_active(activeButton, 0);
    activeButton = rubberButton;
    printf("write\n");
    e = pthread_create(&handler, NULL, rubber, NULL);
    if (e != 0)
      abort();
  }
  else
  {
       pthread_cancel(handler);
  }
}

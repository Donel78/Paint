#include "main.h"

GtkToggleButton *activeButton = NULL;
pthread_t handler;

G_MODULE_EXPORT void drawSignal (GtkToggleButton *drawButton, GtkWidget *fenetre_principale)
{
  int e = 0;
  if (gtk_toggle_button_get_active(drawButton) == 1)
  {
    if (activeButton != NULL && activeButton != drawButton) 
      gtk_toggle_button_set_active(activeButton, 0);
    activeButton = drawButton;
    e = pthread_create(&handler, NULL, draw, NULL);
  }
  else
  {
    pthread_cancel(handler);
  }
}

G_MODULE_EXPORT void togglebutton2 (GtkToggleButton *togglebutton2, GtkWidget *fenetre_principale)
{
  int e = 0;
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

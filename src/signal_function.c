#include "main.h"

GtkToggleButton *activeButton = NULL;
pthread_t handler;
GdkRGBA *color;
int taille = 0;

void quitSignal()
{
  gtk_main_quit();
}

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

G_MODULE_EXPORT void textSignal (GtkToggleButton *textButton)
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


G_MODULE_EXPORT void rubberSignal (GtkToggleButton *rubberButton)
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

G_MODULE_EXPORT void loadimageSignal(GtkFileChooserButton *loadimage)
{
  char *image_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(loadimage));
  printf("%s\n",image_path);
  load(image_path);
}

G_MODULE_EXPORT void saveimageSignal(gpointer data)
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
G_MODULE_EXPORT void colorSignal(GtkColorChooser *ChooserColor)
{
  color = malloc(sizeof (GdkRGBA));
  gtk_color_chooser_get_rgba(ChooserColor,color);
  printf("%f\n",color->red * 255);
  printf("%f\n",color->blue * 255);


}

void t1Signal()
{
  taille = 0;
}
void t2Signal()
{
  taille = 3;
}
void t3Signal()
{
  taille = 6;
}
void t4Signal()
{
  taille = 10;
}

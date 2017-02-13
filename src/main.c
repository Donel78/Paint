#include "main.h"

int e;
pthread_t handler;
GtkToggleButton *activeButton = NULL; 

void *draw(void *arg)
{
  while (1)
  {
    printf("ntm\n");
  }

    pthread_exit(NULL);
}

G_MODULE_EXPORT void drawSignal (GtkToggleButton *drawButton, GtkWidget *fenetre_principale)
{
  if (gtk_toggle_button_get_active(drawButton) == 1)
  {
    if (activeButton != NULL) 
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
  if (gtk_toggle_button_get_active(togglebutton2) == 1)
  {
    if (activeButton != NULL) 
      gtk_toggle_button_set_active(activeButton, 0);
    activeButton = togglebutton2;
    printf("stop\n");
    //e = pthread_create(&handler, NULL, draw, NULL);
  }
  else
  {
       //pthread_cancel(handler);
  }
}

int main(int argc, char *argv [])
{
  GtkWidget *fenetre_principale = NULL;
  GtkBuilder *builder = NULL;
  gchar *filename = NULL;
  GError *error = NULL;

  gtk_init(&argc,&argv);
  builder = gtk_builder_new();
  filename = g_build_filename("test2.glade",NULL);
  gtk_builder_add_from_file (builder,filename,&error);
  g_free(filename);
  if(error)
  {
    gint code = error->code;
    g_printerr("%s\n", error->message);
    g_error_free (error);
    return code;
  }
  
  gtk_builder_connect_signals(builder,NULL);
  fenetre_principale = GTK_WIDGET(gtk_builder_get_object (builder,"MainWindow"));
  g_signal_connect (G_OBJECT (fenetre_principale),"destroy",(GCallback)gtk_main_quit,NULL);
  gtk_widget_show_all(fenetre_principale);
  

  gtk_main();
  return 0;

}

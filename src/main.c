#include "main.h"

SDL_Surface *paint = NULL;

int main(int argc, char *argv [])
{
  SDL_Init(SDL_INIT_VIDEO);
  paint = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_RESIZABLE);
  SDL_FillRect(paint, NULL, SDL_MapRGB(paint->format, 255, 255, 255));
  SDL_Flip(paint);

  GtkWidget *ToolWindow = NULL;
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
  ToolWindow = GTK_WIDGET(gtk_builder_get_object (builder,"ToolWindow"));
  g_signal_connect (G_OBJECT (ToolWindow),"destroy",(GCallback)gtk_main_quit,NULL);
  gtk_widget_show_all(ToolWindow);
 

  gtk_main();
  SDL_Quit();
  return 0;

}

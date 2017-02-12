#include <gtk/gtk.h>
#include <stdio.h>

/*G_MODULE_EXPORT void on_button1_clicked (GtkButton *button1, GtkWidget *fenetre_principale)
{
  while(1)
  {  
    printf("ntm\n");
    sleep(2);
  }
}

G_MODULE_EXPORT void on_button2_clicked (GtkButton *button1, GtkWidget *fenetre_principale)
{
    printf("stop\n");
}
*/

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

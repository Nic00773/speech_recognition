#include "gtk.h"
#include "gtk/gtk.h"

gchar *filename = "";
char *text = "";
GtkWidget *parent;


void charge_image(GtkButton *button, GtkImage *image)
{
  if(strcmp(filename,"") == 0)
    return;
  UNUSED(button);
  //SDL_Surface *img = IMG_Load((char *)filename);
  gtk_image_set_from_file (GTK_IMAGE (image), filename);
}

//Colors for print
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KWHT  "\x1B[37m"

void open_image(GtkButton *button, GtkLabel *text_label)
{
  GtkWidget *label = (GtkWidget *) text_label;
  GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET(button));
  //GtkFileFilter *filter = gtk_file_filter_new ();
  GtkWidget *dialog = gtk_file_chooser_dialog_new (("Open Image"),
                                                   GTK_WINDOW (toplevel),
                                                   GTK_FILE_CHOOSER_ACTION_OPEN,
                                                   "Open", GTK_RESPONSE_ACCEPT,
                                                   "Cancel", GTK_RESPONSE_CANCEL,
                                                   NULL);


  switch (gtk_dialog_run (GTK_DIALOG (dialog)))
  {
  case GTK_RESPONSE_ACCEPT:
  {
      filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
      gtk_label_set_text(GTK_LABEL(label),filename);
      break;
  }
  default:
      break;
  }
  gtk_widget_destroy(dialog);
}


void create_window(int argc, char *argv[])
{
    //Init variables
    GtkWidget *window;
    SGlobalData data;
    //Init GTK
    gtk_init(&argc, &argv);
    //Build from .glade
    data.builder = gtk_builder_new();
    gtk_builder_add_from_file(data.builder, "interface.glade", NULL);
    //Get main_window
    window =  GTK_WIDGET(gtk_builder_get_object(data.builder,"window"));
    parent = window;
    //Connect signals
    gtk_builder_connect_signals(data.builder, &data);

    gtk_window_set_title(GTK_WINDOW(window), "Ocr Project");
    gtk_widget_show_all(window);
    gtk_main();
}

void quit_window(GtkWidget *widget, gpointer window)
{
    gtk_main_quit();
    UNUSED(widget);
    UNUSED(window);
}

void exec(GtkButton *button)
{
    char str[80];
    //a changer
    sprintf(str, "../decoupage/./decoupage %s", filename);
    system(str);
    system("../NeuralNetwork/./nn");
    //system("vim text.txt");
    //fopen("text.txt","w");
    UNUSED(button);
}




int main(int argc, char *argv[])
{

    printf("#-----------------#\n");
    printf("        Ocr\n");
    printf("#-----------------#\n");
    //Create GTK window
    create_window(argc,argv);
    system("rm -r letters");
    return(EXIT_SUCCESS);
}

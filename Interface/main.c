#include <gtk/gtk.h>
#include <stdlib.h>

typedef struct UserInterface
{
    GtkWindow* window; 
    GtkButton* Choisir;
}UserInterface;

void choisir()
{
    system("open ~/Documents/ProjetS4");
}

int main()
{
	gtk_init(NULL, NULL);
	GtkBuilder* builder = gtk_builder_new();
    GError* error = NULL;

    if (gtk_builder_add_from_file(builder, "duel.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.duel"));
    GtkButton* Choisir = GTK_BUTTON(gtk_builder_get_object(builder, "Choisir"));
    /*
    GtkButton* Non = GTK_BUTTON(gtk_builder_get_object(builder, "Non"));
    GtkButton* Strange_no = GTK_BUTTON(gtk_builder_get_object(builder, "Strange_no"));
    GtkButton* Ouvrir = GTK_BUTTON(gtk_builder_get_object(builder, "Ouvrir"));
    */


    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(Choisir, "clicked", G_CALLBACK(choisir), NULL);
    /*
    g_signal_connect(Non, "clicked", G_CALLBACK(non), NULL);
    g_signal_connect(Strange_no, "clicked", G_CALLBACK(strange_no), NULL);
    g_signal_connect(Ouvrir, "clicked", G_CALLBACK(ouvrir), NULL);
    */

    gtk_main();

    return 0;
}

#ifndef GTK_H_
#define GTK_H_

# include <err.h>
# include <stdlib.h>
# include <stdio.h>
# include <gtk/gtk.h>
# include <gtk-3.0/gtk/gtk.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <string.h>


typedef struct
{
    GtkBuilder *builder;
    gpointer user_data;
} SGlobalData;

#define UNUSED(x) (void)(x)

void charge_image(GtkButton *button, GtkImage *image);
void open_image(GtkButton *button, GtkLabel *text_label);
void create_window(int argc, char *argv[]);
void quit_window(GtkWidget *widget, gpointer window);
int launchOCR(GtkButton *button, GtkTextBuffer *buffer);

# endif

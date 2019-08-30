#include <gtk/gtk.h>
#include <string>

#include "videoHandler.h"

//void callback(GtkWidget* widget, gpointer data);

//gtk_signal_connect is used to define what buttons do

GtkWidget* window;

int getHeight()
{
	int width, height;

	gtk_window_get_size(GTK_WINDOW(window), &width, &height);

	return(height);
}

int getWidth()
{
	int width, height;

	gtk_window_get_size(GTK_WINDOW(window), &width, &height);

	return(width);
}

void save() // Not written yet
{
	// saveVideo();
	g_print("Saved");
}

void drawArea(GtkWidget *window)
{
	cairo_surface_t* surface;
	cairo_surface_t* cr;
	int height = getHeight();
	int width = getWidth();

	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, (width-0.2*width), (height-0.2*height));
}

void close(GtkWidget* widget, gpointer data, GtkWidget* window) // Brings up menu for exiting
{
	GtkWidget* dialog{};

	dialog = gtk_dialog_new_with_buttons("Are you Sure?", NULL, GTK_DIALOG_MODAL, "Save & Quit" , GTK_RESPONSE_OK, "Quit" , GTK_RESPONSE_NO, "Cancel", GTK_RESPONSE_CANCEL, NULL);
	gtk_widget_show_all(dialog);
	gint response = gtk_dialog_run(GTK_DIALOG(dialog));
	//Checks which button is pressed
	if (response == GTK_RESPONSE_OK)
	{
		save();
		exit(EXIT_SUCCESS);
	}
	if (response == GTK_RESPONSE_NO)
	{
		gtk_widget_destroy(window);
		exit(EXIT_SUCCESS);
	}
	gtk_widget_destroy(dialog);
	gtk_widget_show_all(window);
}

void createWindow(int argc, char* argv[], std::string title) //Creates the window
{
	GtkWidget* button;

	gtk_init(&argc, &argv);

	//window
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), title.c_str());
	gtk_window_set_default_size(GTK_WINDOW(window),500,500);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(close), NULL);

	//button
	button = gtk_button_new_with_label("Button");
	gtk_container_add(GTK_CONTAINER(window), button);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(close), NULL);

	gtk_widget_show_all(window); // set the window as visible
	loadVideo();

	gtk_main(); //Main loop for GTK
}

void error(std::string error)
{
	gtk_widget_show_all(window);
	g_print("Error: ", error);
}

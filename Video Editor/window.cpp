#include <gtk/gtk.h>
#include <string>

#include "videoHandler.h"
#include "drawingArea.h"

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

void save()
{
	auto capture = getCapture();
	int frames = capture.get(cv::CAP_PROP_FRAME_COUNT);
	frames *= capture.get(cv::CAP_PROP_FPS);
	clip(0, frames, "outvid1.avi");
	g_print("Saved");
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
	drawArea area;

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

	GtkWidget* da = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window), da);
	g_signal_connect(G_OBJECT(da), "draw", G_CALLBACK(display), NULL);

	gtk_widget_show_all(window); // set the window as visible
	loadVideo();

	gtk_main(); //Main loop for GTK
}

void error(std::string error)
{
	gtk_widget_show_all(window);
	g_print("Error: ", error);
}

GtkWidget* getWindowNotNative()
{
	return(window);
}

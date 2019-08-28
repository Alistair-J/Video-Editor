#include <gtk/gtk.h>
#include <string>

//void callback(GtkWidget* widget, gpointer data);

//gtk_signal_connect is used to define what buttons do

void save() // Not written yet
{
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
	GtkWidget* window;
	GtkWidget* button;

	gtk_init(&argc, &argv);

	//window
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), title.c_str());
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(close), NULL);

	//button
	button = gtk_button_new_with_label("Button");
	gtk_container_add(GTK_CONTAINER(window), button);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(close), NULL);

	gtk_widget_show_all(window); // set the window as visible

	gtk_main(); //Main loop for GTK
}

void error(std::string error)
{
	g_print("Error: ", error);
}
#pragma once
#include <gtk/gtk.h>

class drawArea
{
public:
	cairo_format_t format;
	int height, width;
	const GdkPixbuf* pix;
	cairo_surface_t* surface;
	cairo_t* cr;
	//GdkPixbuf* getPixbuf();
	void setPixbuf();
};

void display();
int getBPS();
gboolean draw_callback(GtkWidget* widget, cairo_t* cr, gpointer data);
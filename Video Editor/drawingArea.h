#pragma once
#include <gtk/gtk.h>

class drawArea
{
public:
	int height, width;
	GdkPixbuf* pix;
	cairo_t* cr;
	GdkPixbuf* getPixbuf();
};

gboolean display();
#include <gtk/gtk.h>
#include <opencv2/opencv.hpp>
#include <string>


#include "window.h"
#include "videoHandler.h"
#include "drawingArea.h"

drawArea area;

//const GdkPixbuf* drawArea::getPixbuf()
//{
	//cv::VideoCapture capture = getCapture();
	//cv::Mat frame = getFrame();
	//pix = gdk_pixbuf_new_from_data((guchar*)capture.read(frame), GDK_COLORSPACE_RGB, FALSE, getBPS(), getWidth(), getHeight(), (int)frame.step, NULL, NULL);
	//return (pix);
//}

void drawArea::setPixbuf()
{
	cv::VideoCapture capture = getCapture();
	cv::Mat frame = getFrame();
	//
	area.pix = gdk_pixbuf_new_from_data((guchar*)capture.read(frame), GDK_COLORSPACE_RGB, FALSE, 8, 500, 500, (int)frame.step, NULL, NULL);
}


void display()
{
	area.height = getHeight();
	area.width = getWidth();

	area.format = ((gdk_pixbuf_get_has_alpha(area.pix)) ? CAIRO_FORMAT_ARGB32 : CAIRO_FORMAT_RGB24);
	area.surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, area.width, area.height);
	g_assert(area.surface != NULL);
	area.cr = cairo_create(area.surface);

	//gdk_cairo_set_source_pixbuf(area.cr, area.pix,(area.width),(area.height));
	gdk_cairo_set_source_pixbuf(area.cr, area.pix, 0, 0);

	GdkRGBA* colour{};
	gdk_rgba_parse(colour, "#FF0000");




	gdk_cairo_set_source_rgba(area.cr,colour);

	cairo_paint(area.cr);
	cairo_surface_write_to_png(area.surface, "output.png");
	cairo_destroy(area.cr);
	cairo_surface_destroy(area.surface);
}

int getBPS()
{
	cv::Mat frame = getFrame();
	if (frame.depth() == CV_8U)
	{
		return(8 * (int)frame.channels());
	}
	else
	{
		return(16 * (int)frame.channels());
	}
}

gboolean draw_callback(GtkWidget* widget, cairo_t* cr, gpointer data)
{
	guint width, height;
	GdkRGBA colour;
	GtkStyleContext* context;

	cv::VideoCapture capture = getCapture();
	load1Frame(widget);
	cv::Mat frame = getFrame();
	if (!frame.empty())
	{
		cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

		const GdkPixbuf* pix = gdk_pixbuf_new_from_data((guchar*)frame.data, GDK_COLORSPACE_RGB, FALSE, 8, (int)frame.cols, (int)frame.rows, (int)frame.step, NULL, NULL);
		context = gtk_widget_get_style_context(widget);

		width = gtk_widget_get_allocated_width(widget);
		height = gtk_widget_get_allocated_height(widget);

		cairo_rectangle(cr, 0, 0 , width , height );

		gtk_style_context_get_color(context,
			gtk_style_context_get_state(context),
			&colour);
		gdk_cairo_set_source_rgba(cr, &colour);

		gdk_cairo_set_source_pixbuf(cr, pix, 0, 0);

		gtk_render_background(context, cr, 0, 0, width, height);

		cairo_fill(cr);

		return FALSE;
	}

	return FALSE;
}
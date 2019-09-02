#include <gtk/gtk.h>
#include <opencv2/opencv.hpp>

#include "window.h"
#include "videoHandler.h"
#include "drawingArea.h"

drawArea area;

GdkPixbuf* drawArea::getPixbuf()
{
	cv::VideoCapture capture = getCapture();
	cv::Mat frame = getFrame();
	pix = gdk_pixbuf_new_from_data((guchar*)capture.read(frame), GDK_COLORSPACE_RGB, FALSE, frame.depth(), getWidth(), getHeight(), (int)frame.step, NULL, NULL);
	return (pix);
}

gboolean display()
{
	GtkWidget* window = getWindowNotNative();
	area.height = getHeight();
	area.width = getWidth();
	gdk_cairo_set_source_pixbuf(area.cr, area.pix,(0.2*area.width),(0.2*area.height));

	cairo_fill(area.cr);

	return(FALSE);
}

/*void drawArea(GtkWidget* window)
{
	cairo_surface_t* surface;
	cairo_content_t* cr;
	cv::VideoCapture capture = getCapture();
	cv::Mat frame = getFrame();



	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, (width - 0.2 * width), (height - 0.2 * height));

	gdk_cairo_set_source_pixbuf(cr, pix, 100, 80);

	window.add(surface);

}*/
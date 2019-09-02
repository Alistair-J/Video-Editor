#pragma once
#include <gtk/gtk.h>

void createWindow(int argc, char* argv[], std::string title);
void error(std::string error);
int getWidth();
int getHeight();
GtkWidget* getWindowNotNative();
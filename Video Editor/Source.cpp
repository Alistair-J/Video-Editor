#include <iostream>

#include "window.h"
#include "videoHandler.h"

int main(int   argc, char* argv[])
{
	loadVideo();
	createWindow(argc, argv, "Title");
	return 0;
}
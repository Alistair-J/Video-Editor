#pragma once
#include <opencv2/opencv.hpp>

void loadVideo();
void saveVideo();
void clip(int startTime, int endTime, std::string name);
void loadFrame1();
cv::VideoCapture getCapture();
cv::Mat getFrame();
void load1Frame(GtkWidget* widget);
void changeVideoState();
bool getVideoState();

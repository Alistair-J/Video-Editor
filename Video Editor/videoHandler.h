#pragma once
#include <opencv2/opencv.hpp>

void loadVideo();
void saveVideo();
void clip(int startTime, int endTime, std::string name);
cv::VideoCapture getCapture();
cv::Mat getFrame();
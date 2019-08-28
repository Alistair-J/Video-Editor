#include <opencv2/opencv.hpp>
#include <string>

#include "window.h"

void loadVideo()
{
	cv::VideoCapture capture("sample.mp4");
	if (!capture.isOpened())
	{
		error("Video failed to open");
	}
	while (TRUE)
	{
		cv::Mat frame;
		capture >> frame;
		if (frame.empty())
		{
			break;
		}
		cv::imshow("Frame", frame);
		char c = (char)cv::waitKey(25);
		if (c == 27)
			break;
	}
	capture.release();
	cv::destroyAllWindows();
}

void saveVideo()
{
	cv::VideoWriter write("outvid.avi", cv::VideoWriter::fourcc('F', 'F', 'V', '1'), 60, cv::Size(cv::CAP_PROP_FRAME_WIDTH, cv::CAP_PROP_FRAME_HEIGHT));
}
//playback
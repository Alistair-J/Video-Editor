#include <opencv2/opencv.hpp>
#include <string>
#include <chrono> //<---

#include "window.h"

void saveVideo()
{
	cv::VideoWriter write("outvid.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 60, cv::Size(cv::CAP_PROP_FRAME_WIDTH, cv::CAP_PROP_FRAME_HEIGHT));
}

void loadVideo()
{
	cv::VideoCapture capture("sample.mp4");

	int height = getHeight();
	int width = getWidth();
	height = height - (0.2 * height);
	width = width - (0.2 * width);



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
		cv::namedWindow("Video", cv::WindowFlags::WINDOW_NORMAL);
		//cv::resizeWindow("Video", (width - 0.2 * width), (height - 0.2 * height));
		cv::imshow("Video", frame);

		char c = (char)cv::waitKey(25);
		if (c == 27)
		{
			break;
		}
	}
	saveVideo();
	capture.release();
	cv::destroyAllWindows();
}


//playback
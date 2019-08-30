#include <opencv2/opencv.hpp>
#include <string>
#include <chrono> //<---

#include <iostream>

#include "window.h"

cv::VideoCapture capture("sample.mp4");
cv::Mat frame;

void saveVideo()
{
	const std::string filename = "outvid1.avi";
	cv::VideoWriter writer(filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10,
		cv::Size(capture.get(cv::CAP_PROP_FRAME_WIDTH),
			capture.get(cv::CAP_PROP_FRAME_HEIGHT)), TRUE);

	cv::cvtColor(frame, frame, cv::COLOR_RGB2BGR);

	if (!writer.isOpened()) {
		std::cout << "Could not open the output video file for write\n";
	}
	//--- GRAB AND WRITE LOOP
	std::cout << "Writing videofile\nPress any key to terminate\n";
	while(TRUE)
	{
		// check if we succeeded
		if (!capture.read(frame)) {
			error("ERROR!blank frame grabbed\n");
			break;
		}
		// encode the frame into the videofile stream
		writer.write(frame);
		// show live and wait for a key with timeout long enough to show images		cv::imshow("Live", frame);
		if (cv::waitKey(5) >= 0)
			break;
	}

}

void loadVideo()
{
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
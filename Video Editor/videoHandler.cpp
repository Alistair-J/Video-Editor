#include <opencv2/opencv.hpp>
#include <string>

#include <iostream>

#include "window.h"

cv::VideoCapture capture("sample.mp4");
cv::Mat frame;

cv::VideoCapture getCapture()
{
	return(capture);
}

cv::Mat getFrame()
{
	return(frame);
}

void saveVideo()
{
	const std::string filename = "outvid1.avi";
	int fps = capture.get(cv::CAP_PROP_FPS);
	cv::VideoWriter writer(filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps,
		cv::Size(capture.get(cv::CAP_PROP_FRAME_WIDTH),
			capture.get(cv::CAP_PROP_FRAME_HEIGHT)), TRUE);

	cv::cvtColor(frame, frame, cv::COLOR_RGB2BGR);

	if (!writer.isOpened()) {
		std::cout << "Could not open the output video file for write\n";
	}
	//--- GRAB AND WRITE LOOP
	std::cout << "Writing videofile\nPress any key to terminate\n";
	while (TRUE)
	{
		// check if we succeeded
		if (!capture.read(frame)) {
			error("ERROR!blank frame grabbed\n");
			break;
		}
		// encode the frame into the videofile stream
		writer.write(frame);
		// show live and wait for a key with timeout long enough to show images
		char c = (char)cv::waitKey(25);
		if (c == 27)
		{
			break;
		}
	}

}

void clip(int startTime, int endTime, std::string name)
{
	const std::string filename = name.c_str();
	//int frames = capture.get(cv::CAP_PROP_FRAME_COUNT);
	int fps = capture.get(cv::CAP_PROP_FPS);

	startTime *= fps;
	endTime *= fps;

	cv::VideoWriter writer(filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps,
		cv::Size(capture.get(cv::CAP_PROP_FRAME_WIDTH),
			capture.get(cv::CAP_PROP_FRAME_HEIGHT)), TRUE);

	if (!writer.isOpened()) {
		std::cout << "Could not open the output video file for write\n";
	}

	int frames = 0;
	while (TRUE)
	{
		frames++;
		capture.read(frame);
		if (!capture.read(frame))
		{
			error("ERROR!blank frame grabbed\n");
			break;
		}

		if (frames >= startTime && frames <= endTime)
		{
			writer.write(frame);
		}

		char c = (char)cv::waitKey(25);
		if (c == 27)
		{
			break;
		}
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
	//saveVideo();
	clip(1, 5, "clip1.avi");
	capture.release();
	cv::destroyAllWindows();
}
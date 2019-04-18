#ifndef _MYVIDEOCAPTURE_H_
#define _MYVIDEOCAPTURE_H_

#include<thread>
#include<string>
#include<iostream>
#include "config.h"
#include<functional>
#include<chrono>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/videoio.hpp>
#include<opencv2/highgui.hpp>

class VC
{
public:
	VC(std::string url);
	int readVideo();
	int readVideoThread(std::thread &t);
	int getFrame(cv::Mat &);
	int getSize(cv::Size &);
	int getFps(float &);

private:
	cv::VideoCapture _videoCap;
	cv::Mat _frame; 
	cv::Size _size;
	float _fps;
};

#endif
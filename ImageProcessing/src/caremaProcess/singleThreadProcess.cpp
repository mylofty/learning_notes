#include<iostream>
#include<string>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/videoio.hpp>
#include<opencv2/highgui.hpp>

int singleThread()
{
	const std::string url = "rtsp://admin:admin@192.168.1.108/cam/realmonitor?channel=1&subtype=0";
	cv::VideoCapture videoCap(url);
	if(!videoCap.isOpened())
	{
		std::cout << "video open failed!"<< std::endl;
		return -1;
	}
	cv::Size size = cv::Size((int)videoCap.get(cv::CAP_PROP_FRAME_WIDTH), (int)videoCap.get(cv::CAP_PROP_FRAME_HEIGHT));
	float fps = videoCap.get(cv::CAP_PROP_FPS);
	std::cout << "width, height, fps is " << size << ", " << fps << std::endl;

	// 循环读取每一帧数据
	cv::Mat origin_frame, small_origin_frame, blurframe, small_blurframe;
	for(; ; )
	{
		double t1 = (double)cv::getTickCount();
		videoCap.read(origin_frame);
		if(origin_frame.empty())
		{
			std::cout<<"ERROR! frame empty" << std::endl;
			break;
		}
		cv::resize(origin_frame, small_origin_frame, cv::Size(1920/3, 1080/3), 0, 0);
		cv::imshow("live", small_origin_frame);
		////////////////////	均值平滑	/////////////////////////////
		// for(int i=1; i < 31; i=i+2)
		// {
		// 	cv::blur(origin_frame, blurframe, cv::Size(i, i), cv::Point(-1, -1));
		// }
		// cv::resize(blurframe, small_blurframe, cv::Size(1920/3, 1080/3), 0, 0);
		// cv::imshow("blur", small_blurframe);
		/////////////////////////////////////////////////////////////////
		double t2 = (double)cv::getTickCount();
		double time = (t2 - t1) / cv::getTickFrequency()*1000;
		std::cout << "use time is (/ms): " << time << std::endl;
		if(cv::waitKey(25) >= 0)
			break;
	}
	return 0;
}

int main()
{
	singleThread();
	return 0;
}
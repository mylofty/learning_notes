#include "camera.h"
#include<chrono>
#include<sstream>
#include<sys/stat.h>
#include<iomanip>

Camera::Camera(std::string url, int id, std::function<int(cv::Mat, cv::Mat &)> callback)
	:_vc(url),_analysisCallback(callback)
{
	this->id = id;
	std::thread t;
	this->_vc.readVideoThread(t);
	t.detach();
}

int Camera::save(std::string folder, double during)
{
	cv::Mat frame;
	cv::Size size;
	float fps;
	_vc.getSize(size);
	_vc.getFps(fps);
	/////////////////////////////////处理文件名和文件名//////////////////////////////////////////////////
	mkdir(folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);					//创建文件夹folder
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() );			//生成文件名
	std::stringstream ss;
	ss << std::put_time(std::localtime(&t), "%y-%m-%d-%H-%M");
	std::string filename;
	ss >> filename;
	filename = folder + "/" + filename + ".avi";
	///////////////////////////////////保存实时视频到avi中去//////////////////////////////////////////////
	cv::VideoWriter writer;
	writer.open(filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, size);
	std::cout << "camera " << this->id << " run saveFunction! thread_id is " << std::this_thread::get_id()  << std::endl;
	std::cout << "videocapture picture size is " << size << " fps is " << fps<< std::endl;
	if(!writer.isOpened())
	{
		std::cout << "open VideoWriter failed! " << std::endl;
		return CC::OPEN_WRITER_ERROR;
	}
	// 循环读取每一帧数据并保存
	double tickFrequency = (double)cv::getTickFrequency();
	double startTime = (double)cv::getTickCount();
	for(; ; )
	{
		if(_vc.getFrame(frame) != CC::FAIL)
		{
			std::cout << "frame size is " << frame.size << std::endl;
			writer.write(frame);
			cv::imshow("living", frame);
		}
		std::cout << "camera frame size is " << frame.size << std::endl;
		double endTime = (double)cv::getTickCount();
		double time = (endTime - startTime)/tickFrequency;
		if(time > during)
		{
			std::cout << "camera " << this->id << " save success! thread_id is " << std::this_thread::get_id()  << std::endl;
			break;
		}
		if(cv::waitKey(1) >= 0)
		{
			std::cout << "success break by keypress" << std::endl;
			break;
		}
	}
	return CC::SUCCESS;
}
int Camera::saveThread(std::string folder, double during, std::thread &t)
{
	t = std::thread(&Camera::save, this, folder, during);
	return 0;
}
int Camera::analysis()
{
	return 0;
}
#include<camera.h>
#include<iostream>
#include<Param.h>
template<class T>
Camera<T>::Camera(T url, int id)
{
	this->url = url;
	this->id = id;
}

template<class T>
int Camera<T>::saveAVIRealTime(std::string folder, int during)
{
	cv::VideoCapture videoCap;
	cv::VideoWriter writer;
	// 打开rtsp视频流
	videoCap.open(this->url);
	if(!videoCap.isOpened())
	{
		std::cout << "open camera error! (OPEN_VIDEO_ERROR)" << std::endl;
		return CC::OPEN_CAPTURE_ERROR;
	}
	cv::Size size = cv::Size((int)videoCap.get(cv::CAP_PROP_FRAME_WIDTH), (int)videoCap.get(cv::CAP_PROP_FRAME_HEIGHT));
	float fps = videoCap.get(cv::CAP_PROP_FPS);
	std::cout << "camera " << this->id << " open success! thread_id is " << std::this_thread::get_id()<<" \n video width, height, fps is " << size << ", " << fps << std::endl;
	//打开视频文件写入
	std::string filename = "";
	filename = folder + "/orgin_live.avi";
	writer.open(filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, size);
	if(!writer.isOpened())
	{
		std::cout << "open VideoWriter failed! " << std::endl;
		return CC::OPEN_WRITER_ERROR;
	}
	// 循环读取每一帧数据并保存
	cv::Mat frame;
	
	double tickFrequency = (double)cv::getTickFrequency();
	for(; ; )
	{
		double startTime = (double)cv::getTickCount();
		videoCap.read(frame);
		///////////// DEBUG 显示  ////////////////////////////// 
		// cv::Mat small_frame;
		// cv::resize(frame, small_frame, cv::Size((int)videoCap.get(cv::CAP_PROP_FRAME_WIDTH)/4, videoCap.get((int)cv::CAP_PROP_FRAME_HEIGHT)/4), 0, 0);

		// cv::imshow("orgin_live", small_frame);
		// if(cv::waitKey(25) >= 0)
		// {
		// 	std::cout << "success break by keypress" << std::endl;
		// 	break;
		// }
		/////////////////////////////////////////////////////
		writer.write(frame);
		double endTime = (double)cv::getTickCount();
		double time = (endTime - startTime)/tickFrequency*1000;
		std::cout << "save avi " << time << "ms " << std::endl;
		// if(time > during)
		// {
		// 	std::cout << "success to save " << time << " seconds video" << std::endl;
		// 	break;
		// }
	}
	return CC::SAVE_AVI_SUCCESS;
}

template<class T>
int  Camera<T>::analysis()
{
	cv::VideoCapture videoCap;
	// 打开rtsp视频流
	videoCap.open(this->url);
	videoCap.set(cv::CAP_PROP_BUFFERSIZE, 3); 		//设置队列缓冲区大小为3,默认为38,使得尽量拿到当前的帧
	if(!videoCap.isOpened())
	{
		std::cout << "open camera error! (OPEN_VIDEO_ERROR)" << std::endl;
		return CC::OPEN_CAPTURE_ERROR;
	}
	cv::Size size = cv::Size((int)videoCap.get(cv::CAP_PROP_FRAME_WIDTH), (int)videoCap.get(cv::CAP_PROP_FRAME_HEIGHT));
	float fps = videoCap.get(cv::CAP_PROP_FPS);
	std::cout << "camera " << this->id << " open success! thread_id is "<< std::this_thread::get_id() <<"\n video width, height, fps is " << size << ", " << fps << std::endl;

	cv::Mat origin_frame;
	double tickFrequency = (double)cv::getTickFrequency();
	for(long long iter = 0; ; iter++ )
	{
		videoCap.read(origin_frame);
		////////////////////	analysis 均值平滑	60ms /////////////////////////////
		cv::Mat blurframe, small_blurframe, small_origin_frame;
		double startTime = (double)cv::getTickCount();
		if(iter % 1 == 0)			//每10帧处理一次
		{
			iter = 0;
			for(int i=1; i < 31; i=i+2)
			{
				cv::blur(origin_frame, blurframe, cv::Size(i, i), cv::Point(-1, -1));
			}
			cv::resize(origin_frame, small_origin_frame, cv::Size((int)videoCap.get(cv::CAP_PROP_FRAME_WIDTH)/3, (int)videoCap.get(cv::CAP_PROP_FRAME_HEIGHT)/3), 0, 0);
			cv::resize(blurframe, small_blurframe, cv::Size((int)videoCap.get(cv::CAP_PROP_FRAME_WIDTH)/3, (int)videoCap.get(cv::CAP_PROP_FRAME_HEIGHT)/3), 0, 0);
			cv::imshow("small_origin_frame", small_origin_frame);
		}
		
		if(cv::waitKey(1) >= 0)
		{
			std::cout << "success break by keypress" << std::endl;
			break;
		}
		//////////////////////////////////////////////////////////////////////////////////
		double endTime = (double)cv::getTickCount();
		double time = (endTime - startTime)/tickFrequency * 1000;
		// std::cout << "analysis one picture use time " << time << "ms" << std::endl;

	}
	return CC::ANALYSIS_SUCCESS;
}

template<class T>
std::thread Camera<T>::saveAVIRealTimeThread(std::string folder, int during)
{
	return std::thread(&Camera<T>::saveAVIRealTime, this, folder, during);
}

template<class T>
std::thread Camera<T>::analysisThread()
{
	return std::thread(&Camera<T>::analysis,this);
}
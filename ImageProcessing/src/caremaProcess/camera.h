#include<iostream>
#include<thread>
#include<Param.h>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/videoio.hpp>
#include<opencv2/highgui.hpp>

template<class T>
class Camera
{
public:
	// 构造函数，传入url和摄像机id

	Camera(T url, int id = 0);

	/**
	*  将实时视频流保存到文件中
 	* param floder	视频需要保存到哪个文件夹下
 	* param during:			视频多少时间保存一次，即将文件分片保存
	**/
	int saveAVIRealTime(std::string folder="data", int during = 10);

	/**
	* 该函数将保存视频功能放入另外一个线程中
	**/
	std::thread saveAVIRealTimeThread(std::string folder="data", int during = 10);

	/**
	*	视频分析算法
	**/
	int analysis(int during);

	/**
	* 该函数进视频分析放入另外一个线程中
	*/
	std::thread analysisThread(int during);


private:
	T 	url;			//每个Camera实例的摄像机rtsp流地址，如大华摄像机"rtsp://admin:admin@192.168.1.108/cam/realmonitor?channel=1&subtype=0"
	int 					id;				//表示摄像头id
	// cv::VideoCapture 	videoCap;		//摄像机捕获视频流的类
};

// #include<camera.h>
// #include<iostream>
// #include<Param.h>
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
	double startTime = (double)cv::getTickCount();
	double tickFrequency = (double)cv::getTickFrequency();
	for(; ; )
	{
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
		double time = (endTime - startTime)/tickFrequency;
		if(time > during)
		{
			std::cout <<"thread" << std::this_thread::get_id()  <<  "\tsuccess to save " << time << " seconds video" << std::endl;
			break;
		}
	}
	return CC::SAVE_AVI_SUCCESS;
}

template<class T>
int  Camera<T>::analysis(int during)
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
	long  pic_name_id = 100;
	double startTime = (double)cv::getTickCount();
	for(long long iter = 0; ; iter++ )
	{
		videoCap.read(origin_frame);
		////////////////////	analysis 镜像  /////////////////////////////
		cv::Mat blurframe, small_blurframe, small_origin_frame, origin_image_fliped;		
		if(iter % 10 == 0)			//每10帧处理一次
		{
			iter = 0;
			cv::flip(origin_frame, origin_image_fliped, -1);
			// cv::imshow("small_origin_frame", origin_image_fliped);
			std::string picName = "data2/images" ;
			picName = picName + std::to_string(pic_name_id++) + ".jpg";
			cv::imwrite(picName, origin_image_fliped);
		}
		if(cv::waitKey(1) >= 0)
		{
			std::cout << "success break by keypress" << std::endl;
			break;
		}
		//////////////////////////////////////////////////////////////////////////////////
		double endTime = (double)cv::getTickCount();
		double time = (endTime - startTime)/tickFrequency;
		if(time > during)
		{
			std::cout << "thread is is:" << std::this_thread::get_id() << " \tanalysis picture use time " << time << "ms" << std::endl;
			break;
		}
		

	}
	return CC::ANALYSIS_SUCCESS;
}

template<class T>
std::thread Camera<T>::saveAVIRealTimeThread(std::string folder, int during)
{
	return std::thread(&Camera<T>::saveAVIRealTime, this, folder, during);
}

template<class T>
std::thread Camera<T>::analysisThread(int during)
{
	return std::thread(&Camera<T>::analysis,this, during);
}
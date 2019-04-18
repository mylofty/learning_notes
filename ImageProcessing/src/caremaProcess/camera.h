#include<iostream>
#include<thread>
#include<Param.h>
#include<functional>
#include<chrono>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/videoio.hpp>
#include<opencv2/highgui.hpp>
#include<sys/stat.h>
#include<iomanip>

template<class T>
class Camera
{
public:
	// 构造函数，传入url和摄像机id，以及用户的分析处理函数
	Camera(T url, int id,  std::function<int(cv::Mat, cv::Mat &)> callback);

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
	int analysis(std::string folder, int during);

	/**
	* 该函数进视频分析放入另外一个线程中
	*/
	std::thread analysisThread(std::string folder, int during);


private:
	T 	url;			//每个Camera实例的摄像机rtsp流地址，如大华摄像机"rtsp://admin:admin@192.168.1.108/cam/realmonitor?channel=1&subtype=0"
	int 					id;				//表示摄像头id
	std::function<int(cv::Mat, cv::Mat &)> _analysisCallback;		//用户自定义的分析处理函数
	// cv::VideoCapture 	videoCap;		//摄像机捕获视频流的类
	// cv::Mat _frame;
};

// #include<camera.h>
// #include<iostream>
// #include<Param.h>
template<class T>
Camera<T>::Camera(T url, int id,  std::function<int(cv::Mat, cv::Mat &)> callback) :
			_analysisCallback(callback)
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
	/////////////////////////////////处理文件夹和文件名//////////////////////////////////////////////////
	mkdir(folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);					//创建文件夹folder，该函数只能单层创建文件夹
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() );			//生成文件名
	std::stringstream ss;
	ss << std::put_time(std::localtime(&t), "%y-%m-%d-%H-%M");
	std::string filename;
	ss >> filename;
	filename = folder + "/" + filename + "orgin_live.avi";
	///////////////////////////////////保存实时视频到avi中去//////////////////////////////////////////////
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
		videoCap.read(_frame);
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
		writer.write(_frame);
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
int  Camera<T>::analysis(std::string folder, int during)
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
	std::cout << "camera " << this->id << " open success! thread_id is "<< std::this_thread::get_id()  << std::endl;
	/////////////////////////////////处理文件夹和文件名//////////////////////////////////////////////////
	mkdir(folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);					//创建文件夹folder，该函数只能单层创建文件夹
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() );			//生成文件名
	std::stringstream ss;
	ss << std::put_time(std::localtime(&t), "%y-%m-%d-%H-%M");
	std::string filename;
	ss >> filename;
	///////////////////////////////////分析处理部分//////////////////////////////////////////////
	cv::Mat origin_frame;
	double tickFrequency = (double)cv::getTickFrequency();
	double startTime = (double)cv::getTickCount();
	for(long long iter = 0; ; iter++ )
	{
		videoCap.read(origin_frame);
		// origin_frame = _frame;
		cv::Mat analysis_frame;
		if(iter % 10 == 0)								//定义每10帧处理一帧，10帧调用分析函数一次，并将其保存到指定文件夹下
		{
			_analysisCallback(origin_frame, analysis_frame);
			std::string currentPic = folder + "/" + filename + std::to_string(iter) + ".jpg";
			std::cout << "filename " << currentPic << std::endl;
			cv::imwrite(currentPic, analysis_frame);
		}	
		double endTime = (double)cv::getTickCount();
		double time = (endTime - startTime)/tickFrequency;
		if(time > during)
		{
			std::cout <<"thread" << std::this_thread::get_id()  <<  "\tsuccess to analysis " << time << " seconds video" << std::endl;
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
std::thread Camera<T>::analysisThread(std::string folder, int during)
{
	auto analysisFun= std::bind(&Camera<T>::analysis, this, std::placeholders::_1, std::placeholders::_2);
	return std::thread(analysisFun, folder, during);
}
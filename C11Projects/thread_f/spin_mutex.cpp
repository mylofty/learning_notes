#include<thread>
#include<string>
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
	int read();
	int readThread();
	int get();
private:
	cv::VideoCapture _videoCap;
	cv::Mat _frame; 
}

class Camera
{
public: 
	Camera(std::string url, int id = 0) ;
	int save();
	int analysis();
	int saveThread();
	int analysisThread();
private:
	int id;
	VC _vc;
	std::function<int(std::Mat, std::Mat &)> _analysisCallback;
}

VC::VC(std::string url)
{
	this->_videoCap.open(url);
	if(!_videoCap.isOpend())
	{
		std::cout << "open camera error! (OPEN_VIDEO_ERROR)" << std::endl;
		exit(CC::OPEN_CAPTURE_ERROR);
	}
}

int VC::read()
{
	for(;;)
	{
		_vedioCap.read(_frame);
	}
}
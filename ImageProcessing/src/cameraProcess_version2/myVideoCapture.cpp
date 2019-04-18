#include "myVideoCapture.h"

VC::VC(std::string url)
{
	this->_videoCap.open(url);
	if(!_videoCap.isOpened())
	{
		std::cout << "open camera error! (OPEN_VIDEO_ERROR)" << std::endl;
		exit(CC::OPEN_CAPTURE_ERROR);
	}
	this->_size = cv::Size((int)_videoCap.get(cv::CAP_PROP_FRAME_WIDTH), (int)_videoCap.get(cv::CAP_PROP_FRAME_HEIGHT)); //[1920,1080]
	std::cout << "VC::VC: "<< this->_size.width << ", " << this->_size.height << std::endl;
	this->_fps = _videoCap.get(cv::CAP_PROP_FPS);
}

int VC::readVideo()
{
	std::cout << "readVideo in thread " << std::this_thread::get_id() << std::endl;
	for(;;)
	{
		_videoCap.read(_frame);
		// std::cout << "readvideo frame" << _frame.size() << std::endl;
		// cv::imshow("videocapture", _frame);
		// if(cv::waitKey(1) >= 0)
		// {
		// 	std::cout << "success break by keypress" << std::endl;
		// 	break;
		// }
	}
	return CC::SUCCESS;
}

 int VC::readVideoThread(std::thread &t)
{
	t = std::thread(&VC::readVideo, this);
	return CC::SUCCESS;
}

int VC::getFrame(cv::Mat &mat)
{
	if(this->_frame.empty())
		return CC::FAIL;
	mat = this->_frame;
	return CC::SUCCESS;
}

int VC::getSize(cv::Size &size)
{
	size = this->_size;
	return CC::SUCCESS;
}

int VC::getFps(float &fps)
{
	fps = this->_fps;
	return CC::SUCCESS;
}
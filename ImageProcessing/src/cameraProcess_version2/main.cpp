#include "camera.h"

int myfun(cv::Mat mat, cv::Mat &mat_out)
{
	std::cout << "you succeed do myfun" << std::endl;
	return true;
}

int main(int argc, char const *argv[])
{
	std::thread t;
	Camera cam1("rtsp://admin:admin@192.168.1.169/cam/realmonitor?channel=1&subtype=0", 1, myfun);
	cam1.saveThread("data", 20, t);
	t.join();
	return 0;
}
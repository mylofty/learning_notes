#include "camera.h"
#include<thread>
int myfun(cv::Mat mat, cv::Mat &mat_out)
{
	std::cout << "you success to do myfun" << std::endl;	
	cv::flip(mat, mat_out, -1);
	return true;
}

int main(int argc, char const *argv[])
{
	Camera<std::string> cam1("rtsp://admin:admin@192.168.1.169/cam/realmonitor?channel=1&subtype=0", 1, myfun);
	// Camera<int> cam2(0, 2);

	// std::thread t1 = cam1.analysisThread();
	// std::thread t2 = cam1.saveAVIRealTimeThread("data", 20);
	std::thread t1 = cam1.saveAVIRealTimeThread("real2", 20);
	std::thread t2 = cam1.analysisThread("analysis2", 20);
	// cam1.analysis();
	t1.join();
	t2.join();
	return 0;
}
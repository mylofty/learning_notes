#include<camera.h>
#include<thread>


int main(int argc, char const *argv[])
{
	Camera<std::string> cam1("rtsp://admin:admin@192.168.1.108/cam/realmonitor?channel=1&subtype=0", 1);
	Camera<int> cam2(0, 2);

	// std::thread t1 = cam1.analysisThread();
	// std::thread t2 = cam1.saveAVIRealTimeThread("data", 20);
	std::thread t1 = cam1.saveAVIRealTimeThread("data", 20);
	std::thread t2 = cam2.analysisThread();
	// cam1.analysis();
	t1.join();
	t2.join();
	return 0;
}
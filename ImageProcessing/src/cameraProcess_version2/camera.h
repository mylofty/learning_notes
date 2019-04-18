#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "myVideoCapture.h"
class Camera
{
public: 
	Camera(std::string url, int, std::function<int(cv::Mat, cv::Mat &)> callback) ;
	int save(std::string folder, double during);
	int analysis();
	int saveThread(std::string folder, double during, std::thread &);
	int analysisThread();
private:
	int id;
	VC _vc;
	std::function<int(cv::Mat, cv::Mat &)> _analysisCallback;
};


#endif

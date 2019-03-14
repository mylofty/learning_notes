#include<stdio.h>
#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
// using namespace std;

int main(int argc, char const *argv[])
{
	cv::Mat A, C, D, E;
	A = cv::imread(argv[1], cv::IMREAD_COLOR);
	// std::cout << "Mat A is " << A << std::endl;    
	std::cout << "Mat A.rows is " << A.rows << ", Mat A.cols is " << A.cols \
		<< std::endl;
	std::cout << "Mat A channel is " << A.channels() << std::endl;
	std::cout << "Mat A.at<cv::Vec3b>(1, 1) = " << A.at<cv::Vec3b>(1,1) << std::endl;  // A.at<cv::Vec3b>(1, 1)  [37, 44, 61]
	
	cv::Mat B(A);
	C = A;
	D = A.clone();
	A.copyTo(E);
	std::cout << "A , B, C, D, E is " << A.at<cv::Vec3b>(1,1) << ", " << B.at<cv::Vec3b>(1,1) << ", " << C.at<cv::Vec3b>(1,1) \
		<< ", " << D.at<cv::Vec3b>(1,1) << ", " << E.at<cv::Vec3b>(1,1) << std::endl;
	// A , B, C, D, E is [37, 44, 61], [37, 44, 61], [37, 44, 61], [37, 44, 61], [37, 44, 61]
	cv::Vec3b point1_1;
	point1_1[0] = 0;	
	point1_1[1] = 0;	
	point1_1[2] = 0;
	A.at<cv::Vec3b>(1,1)  = point1_1;	
	std::cout << "A , B, C, D, E is " << A.at<cv::Vec3b>(1,1) << ", " << B.at<cv::Vec3b>(1,1) << ", " << C.at<cv::Vec3b>(1,1) \
		<< ", " << D.at<cv::Vec3b>(1,1) << ", " << E.at<cv::Vec3b>(1,1) << std::endl;
	//A , B, C, D, E is [0, 0, 0], [0, 0, 0], [0, 0, 0], [37, 44, 61], [37, 44, 61]

	//constructor
	cv::Mat M(20, 20, CV_8UC3, cv::Scalar(0,0,255));
	cv::imshow("M picture", M);
	int sz[3] = {2,2,2};
	cv::Mat L(3, sz, CV_8UC1, cv::Scalar::all(0));
	E = cv::Mat::eye(4, 4, CV_64F);
	cv::Mat O = cv::Mat::ones(2, 2, CV_32F);
	cv::Mat Z = cv::Mat::zeros(3, 3, CV_8UC1);
	std::cout << "E is " << E << std::endl;
	std::cout << "O is " << O << std::endl;
	std::cout << "Z is " << Z << std::endl;
	cv::waitKey(0);
	return 0;
}

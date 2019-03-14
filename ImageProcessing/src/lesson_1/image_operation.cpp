#include<opencv2/opencv.hpp>
#include<opencv2/core.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

int main(int argc, char * argv[])
{
	cv::Mat img = cv::imread("./imgs/index.jpg");
	std::cout << "img size is " << img.total() << std::endl;
	cv::imshow("origin img ", img);
	std::vector<int> encode_params;
	std::vector<uchar> img_encode_data;
	encode_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	encode_params.push_back(90);
	cv::imencode(".jpg", img, img_encode_data, encode_params);
	std::cout << "img_encode_data size is " << img_encode_data.size() << std::endl;
	std::cout << "img_encode_data[0] [1] [2] is " << int(img_encode_data[0]) << " , " << int(img_encode_data[1]) << " , " \
						<< int(img_encode_data[2]) << std::endl;
	cv::Mat decode_img;;
	decode_img = cv::imdecode(img_encode_data, CV_LOAD_IMAGE_COLOR);
	std::cout << "decode_img size is " << decode_img.total() << std::endl;
	cv::imshow("decode_img ", decode_img);
	std::vector<int> write_params;
	write_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	write_params.push_back(90);
	// write_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	// write_params.push_back(9);
	cv::imwrite("decode_img.jpg", decode_img, write_params);
	// cv::waitKey(0);
}

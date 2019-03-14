#include<opencv2/opencv.hpp>
#include<opencv2/core.hpp>

int main(int argc, char * argv[])
{
	cv::Mat src = cv::imread("./imgs/index.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat dst;
	double t = (double)cv::getTickCount();
	cv::Mat kernel = (cv::Mat_<char>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cv::filter2D(src, dst, src.depth(), kernel);
	t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
	std::cout << "time is " << t << " ms" << std::endl;
	cv::imshow("src", src);
	cv::imshow("dst", dst);
	cv::waitKey();
}

int main1(int argc, char * argv[])
{
	cv::Mat img = cv::imread("./imgs/index.jpg", CV_LOAD_IMAGE_COLOR);
	cv::imshow("origin img ", img);
	cv::Mat grayimg;
	cv::Mat sobelx;
	cv::Mat sobely;
	cv::cvtColor(img, grayimg, cv::COLOR_BGR2GRAY);
	cv::imshow("origin img ", grayimg);
	cv::Sobel(grayimg, sobelx, CV_32F, 1, 0);
	cv::Sobel(grayimg, sobely, CV_32F, 0, 1);
	double minValx, maxValx;
	cv::minMaxLoc(sobelx, &minValx, &maxValx);
	cv::Mat drawx;
	sobelx.convertTo(drawx, CV_8U, 255.0 / (maxValx - minValx), -minValx * 255.0 /(maxValx - minValx));;
	cv::imshow("drawx", drawx);

	cv::Mat drawx2, drawy2, draw2;
	convertScaleAbs(sobelx, drawx2);
	convertScaleAbs(sobely, drawy2);
	addWeighted(drawx2, 0.5, drawy2, 0.5, 0, draw2);
	cv::imshow("draw2", draw2);
	cv::waitKey();;


}
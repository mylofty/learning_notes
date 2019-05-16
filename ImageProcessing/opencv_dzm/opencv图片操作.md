# opencv基本操作
## 一、图片的读取
1、从文件中加载图片imread
```
Mat img = imread(filename); //默认IMREAD_COLOR，BGR三通道
Mat img2 = imread(filename, IMREAD_GRAYSCALE); //指定灰度图，单通道
```
2、图片显示：imshow
```
void cv::imshow(const String & winname, InputArray mat)
```
3、图片保持到文件：imwrite
```
	std::vector<int> write_params;
	write_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	write_params.push_back(90);
	// write_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	// write_params.push_back(9);
	cv::imwrite("decode_img.jpg", decode_img, write_params);
	// cv::waitKey(0);
```
2、图片编解码：imdecode, imencode
```
	cv::Mat img = cv::imread("./imgs/index.jpg");
	std::cout << "img size is " << img.total() << std::endl;
	cv::imshow("origin img ", img);
	std::vector<int> encode_params;
	std::vector<uchar> img_encode_data;
	encode_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	encode_params.push_back(90); //0-100 数字越小，压缩比率越高
	cv::imencode(".jpg", img, img_encode_data, encode_params);
	std::cout << "img_encode_data size is " << img_encode_data.size() << std::endl;
	std::cout << "img_encode_data[0] [1] [2] is " << int(img_encode_data[0]) << " , " << int(img_encode_data[1]) << " , " \
						<< int(img_encode_data[2]) << std::endl;
	cv::Mat decode_img;;
	decode_img = cv::imdecode(img_encode_data, CV_LOAD_IMAGE_COLOR);
	std::cout << "decode_img size is " << decode_img.total() << std::endl;
	cv::imshow("decode_img ", decode_img);
	cv::waitKey(0);
```
## 二、对图像进行卷积操作
```
	cv::Mat kernel = (cv::Mat_<char>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cv::filter2D(src, dst, src.depth(), kernel);
```
## 二、sobel算子使用
sobel算子是一种常见的边缘提取算子。通过一阶导数进行边缘提取，对x求一阶导数用来进行竖直检测，对y求一阶导数用来进行水平检测。这导致sobel算子更加适合横平竖直的图像边缘检测
常用函数如下：
1、读取图片之后需要将其变成灰度图：
```
cv::cvtColor(img, grayimg, cv::COLOR_BGR2GRAY);
```
2、 使用算子，sobel(src,dst, ddepth, dx, dy);
```
	cv::Sobel(grayimg, sobelx, CV_32F, 1, 0);
	cv::Sobel(grayimg, sobely, CV_32F, 0, 1);
```
3、由于sobel算子使用CV_32F，为了打印图片，需要将图片变为CV_8U
```
	convertScaleAbs(sobelx, drawx2);
	convertScaleAbs(sobely, drawy2);
	addWeighted(drawx2, 0.5, drawy2, 0.5, 0, draw2);//将两个方向的组合起来
```
也可以使用convertTo函数进行格式转换
```
	double minValx, maxValx;
	cv::minMaxLoc(sobelx, &minValx, &maxValx);
	cv::Mat drawx;
	sobelx.convertTo(drawx, CV_8U, 255.0 / (maxValx - minValx), -minValx * 255.0 /(maxValx - minValx));;
```
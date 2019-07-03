## 1、resize
```
	int row = (int)(img.rows / scales);  // resize 后大小
	int col = (int)(img.cols / scales);

	cv::Mat dst(row， col , img.type());
	cv::reszie(img, dst, dst.size(), 0, 0, cv::INTER_LINEAR);
```

# opencv 基础一
## 一、Mat
1、早期的opencv管理图片使用的是结构体IplImage (Image processing Library Image)，然而，跟大多数C程序一样，需要用户手动分配和回收内存，容易出错，不利于程序小型化。

2、Mat是一个C++类，使用者不需要手动去分配和回收内存，（当然早期的代码有的仍然先用IplImage分配内存），Mat包含两部分：(1).矩阵头部（包括矩阵大小，存储位置等），(2).指向内存中像素点的指针

3、**内存管理:** Mat类包含header和pointer，其中，pointer指向一个堆，Mat类管理的图片像素矩阵其实存在这个区域，所以，当进行**复制**和**赋值**操作时，副本中仅仅生成新的header和pointer，图片像素矩阵不会拷贝一份(**浅拷贝**)，pointer类似使用智能指针，通过增加引用计数的方式，只有计数为0才会删除像素内存，所以O（1）时间完成拷贝。
```c++
Mat A, C;
A = imread(argv[1], IMREAD_COLOR);
Mat B(A);  		// 调用拷贝构造函数，不复制图像内存
C = A;			// 执行赋值操作，不复制图像内存
```
若是需要拷贝图片像素矩阵，则需要使用**cv::Mat::clone() ** 和 ** cv::Mat::copyTo() ** 函数
```
Mat F = A.clone();
Mat G;
A.copyTo(G);
```

4、Mat常用构造方法
（1）、构建二维矩阵
```c++
Mat M(20, 20, CV_8UC3, Scalar(0,0,255))  
// 构建20×20图像，每个像素8bit， 3通道， 初始化为（0,0,255），BGR 红色
// CV_8UC3 变量并未定义在cv命名空间中， opencv2/core/hal/interface.h
cv::imshow("M picture", M);
```
（2）、构建多维矩阵
```
cv::Mat L(3, sz, CV_8UC1, cv::Scalar(0));
// 多维矩阵无法cout和imshow，没有重载
```
（3）、创建固定形式矩阵
```
Mat E = Mat::eye(4, 4, CV_64F);
Mat o = Mat::ones(2, 2, CV_32F);
Mat Z = Mat::zeros(3, 3, CV_8UC1);
```
**构造一个跟已有图片一样大小类型的mat**
```
Mat dst = Mat::ones(src.size(), src.type());
```
（4）、从image构造Mat
```c++
Mat img = imread(filename);   // 默认构造三通道图片     IMREAD_COLOR
Mat img = imread(filename, IMREAD_GRAYSCALE);   //指定单通道
```

## 二、Mat 读写像素值
Mat矩阵主要有三种遍历方式：**C指针访问、迭代器访问、随机访问**，图片连续存储下，通常访问速度 C指针(推荐） > 迭代器（安全） > 随机访问（不推荐）
```c++
//! [scan-c]
Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    int channels = I.channels();

    int nRows = I.rows;
    int nCols = I.cols * channels;

    if (I.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i,j;
    uchar* p;
    for( i = 0; i < nRows; ++i)
    {
        p = I.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            p[j] = table[p[j]];
        }
    }
    return I;
}
//! [scan-c]

//! [scan-iterator]
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch(channels)
    {
    case 1:
        {
            MatIterator_<uchar> it, end;
            for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
                *it = table[*it];
            break;
        }
    case 3:
        {
            MatIterator_<Vec3b> it, end;
            for( it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
            {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
        }
    }

    return I;
}
//! [scan-iterator]

//! [scan-random]
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch(channels)
    {
    case 1:
        {
            for( int i = 0; i < I.rows; ++i)
                for( int j = 0; j < I.cols; ++j )
                    I.at<uchar>(i,j) = table[I.at<uchar>(i,j)];
            break;
        }
    case 3:
        {
         Mat_<Vec3b> _I = I;

         for( int i = 0; i < I.rows; ++i)
            for( int j = 0; j < I.cols; ++j )
               {
                   _I(i,j)[0] = table[_I(i,j)[0]];
                   _I(i,j)[1] = table[_I(i,j)[1]];
                   _I(i,j)[2] = table[_I(i,j)[2]];
            }
         I = _I;
         break;
        }
    }

    return I;
}
//! [scan-random]
```

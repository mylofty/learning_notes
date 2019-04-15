# opencv 准备
## 一、安装opencv
1、去官网下载opencv压缩包，解压之后进入文件夹目录
change by master branch
2、执行下面脚本
```shell
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/home/dzm/opencv3 ..
make
make install
```

## 二、编译opencv代码
### 1、使用pkg-config链接opencv库
pkg-config是一个向用户程序提供相应库的路径，版本号等信息的程序， 默认在/usr/lib/pkgconfig目录下寻找test.pc文件，若是找不到，则会在**PKG_CONFIG_PATH**这个环境变量下寻找，所以可以将opencv的pkgconfig添加到该环境变量中
```shell
export PKG_CONFIG_PATH=/home/dzm/opencv3_4/lib64/pkgconfig:$PKG_CONFIG_PATH
```
执行命令**pkg-config -libs --cflags opencv**得到
```
-I/home/dzm/opencv3_4/include/opencv -I/home/dzm/opencv3_4/include -L/home/dzm/opencv3_4/lib64 -lopencv_dnn -lopencv_ml -lopencv_objdetect -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core
```
可见，这就是编译程序使用需要include和link的文件
于是，编译程序时可以执行一下命令
```
g++ -o main.o first.cpp `pkg-config opencv --cflags --libs`
```
编译成功，运行时需要增加链接库目录，可以通过设置环境变量
```
export LD_LIBRARY_PATH=$:/home/dzm/opencv3_4/lib64
```
运行成功
## 2、makefile使用pkg-config
```
CFLAGS=`pkg-config -cflags opencv`
LIBS=`pkg-config -libs opencv`

main.o: main.cpp
	g++ -o main.o main.cpp $(CFLAGS) $(LIBS) 
```
编译成功，运行时需要增加链接库目录，可以通过设置环境变量
```
export LD_LIBRARY_PATH=$:/home/dzm/opencv3_4/lib64
```
运行成功

## 3、makefile手动添加opencv库
```
INCLUDES = -I/home/dzm/opencv3_4/include
LIBS = -lopencv_core -lopencv_imgproc -lopencv_highgui
LIBDIRS = -L/home/dzm/opencv3_4/lib64

main.o : main.cpp
	g++ -o main.o main.cpp $(INCLUDES) $(LIBDIRS) $(LIBS)
```
编译成功，运行时需要增加链接库目录，可以通过设置环境变量
```
export LD_LIBRARY_PATH=$:/home/dzm/opencv3_4/lib64
```
运行成功


**tips**: 以上方法编译成功之后，可执行文件运行时仍可能找不到so文件，当so文件不在系统默认路径（/lib 和 /lib64）之下时，需要增加LD_LIBRARY_PATH，当不能修改path时，可以在g++中添加命令**-Wl, -rpath=$(SOPATH)**
```
INCLUDES = -I/home/dzm/opencv3_4/include
LIBS = -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs
LIBDIRS = -L/home/dzm/opencv3_4/lib64
SOPATH = /home/dzm/opencv3_4/lib64

all: pixel_scan.o mat.o
pixel_scan.o : pixel_scan.cpp
	g++ -o pixel_scan.o pixel_scan.cpp $(INCLUDES) $(LIBDIRS) $(LIBS) -Wl,-rpath=$(SOPATH)
mat.o : mat.cpp
	g++ -o mat.o mat.cpp $(INCLUDES) $(LIBDIRS) $(LIBS)

.PHONY: clean
clean:
	rm *.o
```

## 4、运行时问题
当运行时遇到以前所说问题之时，可以考虑将库文件（.so）目录添加至系统目录
系统链接库目录是在/etc/ld.so.conf中，该文件引用/etc/ld.so.conf.d/中的所有conf文件，所以，只需要增加一个conf文件，将/home/dzm/opencv3_4/lib64保存其中。之后执行sudo ldconfig完成修改即可




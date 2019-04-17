# docker 使用
## 二、docker基本用法
### 1、查看docker状态
```
sudo docker images 	//查看docker中已有的镜像
sudo docker ps			//查看正在运行的容器
sudo docker ps -a		//查看所有本地容器
sudo docker inspect docker_name	//查看某个docker的信息
sudo docker diff docker_name		//查看某个docker的改动
```
apt-get install libopencv-dev build-essential cmake git libgtk2.0-dev pkg-config  python-dev python-numpy libdc1394-22 libdc1394-22-dev libjpeg-dev libpng12-dev libtiff4-dev libjasper-dev libavcodec-dev libavformat-dev libswscale-dev libxine-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev libtbb-dev libqt4-dev libfaac-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev x264 v4l-utils unzip
下載　ippicv_2019_lnx_intel64_general_20180723.tgz

手動下載　 ippicv_2019_lnx_intel64_general_20180723.tgz

docker默认目录 /var/lib/docker, 该目录下images保存本地镜像，containers保持本地已经创建的容器
###2、docker容器使用
(1) 新建docker容器
```
sudo docker run -it --name cameraDemo --hostname ding debian /bin/bash
```
该命令创建了一个命名为cameraDemo的docker容器，指定容器内主机名为ding，该容器以本地或者docker云上的debian镜像为基础搭建，创建后打开容器的bash伪终端
```
sudo docker run debian echo "ddd"  //该方法会用debian镜像创建一个容器，然后执行echo后exit，系统中已经存在了该容器，虽不占用内存，最好删除一次（若不生成为镜像）
```
(2) 启动已经存在的docker
```
sudo docker start docker_name/id
```
(3) 进入已经启动的docker，同时启动bash
```
sudo docker exec -it docker_name/id /bin/bash
```
(4) 关闭启动的docker
```
sudo docker stop docker_name/id
```
(5) 清除单个容器
```
sudo docker rm docker_name/id
```
(6) 清除所有已经停止的容器
```
sudo docker rm -v $(sudo docker ps -aq -f status=exited)
```
(7) 容器与主机传数据
```
sudo docker cp image.png cowsay:/ 			//主机拷贝到cowsay容器/目录
sudo docker cp image.png cowsay:/				//容器拷贝到主机当前目录
```
### 3、docker镜像处理一
(1) 查找镜像
```
sudo docker search keyworks
```
(2) 拉取镜像
```
sudo docker pull docker_images
```
docker run在本地没有镜像的情况下会默认去拉取镜像
(3) 发布镜像
```
sudo  docker login		//首先登录自己的帐号密码，在hub中先建立好仓库opencv3
sudo docker push zhiminding/opencv3 
```
dzm_repo为docker hub用户的用户名，必须是本人，否则无法push

(4) 删除镜像
```
sudo docker rmi docker_image_name
```
该镜像必须已经没有容器，否则先删除容器。同时，先删除下层镜像，最后删除顶层镜像

### 3、docker镜像处理二：创建镜像
(1) 将容器commit成镜像（先关闭容器）
```
sudo docker commit opencv3_ubuntu16 zhiminding/opencv3_ubuntu16
```
在此镜像上设置网络之后再开一个容器
```
sudo docker run --net=host --name opencv3_ubuntu16_2 -h sysu -i -t zhiminding/opencv3_ubuntu16  /bin/bash
```


### 4、镜像导出与导入
(1) 镜像导出
```
sudo docker save -o camera_images.tar zhiminding/camera_opencv3_ubuntu16
```
(2) 镜像导入
```
sudo docker load --input ./camera_images.tar
```







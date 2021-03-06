# docker 使用
## 一、离线安装docker
1、了解官网资料https://docs.docker.com/install/linux/docker-ce/binaries/
下载docker安装包https://download.docker.com/linux/static/stable/x86_64/
从其中选择docker-18.06.1-ce.tgz
2、解压安装包
```
tar -xzvf docker-18.06.1-ce.tgz
```
3、将解压的文件均复制到/usr/bin目录下
```
sudo cp docker/* /usr/bin/

```
4、开启docker守护进程
```
sudo dockerd &
```
5、验证是否成功
```
sudo docker version
```
若是输出以下内容则成功
Client:
 Version:           18.06.1-ce
 API version:       1.38
 Go version:        go1.10.3
 Git commit:        e68fc7a
 Built:             Tue Aug 21 17:20:43 2018
 OS/Arch:           linux/amd64
 Experimental:      false

Server:
 Engine:
  Version:          18.06.1-ce
  API version:      1.38 (minimum version 1.12)
  Go version:       go1.10.3
  Git commit:       e68fc7a
  Built:            Tue Aug 21 17:28:38 2018
  OS/Arch:          linux/amd64
  Experimental:     false

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

### 5、docker run命令参数
```
-a stdin: 指定标准输入输出内容类型，可选 STDIN/STDOUT/STDERR 三项；

-d: 后台运行容器，并返回容器ID；

-i: 以交互模式运行容器，通常与 -t 同时使用；

-p: 端口映射，格式为：主机(宿主)端口:容器端口

-t: 为容器重新分配一个伪输入终端，通常与 -i 同时使用；

--name="nginx-lb": 为容器指定一个名称；

--dns 8.8.8.8: 指定容器使用的DNS服务器，默认和宿主一致；

--dns-search example.com: 指定容器DNS搜索域名，默认和宿主一致；

-h "mars": 指定容器的hostname；

-e username="ritchie": 设置环境变量；

--env-file=[]: 从指定文件读入环境变量；

--cpuset="0-2" or --cpuset="0,1,2": 绑定容器到指定CPU运行；

-m :设置容器使用内存最大值；

--net="bridge": 指定容器的网络连接类型，支持 bridge/host/none/container: 四种类型；

--link=[]: 添加链接到另一个容器；

--expose=[]: 开放一个端口或一组端口；

-v , --volume=[] : 挂载目录( -v /realcomputer_data:/opt/temp)
```






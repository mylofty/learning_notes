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

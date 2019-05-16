# Tars安装与第一个demo
## 一、启动tars images
tars使用首先可以依靠mysql的docker以及tars的docker：
https://hub.docker.com/r/tarscloud/tars
**然而，上面的方法找不到mysql，我将两个docker的网络均设置为--net="host"便可以了**
```bash
docker run -d -it --name tars -p 3000:3000     -v /home/dzm/workspace/tars_data:/data tarscloud/tars:dev
#上一条命令在我的电脑上无法打开mysql，导致报错，可以使用下面两条命令
sudo docker run --name tars-mysqld --detach --net=host -e TZ=Asia/Shanghai -e MYSQL_ROOT_PASSWORD=password -v /home/dzm/tars/mysql_data:/var/lib/mysql mysql:5.6
sudo docker run --name tars --detach --net=host -e INET_NAME=ens33 -e DBIP=192.168.1.108 -e DBPort=3306 -e DBUser=root -e DBPassword=password -v /home/dzm/tars/tars_data:/data tarscloud/tars:dev
```
[快速安装教程](https://github.com/maq128/temp/blob/master/kb/tars%E5%B0%8F%E7%99%BD%E5%AE%89%E8%A3%85%E5%BF%85%E6%88%90%E6%89%8B%E5%86%8C.md) 
之后进入docker进行开发
```bash
sudo docker exec -it tars2 bash
```

## 二、第一个demo
### 1、创建工程
```sh
#将create自动化脚本设置为可执行
chmod +x /usr/local/tars/cpp/script/create_tars_server.sh 
#利用自动化脚本创建服务，需要包括应用、服务、接口
#/usr/local/tars/cpp/script/create_tars_server.sh [App] [Server] [Servant]
/usr/local/tars/cpp/script/create_tars_server.sh TestAPP Helloserver printHello
```
该脚本在/data/TestAPP/Helloserver目录下生成了一些服务框架文件
```sh
[dzm@dzm Helloserver]$ pwd
/home/dzm/workspace/tars_data/TestAPP/Helloserver
[dzm@dzm Helloserver]$ ls
Helloserver.cpp  makefile           printHelloImp.h
Helloserver.h    printHelloImp.cpp  printHello.tars
```
打开printHelloImp.h可以发现，该文件引用了include<printHello.h>，并且，printHelloImp类继承了printHello类。然而，目录下并没有printHello.h，我们需要依靠printHello.tars自动生成该文件。
```sh
usr/local/tars/cpp/tools/tars2cpp printHello.tars
```
由该printHello.h文件可以看出，printHello这个接口的基本方法已经通过自动化脚本生成了，而一些需要用户定义的方法通过tars文件让用户自定义，并且，用户自定义的方法再通过子类printHelloImp继承printHello，让用户去实现
### 2、添加接口新方法
接下来我们在接口文件printHelloImp.h和 printHelloImp.cpp中添加一个printTest方法
 **首先必须在tars文件中增加接口的方法，该文件能够自动生成新的printHello.h**
 tars文件如下定义
```
 module TestAPP
{

	interface printHello
	{
	    int test();
	    int printTest(string sReq, out string sRsp);			//添加新方法，方法有标准定义格式
	};

}; 
```
执行自动化脚本创建新的printHello.h
```sh
usr/local/tars/cpp/tools/tars2cpp printHello.tars
```
新的printHello.h将我们tars文件中定义的方法以virtual虚函数的形式添加到了printHello类中，
```
/* servant for server */
    class printHello : public tars::Servant
    {
    public:
        virtual ~printHello(){}
        virtual tars::Int32 printTest(const std::string & sReq,std::string &sRsp,tars::TarsCurrentPtr current) = 0;
        static void async_response_printTest(tars::TarsCurrentPtr current, tars::Int32 _ret, const std::string &sRsp)
        {
            if (current->getRequestVersion() == TUPVERSION )
            {
                UniAttribute<tars::BufferWriter, tars::BufferReader>  tarsAttr;
                tarsAttr.setVersion(current->getRequestVersion());
                tarsAttr.put("", _ret);
                tarsAttr.put("sRsp", sRsp);

                vector<char> sTupResponseBuffer;
                tarsAttr.encode(sTupResponseBuffer);
                current->sendResponse(tars::TARSSERVERSUCCESS, sTupResponseBuffer);
            }
            else
            {
                tars::TarsOutputStream<tars::BufferWriter> _os;
                _os.write(_ret, 0);

                _os.write(sRsp, 2);

                current->sendResponse(tars::TARSSERVERSUCCESS, _os.getByteBuffer());
            }
        }
```

之后我们需要在继承该类的实现类testHelloImp中实现该方法。
```
########### testHelloImp.h#############
virtual int printTest(const std::string &Req, std::string &Rsp, tars::TarsCurrentPtr current);  //千万不能漏了const
############ testHelloImp.cpp#########
int printHelloImp::printTest(const std::string &Req, std::string &Rsp, tars::TarsCurrentPtr current)
{
	std::cout << "you send to service " << Req << std::endl;
	Rsp = Req;
	return -1;
}
```

### 3、编译服务代码
```
make cleanall    //cleanall会清除tars2cpp生成的printHello.h
make
make tar     	//生成HelloServer.tgz
```

### 4、部署服务代码
上一步生成的HelloServer.tgz服务代码的压缩包其他应用将无法访问，为此，需要将其部署，以便其他服务程序对其进行访问
```
make release
```
```
[root@dzm Helloserver]# make release
[No such dir: /home/tarsproto/TestAPP/Helloserver, now we create it.]
[Copy file  printHello.tars printHello.h [Mm]akefile  ->  /home/tarsproto/TestAPP/Helloserver]
‘printHello.tars’ -> ‘/home/tarsproto/TestAPP/Helloserver/printHello.tars’
‘printHello.h’ -> ‘/home/tarsproto/TestAPP/Helloserver/printHello.h’
‘makefile’ -> ‘/home/tarsproto/TestAPP/Helloserver/makefile’
echo "INCLUDE += -I/home/tarsproto/TestAPP/Helloserver"  >  /home/tarsproto/TestAPP/Helloserver/Helloserver.mk;

```
之后其他服务只需要在makefile中引用如下，即可以对服务进行访问
```
include /home/tarsproto/TestApp/HelloServer/HelloServer.mk
```
### 5、线上发布
进入192.168.1.105:300的web管理平台添加服务，上传tgz文件即可。

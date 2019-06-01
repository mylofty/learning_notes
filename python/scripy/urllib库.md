# urllib库学习
## 1、介绍
Urllib是python内置HTTP请求库。包括如下模块
（1）、urllib.request 请求模块
（2）、urllib.error 异常处理模块
（3）、urllib.parse url解析模块
（4）、urllib.robotparser robots.txt解析模块
## 2、urllib.request模块主要功能
### (1) urllib.request.urlopen函数
（使用时必须要全写http://，不能只写www....）
urlopen函数，包括三个参数：
```
http.client.HTTPResponse rs = urllib.request.urlopen(url,data,timeout)
```
该函数也可以写出如下格式：
```
import urllib.request
request = urllib.request(url,data)
response = urllib.request.urlopen(request)
```
当data参数没有时，视为get方法（https://www.baidu.com/s?ie=UTF-8&wd=%E6%B7%98%E5%AE%9D)，有data时视为post方法。data数据必须要转码为urlopen识别的格式：
```
import urllib.request
import urllib.parse
data = {'word':'hello'}
data_urlencode = urllib.parse.urlencode(data)
data_byte = bytes(data_urlencode,encoding='utf-8')
response = urllib.request.urlopen('http://httpbin.org/post', data=data)
	      print(response.read())
```
该函数返回一个http.client.HTTPResponse的类，注意，这个类只包括包头信息（header）并没有去获取数据包正文部分，必须调用read()函数之后才会获取正文
### (2) HttpResponse类里面的函数
```
rs = urllib.request.urlopen("http://www.baidu.com")
rs.read()  #获取报文body部分 print(rs.read(200));即打印内容前200字节
-->此处获得的是Unicode码，要转换格式，如print(rs.read().decode('utf-8'));
rs.status  #获取报文状态码
rs.reason #返回OK
rs.getheaders() #返回头部 print(rs.status,rs.reason,rs.getheaders())
```
### (3) request.Request用法
有时直接用urllib.request.urlopen不行，比如要插入headers或者其他东西的时候，这个时候就要用request.Request
```
class urllib.request.Request(url, data=None, headers{}, origin_req_host=None, unverifiable=False, method=None)
```
(a)、设置Headers
```
headers = {
   		 'User-Agent': 'Mozilla/4.0 (compatible; MSIE 5.5; Windows NT)',
   		 'Host': 'httpbin.org'
		}
req = request.Request(url=url,headers = headers,method='POST');
//或者
req = request.Request(url=url, data=data, method='POST')
req.add_header('User-Agent','Mozilla/4.0 (compatible; MSIE 5.5; Windows NT')
```
(b)、设置cookie
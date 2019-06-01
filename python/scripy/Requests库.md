# Requests库
Requests库继承自apache的http库，该库是最简单的Http库，爬虫建议使用该库

该库的功能：
- Keep-Alive & 连接池
- 国际化域名和 URL
- 带持久 Cookie 的会话
- 浏览器式的 SSL 认证
- 自动内容解码
- 基本/摘要式的身份认证
- 优雅的 key/value Cookie
- 自动解压
- Unicode 响应体
- HTTP(S) 代理支持
- 文件分块上传
- 流下载
- 连接超时
- 分块请求
- 支持 .netrc
 


# 一、各种请求方式(get,post,head,delete...)
## get方式
带参数的get方式：
```
payload = {'key1': 'value1', 'key2': 'value2'}
r = requests.get("http://httpbin.org/get", params=payload)
```
Requests 会自动解码来自服务器的内容。大多数 unicode 字符集都能被无缝地解码

请求发出后，Requests 会基于 HTTP 头部对响应的编码作出有根据的推测。当你访问 r.text 之时，Requests 会使用其推测的文本编码。你可以找出 Requests 使用了什么编码，并且能够使用 r.encoding 属性来改变它。

带头部信息
```
import requests
headers = {

    "User-Agent":"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36"
}
response =requests.get("https://www.zhihu.com",headers=headers)

print(response.text)
```



## post请求
*此处data数据不需要编码，requests会自动把数据编码成所需的表单格式*
```
import requests

data = {
    "name":"zhaofan",
    "age":23
}
response = requests.post("http://httpbin.org/post",data=data)
print(response.text)
```
# requests函数参数
- method -- method for the new Request object.
- url -- URL for the new Request object.
- params -- (optional) Dictionary or bytes to be sent in the query string for the Request.
- data -- (optional) Dictionary or list of tuples [(key, value)] (will be form-encoded), bytes, or file-like object to send in the body of the Request.
- json -- (optional) json data to send in the body of the Request.
```
import requests

data = {
    "name":"zhaofan",
    "age":23
}
response = requests.post("http://httpbin.org/post",json=data)
print(response.text)
```
- headers -- (optional) Dictionary of HTTP Headers to send with the Request.
- cookies -- (optional) Dict or CookieJar object to send with the Request.
```
要想发送你的cookies到服务器，可以使用 cookies 参数：

>>> url = 'http://httpbin.org/cookies'
>>> cookies = dict(cookies_are='working')

>>> r = requests.get(url, cookies=cookies)
>>> r.text
'{"cookies": {"cookies_are": "working"}}'
```
- files -- (optional) 
    
    Dictionary of 'name': file-like-objects (or {'name': file-tuple}) for multipart encoding upload. file-tuple can be a 2-tuple ('filename', fileobj), 3-tuple ('filename', fileobj, 'content_type') or a 4-tuple ('filename', fileobj, 'content_type', custom_headers), where 'content-type' is a string defining the content type of the given file and custom_headers a dict-like object containing additional headers to add for the file.
```
url = 'http://httpbin.org/post'
files = {'file': open('report.xls', 'rb')}
r = requests.post(url, files=files)
r.text

#你可以显式地设置文件名，文件类型和请求头：

url = 'http://httpbin.org/post'
files = {'file': ('report.xls',open('report.xls','rb'),'application/vnd.ms-excel', {'Expires': '0'})}
r = requests.post(url, files=files)
r.text
#{
#  ...
#  "files": {
#    "file": "<censored...binary...data>"
#  },
#  ...
#}
```
- auth -- (optional) Auth tuple to enable Basic/Digest/Custom HTTP Auth.
- timeout (float or tuple) -- (optional) 
        
    How many seconds to wait for the server to send data before giving up, as a float, or a (connect timeout, read timeout) tuple.
- allow_redirects (bool) -- (optional) Boolean. 
    
    Enable/disable GET/OPTIONS/POST/PUT/PATCH/DELETE/HEAD redirection. Defaults to True.
- proxies -- (optional) Dictionary mapping protocol to the URL of the proxy.
- verify -- (optional) 
    
    Either a boolean, in which case it controls whether we verify the server's TLS certificate, or a string, in which case it must be a path to a CA bundle to use. Defaults to True.
    
- stream 

    -- (optional) if False, the response content will be immediately downloaded.
- cert -- (optional) if String, path to ssl client cert file (.pem). If Tuple, ('cert', 'key') pair.
- 

# response对象
response对象是requests的返回值
```
response = requests.get("http://httpbin.org/get")
```
response对象包含下列成员
- content 
    
    Content of the response, in bytes.
- cookies = None 

   A CookieJar of Cookies the server sent back.
- encoding = None 

    Encoding to decode with when accessing r.text.
- headers = None

    Case-insensitive Dictionary of Response Headers. For example, headers['content-encoding'] will return the value of a 'Content-Encoding' response header.
- json(**kwargs)
Returns the json-encoded content of a response, if any.
    
    参数:	**kwargs -- Optional arguments that json.loads takes.
    
    引发:	ValueError -- If the response body does not contain valid json.
- text

    Content of the response, in unicode.
- url = None

    Final URL location of Response.
## 获取正文 --rs.text
*自动根据检测到的编码进行转码*
```
import requests
response = requests.get("www.baidu.com") 
print(response.text)
```
## 获取json --rs.json()  *必须加括号*
```
import requests
import json
response = requests.get("http://httpbin.org/get")
print(type(response.text))
print(response.json())
print(json.loads(response.text))
print(type(response.json()))
```
## 获取二进制数据 --rs.content
```
import requests
rs = requests.get('http://www.baidu.com')
print(rs.text)
print(rs.content)
```
## 获取其他属性
```
import requests
 
response = requests.get("http://www.baidu.com")
print(type(response.status_code),response.status_code)
print(type(response.headers),response.headers)
print(type(response.cookies),response.cookies)
print(type(response.url),response.url)
print(type(response.history),response.history)
```
# requests高级用法

# 简介
Beautiful Soup 4 是一个可以从HTML或XML文件中提取数据的Python库
# beautifulsoup对象
```
from bs4 import BeautifulSoup
soup = BeautifulSoup(open("index.html",'lxml')
# 推荐自己定义解析器lxml
soup2 = BeautifulSoup("<html>data</html>")
```
该对象直接返回的是Unicode码 print(soup)
## 用soup对象获取对好格式的html的string
        print(soup.prettify())
## 用soup选择标签（tag）
- title标签
    
        tag=soup.title 

    该方法只获取找到的第一个该标签,要找多项，要用到标签选择器
- head标签
- p标签
- ..
```
soup = BeautifulSoup(html,'lxml')
htmlstr = soup.prettify()
title = soup.title
p = soup.p
head = soup.head
print(type(head),head)
print(p)
# ans: <class 'bs4.element.Tag'> <head><title>The Dormouse's story</title></head><pclass="title"><b>The Dormouse's story</b></p>
```
# Tag对象
```
soup = BeautifulSoup('<b class="boldest">Extremely bold</b>','xml')
tag = soup.b
type(tag)
# <class 'bs4.element.Tag'>
```
## 获取名称
    soup.title.name
    
    返回title

## 获取属性
由于标签里面的属性

如tag <b class="boldest"> 有一个 “class” 的属性,值为 “boldest”
```
tag['class']

或者
tag.attrs['class']
或者
tag.attrs 获得所有属性
# ans: u'boldest'
```
## 获取内容
    print(soup.p.string)
    
    结果就可以获取第一个p标签的内容：
    
    The Dormouse's story
## 嵌套选择

我们直接可以通过下面嵌套的方式获取

    print(soup.head.title.string)

# 标签选择器
## find_all
find_all(name,attrs,recursive,text,**kwargs)

可以根据标签名，属性，内容查找文档（soup)

- name参数
```
print(soup.find_all('a'))
for ip in soup.find_all('a'):
    print(ip)
# ans:
#<a class="sister" href="http://example.com/elsie" id="link1">Elsie</a>
#<a class="sister" href="http://example.com/lacie" id="link2">Lacie</a>
#<a class="sister" href="http://example.com/tillie" id="link3">Tillie</a>
```

- attrs参数
```
print(soup.find_all(attrs={'id': 'list-1'}))
print(soup.find_all(attrs={'name': 'elements'}))
```
- text
```
print(soup.find_all(text='Foo'))
# ans:结果返回的是查到的所有的text='Foo'的文本
```
## find
        find(name,attrs,recursive,text,**kwargs)
find返回的匹配结果的第一个元素

# 其他一些类似的用法：
find_parents()返回所有祖先节点，find_parent()返回直接父节点。

find_next_siblings()返回后面所有兄弟节点，find_next_sibling()返回后面第一个兄弟节点。

find_previous_siblings()返回前面所有兄弟节点，find_previous_sibling()返回前面第一个兄弟节点。

find_all_next()返回节点后所有符合条件的节点,
find_next()返回第一个符合条件的节点

find_all_previous()返回节点后所有符合条件的节点,

find_previous()返回第一个符合条件的节点

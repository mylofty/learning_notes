
# python numpy 基本操作

**numpy** array称之为ndarray,numpy的ndarray与python的array不同。python array.array是一个一维数组，np.array是一个多维数组，每一维称之为轴（axes）
## 1、np.array构造函数

### (1)、利用np.array函数创建np.array
 numpy.array(object, dtype=None, copy=True, order='K', subok=False, ndmin=0)


```python
import numpy as np
a = np.array([2,3,4])
print(a)
print(type(a))
print(a.dtype)
print(a.shape)
print('a[0]is ',a[0])
#print('a[0][1]is',a[0][1])    is wrong
```

    [2 3 4]
    <class 'numpy.ndarray'>
    int32
    (3,)
    a[0]is  2
    

**注意** ： 不能省略方括号而直接插入序列 如 np.array(2,3,4)


```python
#构建二维数组
b = np.array([[1,2,3],[4,5,6]],dtype = np.int16)
print(b)
print('b shape is',b.shape)
print('b[0] is',b[0])
print('b[0]type is',type(b[0]))
print('b[0] dtype is',b[0].dtype)
```

    [[1 2 3]
     [4 5 6]]
    b shape is (2, 3)
    b[0] is [1 2 3]
    b[0]type is <class 'numpy.ndarray'>
    b[0] dtype is int16
    

**注意** 此处是插入的  \[ \[\] , \[\] \]


```python
#用range产生list
c= np.array( range(0,100) )
print(c)
```

    [ 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
     25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49
     50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74
     75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99]
    

### (2)、利用占位符构造数组
**zeros 函数构造初始值为0的数组**


```python
zero = np.zeros( (3,4))              #由于是占位符，只表示空间，所以zeros里面用小括号括起来
zero2 = np.zeros(3)                  #np.zeros构造的是数组，所以可以用该函数构造一维数组
print(zero)
print(zero2)
```

    [[ 0.  0.  0.  0.]
     [ 0.  0.  0.  0.]
     [ 0.  0.  0.  0.]]
    [ 0.  0.  0.]
    

**ones函数构造初始值为1的数组**


```python
one = np.ones( (2,4),dtype = int)
print(one)
```

    [[1 1 1 1]
     [1 1 1 1]]
    

**empty函数构造初始值随机的数组，默认类型为float64**


```python
empty = np.empty((2,5))
print(empty)
```

    [[  2.12199579e-314   0.00000000e+000   2.12199579e-314   1.42418987e-306
        1.50200295e-307]
     [  4.67296746e-307   1.69121096e-306   1.29062568e-306   1.42419938e-306
        7.56603881e-307]]
    

### （3）、通过随机数函数random生成给定大小的数组
此处有很多np.random库中的函数，由于np.random是numpy中的random库，所以大部分函数都是操作ndarray格式的，不详细列举


```python
rand = 10*np.random.random((2,4))
print(rand)
randint = np.floor(rand)
print(randint)
randi = np.random.randint(3,high = 6,size=10)                #最小值为3，最大值不大于6，size为10的随机均为分布
print(randi)
randi2 = np.random.randint(5,size=(2,4))                     #当不提供high属性时，给定的参数为最大值不大于5.
print(randi2)

```

    [[ 9.69936167  4.35667075  6.81937385  8.76402435]
     [ 2.95693062  1.50591608  5.02003945  5.43058465]]
    [[ 9.  4.  6.  8.]
     [ 2.  1.  5.  5.]]
    [5 3 5 3 5 5 5 3 3 3]
    [[1 3 2 3]
     [3 1 0 4]]
    

### (4)、利用arange函数创建等差数组直接产生array


```python
arange1 = np.arange(6)         # 按序生成0-6的数组
print(arange1)
arange = np.arange(10,30,5)
print(arange)
print(arange.dtype)
print(arange.size)
```

    [0 1 2 3 4 5]
    [10 15 20 25]
    int32
    4
    

## 2、np.array形状操作

### (1)、numpy.reshape函数
numpy.reshape(a, newshape, order='C') 

**a** ：需要reshape的数组

**newshape**：需要转变成的格式，如(2,3),即2行3列。若是**（2，-1），则表示输出两行，列数根据数组元素个数和给定的行数计算出来**

**order**:输出的风格，如C风格


```python
reshape = np.arange(6).reshape((3,2)) #reshape的行列必须保证与原数组大小相同
print(reshape)
reshape2 = np.reshape(reshape,(2,3))
print(reshape2)
reshape3 = np.reshape(reshape2,(3,-1))
print(reshape3)
```

    [[0 1]
     [2 3]
     [4 5]]
    [[0 1 2]
     [3 4 5]]
    [[0 1]
     [2 3]
     [4 5]]
    

**注意：** reshape之后，要注意reshape后与原数组共享内存,无论是否连续切片


```python
orgin = np.arange(16).reshape((4,4))
print('orgin is',orgin)
orgin_reshape1 = orgin[:,0].reshape((2,2))
print('orgin_shape1 is',orgin_reshape1)
orgin_reshape2 = orgin[0,:].reshape(2,2)
print('orgin_shape2 is',orgin_reshape2)
print('orgin 和 orgin_reshape1 共享内存吗？',np.may_share_memory(orgin,orgin_reshape1))
print('orgin 和 orgin_reshape2 共享内存吗？',np.may_share_memory(orgin,orgin_reshape2))
```

    orgin is [[ 0  1  2  3]
     [ 4  5  6  7]
     [ 8  9 10 11]
     [12 13 14 15]]
    orgin_shape1 is [[ 0  4]
     [ 8 12]]
    orgin_shape2 is [[0 1]
     [2 3]]
    orgin 和 orgin_reshape1 共享内存吗？ True
    orgin 和 orgin_reshape2 共享内存吗？ True
    

## 3、数组拷贝

### (1)不拷贝
如简单的直接赋值操作，两个引用在同一块内存，修改任何一个都会修改到同一块内存上,两者其实本质上是一个东西


```python
copy = np.arange(12)
copy1 = copy
print('copy is copy1 ?',copy is copy1)
copy1.shape = (3,4)
print('copy shape have change to (4,4),what is copy1?',copy1.shape)
```

    copy is copy1 ? True
    copy shape have change to (4,4),what is copy1? (3, 4)
    

### (2)、视图view ，也称浅拷贝
view生成一个在原来内存上的新数组，两个数组共享数据，

数组切片返回的就是view


```python
v = np.arange(12)
a = v.view()
print('a is v ?',a is v)            #视图和原数组不是同一个对象
a[2] = 199
print(' v is ',v)                 #视图发生数据变化，原数组数据也会发生变化
a.shape = (4,3)
print('a is ',a)
print( 'v is ',v)               #视图形状变化之后，原对象形状不会发生变化，所以视图与原对象仅仅共享数据。

```

    a is v ? False
     v is  [  0   1 199   3   4   5   6   7   8   9  10  11]
    a is  [[  0   1 199]
     [  3   4   5]
     [  6   7   8]
     [  9  10  11]]
    v is  [  0   1 199   3   4   5   6   7   8   9  10  11]
    


```python
s = v[1:5]                     #对数组进行切片，s与a共享数据，一个改变，另一个也会变
s[2] = 9999
print('v is ',v)
```

    v is  [   0    1  199 9999    4    5    6    7    8    9   10   11]
    

### (3)、深拷贝
copy函数生成一个全新对象


```python
co = np.arange(12)
co1 = co.copy()
co1[2] = 999                  #深拷贝的co1数据改变不会影响原对象co
co1.shape = (3,4)         #深拷贝的co1 形状改变不会影响原对象co
print('co is',co)
print('co1 is',co1)
```

    co is [ 0  1  2  3  4  5  6  7  8  9 10 11]
    co1 is [[  0   1 999   3]
     [  4   5   6   7]
     [  8   9  10  11]]
    

 Markdown工具和资料参考



# 工具



|        | 支持平台    | 地址             | 优缺点                       |

| ------------- | -------------- | ---------------------------- | -------------------------------------------------- |

| Typora    | win,mac,linux | https://typora.io/#download | ****开源免费，跨平台，首选**** |

| VSCode   | win,mac,linux | 插件：Markdown Preview Mermaid Support | 左边编辑右边预览，写长的时序图比较方便 |

| Markdown Plus | 浏览器     | <http://mdp.tylingsoft.com/> | web，左边编辑右边预览。但不支持alt包含3个分支   |

| TAPD | | http://tapd.oa.com/markdown_wikis/wiki_demo | 目前标签跟mermaid标准不一样，并且注释暂时不支持BR换行，预计1月底的版本都支持 |



# 资料



markdown的时序图、流程图、甘特图等的详解，看这里



https://mermaidjs.github.io/ 



 转换到TAPD



目前版本的TAPD支持流程图、时序图，但标签跟mermaid标准不同，需要替换一下。预计2020年1月底的TAPD新版，就跟mermaid标准一样。







mermaid

sequenceDiagram

替换成 seq





mermaid

graph

替换成 flow



<BR/> 替换成空，因为现版本的TAPD还不支持BR换行







 时序图demo



# 1.时序图--普通



```mermaid

sequenceDiagram

客户端->>WebServer: 提交订单申请（用户信息,pid,数量）

Note over WebServer, MySQL: DB的操作都写上SQL<br/>这个SQL简单不另外写注释

WebServer->>MySQL: 获取递增的订单编号 := insert into table1 ...

WebServer->>MySQL: 获取商品信息：select table1（产品pid）

MySQL-->>WebServer: 返回商品信息: 产品名称，属性，金额等

Note over 客户端,WebServer: 条件执行：满足中括号[]内的条件,<br/>就执行右边的动作

WebServer-->>客户端: [商品已卖完] 提示已卖完

WebServer->>WebServer: 订单业务逻辑处理（订单编号，支付金额，优惠金额等）

Note over WebServer, MySQL: update table1<br/>set ...<br/>where xxx=订单编号<br/> and yyy=pid...

WebServer->>MySQL: 更新订单：update table1（订单编号，pid，数量，待支付）

```



# 2.时序图--循环



```mermaid

sequenceDiagram

WebServer->>MySQL: 推送用户列表 := select * from t1 where ...

Note over WebServer, 推送服务器: 给每个用户推送模板消息

loop 推送用户列表 as uid

WebServer->>推送服务器: 发送模板消息(uid)

推送服务器-->>WebServer: 发送结果

WebServer->>MySQL: 记录发送结果: insert into table2...

end

```



# 3.时序图--分支



```mermaid

sequenceDiagram

客户端->>WebServer: 购买商品(参数1,参数2)

WebServer->>MySQL: 获取商品信息: select from table1 where ...

MySQL-->>WebServer: 商品信息

Note over WebServer, MySQL: 操作简单的就不需要alt，<br/>用普通的[]条件就可以

alt 微信支付

WebServer->>MySQL: 操作1

else 储值支付

WebServer->>MySQL: 操作2

else 到付

WebServer->>MySQL: 操作3

end

WebServer-->>客户端: 重定向拉起支付

```



# 4.时序图--指定Actor的顺序



```mermaid

sequenceDiagram



participant 客户端

participant Server1

participant Server2

participant MySQL



客户端->>Server2: 请求1(...)

Server2-->>客户端: 应答1(...)

客户端->>Server1: 请求2(...)

Server1-->>客户端: 应答2(...)



```



 流程图demo



# 流程图--从上到下



```mermaid

graph TD

A[模块A] -->|A1| B(模块B)

B --> C{判断条件C}

C -->|条件C1| D[模块D]

C -->|条件C2| E[模块E]

C -->|条件C3| F[模块F]

```







流程图--从左到右



```mermaid

graph LR

A[模块A] -->|A1| B(模块B)

B --> C{判断条件C}

C -->|条件C1| D[模块D]

C -->|条件C2| E[模块E]

C -->|条件C3| F[模块F]

```



# 系统部署图



```mermaid

graph TD

SLB("负载均衡器") --- B_Nginx(nginx)

SLB --- D_Nginx(nginx)

subgraph B区机房

B_Nginx --- B_php1(php)

B_Nginx --- B_php2(php)

end

subgraph D区机房

D_Nginx --- D_php1(php)

D_Nginx --- D_php2(php)

end

subgraph B区和D区机房

B_php1 --- DB+Redis

B_php2 --- DB+Redis

D_php1 --- DB+Redis

D_php2 --- DB+Redis

end

```



# 流程图变颜色和各种形状



```mermaid

graph TD;

  A-->B(B)

  A-->C>C]

  B-->D((D))

  C-->D

classDef eco fill:red;

class D eco

```



 状态机demo



# TCP状态机



```mermaid

stateDiagram

   

  note right of CLOSED: CLOSED是起点 

  CLOSED --> LISTEN: 被动打开

  CLOSED --> SYN_SENT: 主动打开发送SYN

  LISTEN --> CLOSED: 关闭

  LISTEN --> SYN_RCVD: 收到SYN,发送SYN,ACK

  LISTEN --> SYN_SENT: 发送SYN

  SYN_RCVD --> LISTEN: 收到RST

  SYN_RCVD --> ESTABLISHED: 收到ACK

  SYN_SENT --> SYN_RCVD: 收到SYN,发送SYN,ACK

  ESTABLISHED --> CLOSEWAIT: 收到FIN,发送ACK

   

  CLOSEWAIT --> LAST_ACK: 关闭 发送FIN

  LAST_ACK --> CLOSED: 收到ACK

   

  SYN_RCVD --> FIN_WAIT_1: 关闭 发送FIN

  ESTABLISHED --> FIN_WAIT_1: 关闭 发送FIN

  FIN_WAIT_1 --> FIN_WAIT_2: 收到ACK

  FIN_WAIT_1 --> CLOSING: 收到FIN,发送ACK

  FIN_WAIT_1 --> TIME_WAIT: 收到FIN,发送ACK

  FIN_WAIT_2 --> TIME_WAIT: 收到FIN,发送ACK

  CLOSING --> TIME_WAIT: 收到ACK

  TIME_WAIT --> CLOSED: 定时经过两倍报文段寿命后

   

```



# demo状态机



```mermaid

stateDiagram

  [*] --> Still

  Still --> [*]



  Still --> Moving

  Moving --> Still

  Moving --> Crash

  Crash --> [*]

```



 类图



```mermaid

classDiagram

   Animal <|-- Duck

   Animal <|-- Fish

   Animal <|-- Zebra

   Animal : +int age

   Animal : +String gender

   Animal: +isMammal()

   Animal: +mate()

   class Duck{

​     +String beakColor

​     +swim()

​     +quack()

   }

   class Fish{

​     -int sizeInFeet

​     -canEat()

   }

   class Zebra{

​     +bool is_wild

​     +run()

   }

```



 饼图

```mermaid

pie

  "Dogs" : 386

  "Cats" : 85

  "Rats" : 150

```



```

this is a python

```
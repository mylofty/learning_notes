[toc]

# 一、课程来源
https://zhuanlan.zhihu.com/p/366395817

https://zhuanlan.zhihu.com/p/366395817

# 二、介绍
防腐层（Anti-Corruption Layer) 是一种在外部依赖频繁变更的情况下，如何将核心业务和外部依赖隔离的机制
限界上下文（Bounded Context）微服务拆分的依据

## Domain Primitive（DP）原则
### 1. 将隐性概念显示化（make implicit concepts explicit）
普通代码存在的问题
1. 胶水代码：由于我们有时候需要把入参进行修改才能丢到我们的逻辑处理函数中，这个对入参的修改代码就是所说的胶水代码。胶水代码抽离成一个xxxUtils静态类中，容易导致代码找不到业务逻辑。胶水代码可以改为一个对象的函数，表为可复用，可测试的逻辑
2. 隐性代码，有一些逻辑，比如手机号区号，既不属于用户，也不属于注册服务，要是直接写到业务逻辑中，就是隐形代码，需要将隐性代码显示化（make implicit concepts explicit）生成一个新的value object
3. 数据校验逻辑和非核心业务逻辑，应该有其他的object进行处理，核心业务逻辑保持清晰
4. 入参是一个string，虽然简单，但是不好扩展，而且当多个入参都是string，容易写错。修改为入参为对象，则不容易错，易扩展。本来在核心逻辑中需要做的数据校验和处理，现在都被前置到这个入参对象里面做处理了，数据有问题，就不能进入到这个核心函数。
### 2. 将隐性上下文显示化（make implicit context explicit)
1. 支持10元，直接传参数：10，不如将数组转为money类，包含数字和货币，方便扩展
### 3. 封装多对象行为(emcapsulate multi-object behaviro)
1. 在支付的逻辑中，包含了金额计算换算的逻辑，而金额换算逻辑需要涉及多个对象，所以将整个换算封装成一个类，让支付逻辑简单化

### 4. DP的定义
1. 传统意义上的value object
2. DP是一个完整的概念整体，拥有精准定义
3. DP使用业务域中的原生语言
4. DP可以是业务域的最小组成部分、也可以构建复杂组合

### 5. 常见的 DP 的使用场景包括：
1. 有格式限制的 String：比如Name，PhoneNumber，OrderNumber，ZipCode，Address等
2. 有限制的Integer：比如OrderId（>0），Percentage（0-100%），Quantity（>=0）等
3. 可枚举的 int ：比如 Status（一般不用Enum因为反序列化问题）
4. Double 或 BigDecimal：一般用到的 Double 或 BigDecimal 都是有业务含义的，比如 Temperature、Money、Amount、ExchangeRate、Rating 等
5. 复杂的数据结构：比如 Map<String, List<Integer>> 等，尽量能把 Map 的所有操作包装掉，仅暴露必要行为





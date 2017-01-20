
### 引导


### 路由


### 响应

默认返回状态码200,如果返回其他的状态码，要
Yii::$app->response->statusCode = 200;


### session cookie


#### 1. session 的存储
yii\web\DbSession: 存储session数据在数据表中
yii\web\CacheSession: 存储session数据到缓存中，缓存和配置中的缓存组件相关
yii\redis\Session: 存储session数据到以redis 作为存储媒介中
yii\mongodb\Session: 存储session数据到MongoDB.

```
CREATE TABLE session
(
    id CHAR(40) NOT NULL PRIMARY KEY,
    expire INTEGER,
    data BLOB
)
```

#### 2. Flash 数据：只会在下一次请求中有效


### 3.cookie

### 4. cookie 验证


### 错误处理

errorHandler


### 日志

1. 日志记录
Yii::trace()：记录一条消息去跟踪一段代码是怎样运行的。这主要在开发的时候使用。
Yii::info()：记录一条消息来传达一些有用的信息。
Yii::warning()：记录一个警告消息用来指示一些已经发生的意外。
Yii::error()：记录一个致命的错误，这个错误应该尽快被检查。

2.target


## 关联概念

### 组件

#### 属性
PHP中类的成员变量称为属性。

#### 事件
为什么使用事件和触发器呢？可以直接创建对象

1. 事件处理器是一个PHP回调函数
    * 全局函数, 比如trim
    * [$object, 'callback']
    * ['ClassName', 'callback'] 静态方法
    * 匿名函数 function ($event) { $event->name; $event->sender; $event->data};
2.事件处理器：
```
    $foo->on(Foo::EVENT_HELLO, ['app\components\Bar', 'methodName']);

```
3. 事件处理顺序
事件发生后，按添加顺序依次执行.终端处理:
```
$foo->on(Foo::EVENT_HELLO, function ($event) {
    $event->handled = true;
});
```

4. 出发事件

#### 行为

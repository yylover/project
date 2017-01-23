多个系统如何通过定时任务同步数据？异构系统不同的进程间如何相互调用，通讯。消息服务删除解决多系统、异构系统的数据交换问题。RabbitMQ是当前主流的消息中间件之一。

消息中间件主要用于组件之间的解耦，消息的发送者无需知道消息使用者存在。反之，亦然。RabbitMQ是开源AMQP实现。

rabbitMQ的核心思想在于P不应该知道后面队列的情况，只需要把消息发给exchange即可。

核心概念：
Queue:内部对象，用于存储消息。
绑定：绑定是exchange和队列的关系，可以理解为Queue对exchange感兴趣。
Exchange:路由组件。

消息反馈：为了防止丢消息，收到消息后要回复ack,如果断开之前没有回复，才有可能发送给其他消费者。

Message 持久化：
为了保证不丢消息，可以把Queue和Message都设置为可持久化的。

prefetch count:用于限制Queue每次发送给每个消费者的消息树。

routeKey:生产者发送给exchange时，一般会指定一个routingKey,而这个routingkey最终要与exchangeType和binding key联合使用才能生效。

bindingKey: 绑定exchange和Queue时，一般会指定一个bindingKey,消费者将消息发送给exchange时，指定的routingKey和bindingKey匹配时，会发到相应的队列。


二、exchange 类型
exchange : direct topic headers fanout


1. Direct :
任何发到direct exchange 的消息都会转发到routekey指定的Queue,不需要任何绑定操作。即routing key  bindingkey 完全匹配时，才会发送给响应的Queue


A. 一般情况可以使用rabbitMQ自带的exchange，名称为空字符串。
B. 消息传递时需要一个RouteKey，可简单理解为消息队列名称。
C如果vhost中不存在指定的队列名，则消息被丢弃。

2. Fanout 
任何发到exchange 的消息会转发到与该exchange bind的所有queue中，

a) 可以理解为路由表模式，不需要任何RouteKey
b) 这种模式需要提前将Exchange与Queue绑定，一个exange 可以绑定多个Queue,一个queue可以同时与多个exchange绑定。
c) 如果接收到消息的exchange 没有与任何Queue绑定，消息丢弃。

2. Topic 
任何发送到exchange的消息会转发到所有关心RouteKey的Queue中，
a) 这种话题较为复杂，每个队列都有关心的主题，所有的消息都带有一个标题(routeKey),exchange 会转发到所有关注主题与RouteKey模糊匹配的队列。
b) 这种模式需要RouteKey,也需要提前绑定Exchange 和Queue
c) 绑定时，要提供一个队列关心的主题，如”#.log.#”表示该队列关心所有涉及log的消息。“MQ.log.err”
d) 如果发现没有匹配的Queue，会抛弃此消息

routine key: ‘.’分割的字符串
binding Key: . 分割的字符串。*匹配一个单词，#匹配多个单词。


4. headers:
headers类型的exchange不依赖routingKey 和bindingKey来路由消息，而是根据发送消息内容的header属性进行匹配。


每个exchange的进程不同，都在自己独立的进程中执行。因此增加多个交换机就是增加多个进程。


三、持久化：
Queue和exchange创建时指定的标志durable.
持久化消息的步骤：
1) exchange durable
2) queue durable
3) Message 的DeliveryMode 设置为2；

对于bind,如果绑定了一个durable队列和durable交换机，会自动保留这个bind。如果队列和交换机，无论是否durable,则会删除绑定。
注意：
A. RabbitMQ 不允许你绑定一个非坚固（non-durable）的交换机和一个durable的队列。反之亦然。要想成功必须队列和交换机都是durable的。(错误，可以绑定)
B. 一旦创建exchange queue就不能修改标志了。
c. 一个queue可以与exchange 多次绑定，

四、


开启rabbitMQ管理界面
./rabbitmq-plugins enable rabbitmq_management

rabbitMQ:

开启插件:
linux-bnnq:~ # rabbitmq-plugins enable rabbitmq_management  

重启:
linux-bnnq:~ # /etc/init.d/rabbitmq-server restart   

启动:
linux-bnnq:~ # rabbitmq-server –detached  
linux-bnnq:~ # /etc/init.d/rabbitmq-server start   
关闭:

linux-bnnq:~ # rabbitmqctl stop  
linux-bnnq:~ # rabbitmq-service stop 

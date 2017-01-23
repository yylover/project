Kafka高吞吐量的分布式订阅消息系统。是分布式的、可划分的、冗余备份的、持久性的日志服务。主要用于处理活跃的流式数据。


一、基本概念：
Topic:特定类型的消息流
生产者:producer:能否发布消息到话题的对象。
broker:已发布的消息保存在一组服务器中，称为代理或kafka集群。
消费者：可以订阅一个或多个话题，从broker拉数据，从而消费这些已经发布的数据。
Partition: Topic物理分组。一个Topic可以分为多个partition,每个partition是一个有序队列。


Topic可认为是一类消息，每个topic分为多个partition,其存储层面是append log文件。任何发布到此partition的消息直接追加到log文件尾部。每条消息在文件中的位置称为offset. long 型数字，唯一标识一条消息。kafka没有其他的额外索引机制来存储offset,因为kafka中不允许对消息进行随机读写。




kafka的架构：
存储布局非常简单，每个分区对应一个逻辑日志。

kafka内在就是分布式的。一个kafka集群通常包括多个代理。为了均衡负载，将话题分成多个分区。每个代理存储一到多个数去。

kafka与JMS实现activeMQ的不同在于:即使消息被消费，仍然不能立即删除。日志文件会根据broker配置要求，保留一定时间删除。
对于consumer而言，需要保存消息的offset,对于offset的保存和使用，由consumer来控制。正常读消息时，offset会线性向前驱动，即消息被一次顺序消费。
kafka集群不会维护任何consumer和producer状态信息。这些信息由zookeeper保存，因此producer和consumer实现非常轻量，可以随意离开。
a) Producer根据指定的partition方法(round-robin hash等)将消息发送到指定的topic的partition里面
b) kafka集群接收到producer发来的数据，将其持久化到硬盘，并保留消息指定长时间。
c) Consumer从kafka 拉取消息，并控制消息的offset



2. kafka 高吞吐量的设计:

a) 数据磁盘持久化:消息不再内存中cache,直接写入磁盘
b) zero-copy 减少IO操作步骤
c) 数据批量发送
d) 数据压缩
f) Topic 划分多个partiion 提高并行性

负载均衡:
1) producer 根据指定的算法，发送到指定partition;
2) 存在多个partition, 每个partition 有自己的replica,每个replica分布在不同的broker节点。
3) 多个partition需要序曲lea partition,lead partition负责读写，并由zookeeper负责fail over

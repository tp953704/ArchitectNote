# Kafka 教程

> Kafka 是 Apache 的开源项目。**Kafka 既可以作为一个消息队列中间件，也可以作为一个分布式流处理平台**。
>
> **Kafka 用于构建实时数据管道和流应用。它具有水平可伸缩性，容错性，快速快速性**。

## 📖 内容

- [Kafka 应用指南](kafka-quickstart.md)
- [Kafka 生产者](kafka-producer.md)
- [Kafka 消费者](kafka-consumer.md)
- [Kafka 可靠的数据传递](kafka-reliable-transmission.md)
- [Kafka 分区再均衡](kafka-rebalance.md)
- [Kafka 集群](kafka-cluster.md)
- [Kafka 流式处理](kafka-stream.md)
- [Kafka 运维指南](kafka-ops.md)

## 📚 资料

- **官方**
  - [Kakfa 官网](http://kafka.apache.org/)
  - [Kakfa Github](https://github.com/apache/kafka)
  - [Kakfa 官方文档](https://kafka.apache.org/documentation/)
- **书籍**
  - [《Kafka 权威指南》](https://item.jd.com/12270295.html)
- **教程**
  - [Kafka 中文文档](https://github.com/apachecn/kafka-doc-zh)
  - [Kafka 核心技术与实战](https://time.geekbang.org/column/intro/100029201)
  - [消息队列高手课](https://time.geekbang.org/column/intro/100032301)

## 🚪 传送

◾ 🏠 [BIGDATA-TUTORIAL 首页](https://github.com/dunwu/bigdata-tutorial) ◾ 🎯 [我的博客](https://github.com/dunwu/blog) ◾
# Kafka 应用指南

> Kafka 是 Apache 的开源项目。**Kafka 既可以作为一个消息队列中间件，也可以作为一个分布式流处理平台**。
>
> **Kafka 用于构建实时数据管道和流应用。它具有水平可伸缩性，容错性，快速快速性**。

<!-- TOC depthFrom:2 depthTo:3 -->

- [一、Kafka 简介](#一kafka-简介)
  - [Kafka 的特性](#kafka-的特性)
  - [Kafka 核心功能](#kafka-核心功能)
  - [Kafka 适用场景](#kafka-适用场景)
  - [Kafka 术语](#kafka-术语)
- [快速入门](#快速入门)
  - [引入依赖](#引入依赖)
  - [Kafka 核心 API](#kafka-核心-api)
  - [发送消息](#发送消息)
  - [消费消息流程](#消费消息流程)
- [Kafka 分区](#kafka-分区)
  - [什么是分区](#什么是分区)
  - [为什么要使用分区](#为什么要使用分区)
- [参考资料](#参考资料)
- [🚪 传送](#🚪-传送)

<!-- /TOC -->

## Kafka 简介

Kafka 是一个消息队列中间件，也是一个分布式流处理平台。

![img](http://dunwu.test.upcdn.net/snap/20200726185629.png)

### Kafka 的特性

Kafka 具有如下特性：

- **伸缩性** - 随着数据量增长，可以通过对 Broker 集群水平扩展来提高系统性能。
- **高性能** - 通过横向扩展生产者、消费者(通过消费者群组实现)和 Broker（通过扩展实现系统伸缩性）可以轻松处理巨大的消息流。
- **消息持久化** - Kafka 将所有的消息存储到磁盘，并在结构中对它们进行排序，以便利用顺序磁盘读取，所以消息不会丢失。

### Kafka 核心功能

- **发布 / 订阅** - 发布 / 订阅类似于一个消息系统，读写流式的数据
- **流处理** - 编写可扩展的流处理应用，用于实时事件响应
- **存储** - 将流式数据存储在一个分布式、有副本的集群中

### Kafka 适用场景

Kafka 适用于两种场景:

- **构造实时流数据管道**，它可以在应用间可靠地传输数据（相当于消息队列）。
- **构建实时流式应用程序**，对这些流数据进行转换（即流处理，通过 kafka stream 在主题内部进行转换）。

Kafka 允许您将大量消息通过集中介质存储并存储，而不用担心性能或数据丢失等问题。这意味着它非常适合用作系统架构的核心，充当连接不同应用程序的集中介质。Kafka 可以成为事件驱动架构的核心部分，并真正将应用程序彼此分离。

![img](http://dunwu.test.upcdn.net/cs/java/javaweb/distributed/mq/kafka/kafka-event-system.png)

### Kafka 术语

- 消息：Record。Kafka 是消息引擎嘛，这里的消息就是指 Kafka 处理的主要对象。
- **Broker** - Kafka 集群包含一个或多个节点，这种节点被称为 Broker。
- **Topic**：Topic 是承载消息的逻辑容器，在实际使用中多用来区分具体的业务。不同 Topic 的消息是物理隔离的；同一个 Topic 的消息保存在一个或多个 Broker 上，但用户只需指定消息的 Topic 即可生产或消费数据而不必关心数据存于何处。对于每一个 Topic， Kafka 集群都会维持一个分区日志。
- **Partition**：分区。一个有序不变的消息序列。为了提高 Kafka 的吞吐率，每个 Topic 包含一个或多个 Partition，每个 Partition 在物理上对应一个文件夹，该文件夹下存储这个 Partition 的所有消息和索引文件。Kafka 日志的 Partition 分布在 Kafka 集群的节点上。每个节点在处理数据和请求时，共享这些 Partition。每一个 Partition 都会在已配置的节点上进行备份，确保容错性。
- **Offset**：消息位移。表示分区中每条消息的位置信息，是一个单调递增且不变的值。
- **Replica**：副本。Kafka 中同一条消息能够被拷贝到多个地方以提供数据冗余，这些地方就是所谓的副本。副本还分为领导者副本和追随者副本，各自有不同的角色划分。副本是在分区层级下的，即每个分区可配置多个副本实现高可用。
- **Producer**：生产者。向主题发布新消息的应用程序。Producer 可以将数据发布到所选择的 Topic 中。Producer 负责将记录分配到 Topic 中的哪一个 Partition 中。
- **Consumer**：消费者。从主题订阅新消息的应用程序。Consumer 使用一个 Consumer Group 来进行标识，发布到 Topic 中的每条记录被分配给订阅 Consumer Group 中的一个 Consumer，Consumer 可以分布在多个进程中或者多个机器上。
  - 如果所有的 Consumer 在同一 Consumer Group 中，消息记录会负载平衡到每一个 Consumer。
  - 如果所有的 Consumer 在不同的 Consumer Group 中，每条消息记录会广播到所有的 Consumer。
- **Consumer Group**：消费者组。多个 Consumer 实例共同组成的一个组，同时消费多个分区以实现高吞吐。每个 Consumer 属于一个特定的 Consumer Group（可以为每个 Consumer 指定 group name，若不指定 Group 则属于默认的 Group）。**在同一个 Group 中，每一个 Consumer 可以消费多个 Partition，但是一个 Partition 只能指定给一个这个 Group 中一个 Consumer**。
- **Consumer Offset**：消费者位移。表征消费者消费进度，每个消费者都有自己的消费者位移。
- **Rebalance**：重平衡。 消费者组内某个消费者实例挂掉后，其他消费者实例自动重新分配订阅主题分区的过程。Rebalance 是 Kafka 消费者端实现高可用的重要手段。

<div align="center">
<img src="http://kafka.apachecn.org/10/images/consumer-groups.png" />
</div>
### Kafka 基本工作流程

Kafka 通过 Topic 对存储的流数据进行分类。

Topic 就是数据主题，是数据记录发布的地方，可以用来区分业务系统。一个 Topic 可以拥有一个或者多个消费者来订阅它的数据。

在 Kafka 中，任意一个 Topic 维护一个 Partition 日志，如下所示：

<div align="center">
<img src="http://dunwu.test.upcdn.net/cs/java/javaweb/distributed/mq/kafka/kafka-log-anatomy.png" width="400"/>
</div>


每个 Partition 都是一个有序的、不可变的记录序列，不断追加到结构化的提交日志中。Partition 中的记录每个分配一个连续的 id 号，称为偏移量（Offset），用于唯一标识 Partition 内的每条记录。

**Kafka 集群持久化保存（使用可配置的保留期限）所有发布记录——无论它们是否被消费**。例如，如果保留期限被设置为两天，则在记录发布后的两天之内，它都可以被消费，超过时间后将被丢弃以释放空间。Kafka 的性能和数据大小无关，所以长时间存储数据没有什么问题。

<div align="center">
<img src="http://kafka.apachecn.org/10/images/log_consumer.png" width="400"/>
</div>


实际上，保留在每个 Consumer 基础上的唯一元数据是该 Consumer 在日志中消费的位置。这个偏移量是由 Consumer 控制的：Consumer 通常会在读取记录时线性的增加其偏移量。但实际上，由于位置由 Consumer 控制，所以 Consumer 可以采用任何顺序来消费记录。

日志中的 Partition 有以下几个用途：

- 首先，它们允许日志的大小超出服务器限制的大小。每个单独的 Partition 必须适合承载它的服务器，但是一个 Topic 可能有很多 Partition，因此它可以处理任意数量的数据。
- 其次，它可以作为并行的单位。

![img](http://dunwu.test.upcdn.net/cs/java/javaweb/distributed/mq/kafka/kafka-producer-consumer.png)

## 快速入门

### 引入依赖

Stream API 的 maven 依赖：

```xml
<dependency>
    <groupId>org.apache.kafka</groupId>
    <artifactId>kafka-streams</artifactId>
    <version>1.1.0</version>
</dependency>
```

其他 API 的 maven 依赖：

```xml
<dependency>
    <groupId>org.apache.kafka</groupId>
    <artifactId>kafka-clients</artifactId>
    <version>1.1.0</version>
</dependency>
```

### Kafka 核心 API

Kafka 有 4 个核心 API

<div align="center">
<img src="http://dunwu.test.upcdn.net/cs/java/javaweb/distributed/mq/kafka/kafka-core-api.png" width="400"/>
</div>


- [Producer API](https://kafka.apache.org/documentation.html#producerapi) - 允许一个应用程序发布一串流式数据到一个或者多个 Kafka Topic。
- [Consumer API](https://kafka.apache.org/documentation.html#consumerapi) - 允许一个应用程序订阅一个或多个 Kafka Topic，并且对发布给他们的流式数据进行处理。
- [Streams API](https://kafka.apache.org/documentation/streams) - 允许一个应用程序作为一个流处理器，消费一个或者多个 Kafka Topic 产生的输入流，然后生产一个输出流到一个或多个 Kafka Topic 中去，在输入输出流中进行有效的转换。
- [Connector API](https://kafka.apache.org/documentation.html#connect) - 允许构建并运行可重用的生产者或者消费者，将 Kafka Topic 连接到已存在的应用程序或数据库。例如，连接到一个关系型数据库，捕捉表的所有变更内容。

### 发送消息

#### 发送并忽略返回

代码如下，直接通过 `send` 方法来发送

```java
ProducerRecord<String, String> record =
            new ProducerRecord<>("CustomerCountry", "Precision Products", "France");
    try {
            producer.send(record);
    } catch (Exception e) {
            e.printStackTrace();
}
```

#### 同步发送

代码如下，与“发送并忘记”的方式区别在于多了一个 `get` 方法，会一直阻塞等待 `Broker` 返回结果：

```java
ProducerRecord<String, String> record =
            new ProducerRecord<>("CustomerCountry", "Precision Products", "France");
    try {
            producer.send(record).get();
    } catch (Exception e) {
            e.printStackTrace();
}
```

#### 异步发送

代码如下，异步方式相对于“发送并忽略返回”的方式的不同在于：在异步返回时可以执行一些操作，如记录错误或者成功日志。

首先，定义一个 callback

```java
private class DemoProducerCallback implements Callback {
      @Override
        public void onCompletion(RecordMetadata recordMetadata, Exception e) {
           if (e != null) {
               e.printStackTrace();
             }
        }
}
```

然后，使用这个 callback

```java
ProducerRecord<String, String> record =
            new ProducerRecord<>("CustomerCountry", "Biomedical Materials", "USA");
producer.send(record, new DemoProducerCallback());
```

#### 发送消息示例

```java
import java.util.Properties;
import org.apache.kafka.clients.producer.KafkaProducer;
import org.apache.kafka.clients.producer.Producer;
import org.apache.kafka.clients.producer.ProducerConfig;
import org.apache.kafka.clients.producer.ProducerRecord;

/**
 * Kafka 生产者生产消息示例 生产者配置参考：https://kafka.apache.org/documentation/#producerconfigs
 */
public class ProducerDemo {
    private static final String HOST = "localhost:9092";

    public static void main(String[] args) {
        // 1. 指定生产者的配置
        Properties properties = new Properties();
        properties.put(ProducerConfig.BOOTSTRAP_SERVERS_CONFIG, HOST);
        properties.put(ProducerConfig.ACKS_CONFIG, "all");
        properties.put(ProducerConfig.RETRIES_CONFIG, 0);
        properties.put(ProducerConfig.BATCH_SIZE_CONFIG, 16384);
        properties.put(ProducerConfig.LINGER_MS_CONFIG, 1);
        properties.put(ProducerConfig.BUFFER_MEMORY_CONFIG, 33554432);
        properties.put(ProducerConfig.KEY_SERIALIZER_CLASS_CONFIG,
            "org.apache.kafka.common.serialization.StringSerializer");
        properties.put(ProducerConfig.VALUE_SERIALIZER_CLASS_CONFIG,
            "org.apache.kafka.common.serialization.StringSerializer");

        // 2. 使用配置初始化 Kafka 生产者
        Producer<String, String> producer = new KafkaProducer<>(properties);

        try {
            // 3. 使用 send 方法发送异步消息
            for (int i = 0; i < 100; i++) {
                String msg = "Message " + i;
                producer.send(new ProducerRecord<>("HelloWorld", msg));
                System.out.println("Sent:" + msg);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            // 4. 关闭生产者
            producer.close();
        }
    }
}
```

### 消费消息流程

#### 消费流程

具体步骤如下：

1. 创建消费者。
2. 订阅主题。除了订阅主题方式外还有使用指定分组的模式，但是常用方式都是订阅主题方式
3. 轮询消息。通过 poll 方法轮询。
4. 关闭消费者。在不用消费者之后，会执行 close 操作。close 操作会关闭 socket，并触发当前消费者群组的再均衡。

```java
    // 1.构建KafkaCustomer
    Consumer consumer = buildCustomer();

    // 2.设置主题
    consumer.subscribe(Arrays.asList(topic));

    // 3.接受消息
    try {
        while (true) {
            ConsumerRecords<String, String> records = consumer.poll(500);
            System.out.println("customer Message---");
            for (ConsumerRecord<String, String> record : records)

                // print the offset,key and value for the consumer records.
                System.out.printf("offset = %d, key = %s, value = %s\n",
                        record.offset(), record.key(), record.value());
        }
    } finally {
        // 4.关闭消息
            consumer.close();
    }
```

创建消费者的代码如下：

```java
public Consumer buildCustomer() {
    Properties props = new Properties();
    // bootstrap.servers是Kafka集群的IP地址。多个时,使用逗号隔开
    props.put("bootstrap.servers", "localhost:9092");
    // 消费者群组
    props.put("group.id", "test");
    props.put("enable.auto.commit", "true");
    props.put("auto.commit.interval.ms", "1000");
    props.put("session.timeout.ms", "30000");
    props.put("key.deserializer",
            "org.apache.kafka.common.serialization.StringDeserializer");
    props.put("value.deserializer",
            "org.apache.kafka.common.serialization.StringDeserializer");
    KafkaConsumer<String, String> consumer = new KafkaConsumer
            <String, String>(props);

    return consumer;
}
```

#### 消费消息方式

分为订阅主题和指定分组两种方式：

- 消费者分组模式。通过订阅主题方式时，消费者必须加入到消费者群组中，即消费者必须有一个自己的分组；
- 独立消费者模式。这种模式就是消费者是独立的不属于任何消费者分组，自己指定消费那些 `Partition`。

1、订阅主题方式

```java
consumer.subscribe(Arrays.asList(topic));
```

2、独立消费者模式

通过 consumer 的 `assign(Collection<TopicPartition> partitions)` 方法来为消费者指定分区。

```java
public void consumeMessageForIndependentConsumer(String topic){
    // 1.构建KafkaCustomer
    Consumer consumer = buildCustomer();

    // 2.指定分区
    // 2.1获取可用分区
    List<PartitionInfo> partitionInfoList = buildCustomer().partitionsFor(topic);
    // 2.2指定分区,这里是指定了所有分区,也可以指定个别的分区
    if(null != partitionInfoList){
        List<TopicPartition> partitions = Lists.newArrayList();
        for(PartitionInfo partitionInfo : partitionInfoList){
            partitions.add(new TopicPartition(partitionInfo.topic(),partitionInfo.partition()));
        }
        consumer.assign(partitions);
    }

    // 3.接受消息
    while (true) {
        ConsumerRecords<String, String> records = consumer.poll(500);
        System.out.println("consume Message---");
        for (ConsumerRecord<String, String> record : records) {

            // print the offset,key and value for the consumer records.
            System.out.printf("offset = %d, key = %s, value = %s\n",
                    record.offset(), record.key(), record.value());

            // 异步提交
            consumer.commitAsync();


        }
    }
}
```

## 持久化

在基本工作流程中提到了：**Kafka 集群持久化保存（使用可配置的保留期限）所有发布记录——无论它们是否被消费**。Kafka 是如何实现持久化的呢？

**Kafka 对消息的存储和缓存严重依赖于文件系统**。

- 顺序磁盘访问在某些情况下比随机内存访问还要快！在 Kafka 中，所有数据一开始就被写入到文件系统的持久化日志中，而不用在 cache 空间不足的时候 flush 到磁盘。实际上，这表明数据被转移到了内核的 pagecache 中。所以，**虽然 Kafka 数据存储在磁盘中，但其访问性能也不低**。

- Kafka 的协议是建立在一个 “消息块” 的抽象基础上，合理将消息分组。 这使得网络请求将多个消息打包成一组，而不是每次发送一条消息，从而使整组消息分担网络中往返的开销。Consumer 每次获取多个大型有序的消息块，并由服务端依次将消息块一次加载到它的日志中。这可以**有效减少大量的小型 I/O 操作**。
- 由于 Kafka 在 Producer、Broker 和 Consumer 都**共享标准化的二进制消息格式**，这样数据块不用修改就能在他们之间传递。这可以**避免字节拷贝带来的开销**。
- Kafka 以高效的批处理格式支持一批消息可以压缩在一起发送到服务器。这批消息将以压缩格式写入，并且在日志中保持压缩，只会在 Consumer 消费时解压缩。**压缩传输数据，可以有效减少网络带宽开销**。
  - Kafka 支持 GZIP，Snappy 和 LZ4 压缩协议。

所有这些优化都允许 Kafka 以接近网络速度传递消息。

## Kafka 分区

### 什么是分区

Kafka 通过 Topic 对存储的流数据进行分类。Topic 就是数据主题，是数据记录发布的地方，可以用来区分业务系统。一个 Topic 可以拥有一个或者多个消费者来订阅它的数据。

在 Kafka 中，任意一个 Topic 维护一个 Partition 日志，如下所示：

<div align="center">
<img src="http://dunwu.test.upcdn.net/cs/java/javaweb/distributed/mq/kafka/kafka-log-anatomy.png" width="400"/>
</div>


每个 Partition 都是一个有序的、不可变的记录序列，不断追加到结构化的提交日志中。Partition 中的记录每个分配一个连续的 id 号，称为偏移量（Offset），用于唯一标识 Partition 内的每条记录。

**Kafka 集群持久化保存（使用可配置的保留期限）所有发布记录——无论它们是否被消费**。例如，如果保留期限被设置为两天，则在记录发布后的两天之内，它都可以被消费，超过时间后将被丢弃以释放空间。Kafka 的性能和数据大小无关，所以长时间存储数据没有什么问题。

<div align="center">
<img src="http://kafka.apachecn.org/10/images/log_consumer.png" width="400"/>
</div>

实际上，保留在每个 Consumer 基础上的唯一元数据是该 Consumer 在日志中消费的位置。这个偏移量是由 Consumer 控制的：Consumer 通常会在读取记录时线性的增加其偏移量。但实际上，由于位置由 Consumer 控制，所以 Consumer 可以采用任何顺序来消费记录。

### 为什么要使用分区

对数据进行分区的主要原因，就是为了实现系统的**伸缩性**。不同的分区能够被放置到不同节点的机器上，而数据的读写操作也都是针对分区这个粒度而进行的，这样每个节点的机器都能独立地执行各自分区的读写请求处理。并且，我们还可以**通过添加新的节点机器来增加整体系统的吞吐量**。

日志中的 Partition 有以下几个用途：

- 首先，它实现了 Kafka 的**伸缩性**，可以通过添加新节点来**扩容**。
- 其次，不同的分区能够被放置到不同节点的机器上，而数据的读写操作也都是针对分区这个粒度而进行的，这样每个节点的机器都能独立地执行各自分区的读写请求处理。从而提升 Kafka 的**吞吐量**。

<div align="center">
<img src="http://dunwu.test.upcdn.net/cs/java/javaweb/distributed/mq/kafka/kafka-producer-consumer.png" width="640"/>
</div>

## 参考资料

- **官方**
  - [Kakfa 官网](http://kafka.apache.org/)
  - [Kakfa Github](https://github.com/apache/kafka)
  - [Kakfa 官方文档](https://kafka.apache.org/documentation/)
- **书籍**
  - [《Kafka 权威指南》](https://item.jd.com/12270295.html)
- **教程**
  - [Kafka 中文文档](https://github.com/apachecn/kafka-doc-zh)
  - [Kafka 核心技术与实战](https://time.geekbang.org/column/intro/100029201)
- **文章**
  - [Thorough Introduction to Apache Kafka](https://hackernoon.com/thorough-introduction-to-apache-kafka-6fbf2989bbc1)
  - [Kafka(03) Kafka 介绍](http://www.heartthinkdo.com/?p=2006#233)
  - [Kafka 剖析（一）：Kafka 背景及架构介绍](http://www.infoq.com/cn/articles/kafka-analysis-part-1)

## 🚪 传送

◾ 🏠 [BIGDATA-TUTORIAL 首页](https://github.com/dunwu/bigdata-tutorial) ◾ 🎯 [我的博客](https://github.com/dunwu/blog) ◾
# Kafka 生产者

<!-- TOC depthFrom:2 depthTo:3 -->

- [一、发送流程](#一发送流程)
  - [Kafka 要素](#kafka-要素)
  - [Producer 管理 TCP 连接](#producer-管理-tcp-连接)
  - [Kafka 发送流程](#kafka-发送流程)
- [二、发送方式](#二发送方式)
  - [异步发送](#异步发送)
  - [同步发送](#同步发送)
  - [异步回调发送](#异步回调发送)
- [三、序列化](#三序列化)
- [四、分区](#四分区)
- [五、幂等性](#五幂等性)
  - [PID 和 Sequence Number](#pid-和-sequence-number)
  - [生成 PID 的流程](#生成-pid-的流程)
  - [幂等性的应用实例](#幂等性的应用实例)
- [六、事务](#六事务)
  - [引入事务目的](#引入事务目的)
  - [事务操作的 API](#事务操作的-api)
  - [Kafka 事务相关配置](#kafka-事务相关配置)
  - [Kafka 事务应用示例](#kafka-事务应用示例)
- [七、压缩](#七压缩)
  - [Kafka 消息格式](#kafka-消息格式)
  - [Kafka 如何压缩](#kafka-如何压缩)
  - [何时解压缩](#何时解压缩)
  - [压缩算法](#压缩算法)
- [参考资料](#参考资料)

<!-- /TOC -->

## 一、发送流程

### Kafka 要素

Kafka 发送的对象叫做 `ProducerRecord` ，它有 4 个关键参数：

- `Topic` - 主题
- `Partition` - 分区（非必填）
- `Key` - 键（非必填）
- `Value` - 值

### Producer 管理 TCP 连接

Kafka Producer 端管理 TCP 连接的方式是：

1. Producer 实例创建时启动 Sender 线程，从而创建与 `bootstrap.servers` 中所有 Broker 的 TCP 连接。
2. Producer 实例首次更新元数据信息之后，还会再次创建与集群中所有 Broker 的 TCP 连接。
3. 如果 Producer 端发送消息到某台 Broker 时发现没有与该 Broker 的 TCP 连接，那么也会立即创建连接。
4. 如果设置 Producer 端 `connections.max.idle.ms` 参数大于 0，则步骤 1 中创建的 TCP 连接会被自动关闭；如果设置该参数 =-1，那么步骤 1 中创建的 TCP 连接将无法被关闭，从而成为“僵尸”连接。

### Kafka 发送流程

Kafka 生产者发送消息流程：

（1）**序列化** - 发送前，生产者要先把键和值序列化。

（2）**分区** - 数据被传给分区器。分区器决定了一个消息被分配到哪个分区。

（3）**批次传输** - 接着，这条记录会被添加到一个队列批次中。这个队列的所有消息都会发送到相同的主题和分区上。会由一个独立线程负责将这些记录批次发送到相应 Broker 上。

- **批次，就是一组消息，这些消息属于同一个主题和分区**。
- 发送时，会把消息分成批次传输，如果每一个消息发送一次，会导致大量的网路开销。

（4）**响应** - 服务器收到消息会返回一个响应。

- 如果**成功**，则返回一个 `RecordMetaData` 对象，它包含了主题、分区、偏移量；
- 如果**失败**，则返回一个错误。生产者在收到错误后，可以进行重试，重试次数可以在配置中指定。失败一定次数后，就返回错误消息。

![img](http://dunwu.test.upcdn.net/snap/20200528224323.png)

生产者在向 broker 发送消息时是怎么确定向哪一个 broker 发送消息？

- 生产者会向任意 broker 发送一个元数据请求（`MetadataRequest`），获取到每一个分区对应的 leader 信息，并缓存到本地。
- 生产者在发送消息时，会指定 Partition 或者通过 key 得到到一个 Partition，然后根据 Partition 从缓存中获取相应的 leader 信息。

![img](http://dunwu.test.upcdn.net/snap/20200621113043.png)

## 二、发送方式

Kafka 生产者核心配置：

- `bootstrap.servers` - broker 地址清单。
- `key.serializer` - 键的序列化器。
- `value.serializer` - 值的序列化器。

### 异步发送

直接发送消息，不关心消息是否到达。

这种方式吞吐量最高，但有小概率会丢失消息。

【示例】发送并忘记

```java
ProducerRecord<String, String> record =
            new ProducerRecord<>("CustomerCountry", "Precision Products", "France");
try {
    producer.send(record);
} catch (Exception e) {
    e.printStackTrace();
}
```

### 同步发送

返回一个 `Future` 对象，调用 `get()` 方法，会一直阻塞等待 `Broker` 返回结果。

这是一种可靠传输方式，但吞吐量最差。

【示例】同步发送

```java
ProducerRecord<String, String> record =
            new ProducerRecord<>("CustomerCountry", "Precision Products", "France");
try {
    producer.send(record).get();
} catch (Exception e) {
    e.printStackTrace();
}
```

### 异步响应发送

代码如下，异步方式相对于“发送并忽略返回”的方式的不同在于：在异步返回时可以执行一些操作，如：抛出异常、记录错误日志。

这是一个折中的方案，即兼顾吞吐量，也保证消息不丢失。

【示例】异步发送

首先，定义一个 callback：

```java
private class DemoProducerCallback implements Callback {
      @Override
        public void onCompletion(RecordMetadata recordMetadata, Exception e) {
           if (e != null) {
               e.printStackTrace();
             }
        }
}
```

然后，使用这个 callback：

```java
ProducerRecord<String, String> record =
            new ProducerRecord<>("CustomerCountry", "Biomedical Materials", "USA");
producer.send(record, new DemoProducerCallback());
```

## 三、序列化

Kafka 内置了常用 Java 基础类型的序列化器，如：`StringSerializer`、`IntegerSerializer`、`DoubleSerializer` 等。

但如果要传输较为复杂的对象，推荐使用序列化性能更高的工具，如：Avro、Thrift、Protobuf 等。

使用方式是通过实现 `org.apache.kafka.common.serialization.Serializer` 接口来引入自定义的序列化器。

## 四、分区

前文中已经提到，Kafka 生产者发送消息使用的对象 `ProducerRecord` ，可以选填 Partition 和 Key。

- 如果 `ProducerRecord` 指定了 Partition，则分区器什么也不做，否则分区器会选择一个分区。
- 如果传入的是 key，则通过分区器选择一个分区来保存这个消息；
- 如果 key 和 Partition 都没有指定，则会默认生成一个 key。

当指定这两个参数时，意味着：**会将特定的 key 发送给指定分区**。

> 说明：某些场景下，可能会要求按序发送消息。
>
> Kafka 的 Topic 如果是单分区，自然是有序的。但是，Kafka 是基于分区实现其高并发性的，如果使用单 partition，会严重降低 Kafka 的吞吐量。所以，这不是一个合理的方案。
>
> 还有一种方案是：生产者将同一个 key 的消息发送给指定分区，这可以保证同一个 key 在这个分区中是有序的。然后，消费者为每个 key 设定一个缓存队列，然后让一个独立线程负责消费指定 key 的队列，这就保证了消费消息也是有序的。

## 五、幂等性

在 Kafka 中，Producer **默认不是幂等性的**，但我们可以创建幂等性 Producer。它其实是 0.11.0.0 版本引入的新功能。在此之前，Kafka 向分区发送数据时，可能会出现同一条消息被发送了多次，导致消息重复的情况。在 0.11 之后，指定 Producer 幂等性的方法很简单，仅需要设置一个参数即可，即 `props.put(“enable.idempotence”, ture)`，或 `props.put(ProducerConfig.ENABLE_IDEMPOTENCE_CONFIG， true)`。

`enable.idempotence` 被设置成 true 后，Producer 自动升级成幂等性 Producer，其他所有的代码逻辑都不需要改变。Kafka 自动帮你做消息的去重。底层具体的原理很简单，就是经典的用空间去换时间的优化思路，即在 Broker 端多保存一些字段。当 Producer 发送了具有相同字段值的消息后，Broker 能够自动知晓这些消息已经重复了，于是可以在后台默默地把它们“丢弃”掉。当然，实际的实现原理并没有这么简单，但你大致可以这么理解。

我们必须要了解幂等性 Producer 的作用范围：

- 首先，**`enable.idempotence` 只能保证单分区上的幂等性**，即一个幂等性 Producer 能够保证某个主题的一个分区上不出现重复消息，它无法实现多个分区的幂等性。
- 其次，**它只能实现单会话上的幂等性，不能实现跨会话的幂等性**。这里的会话，你可以理解为 Producer 进程的一次运行。当你重启了 Producer 进程之后，这种幂等性保证就丧失了。

如果想实现多分区以及多会话上的消息无重复，应该怎么做呢？答案就是事务（transaction）或者依赖事务型 Producer。这也是幂等性 Producer 和事务型 Producer 的最大区别！

### PID 和 Sequence Number

为了实现 Producer 的幂等性，Kafka 引入了 Producer ID（即 PID）和 Sequence Number。

- **PID**。每个新的 Producer 在初始化的时候会被分配一个唯一的 PID，这个 PID 对用户是不可见的。
- **Sequence Numbler**。对于每个 PID，该 Producer 发送数据的每个 `<Topic, Partition>` 都对应一个从 0 开始单调递增的 Sequence Number。

Broker 端在缓存中保存了这 seq number，对于接收的每条消息，如果其序号比 Broker 缓存中序号大于 1 则接受它，否则将其丢弃。这样就可以实现了消息重复提交了。但是，只能保证单个 Producer 对于同一个 `<Topic, Partition>` 的 Exactly Once 语义。不能保证同一个 Producer 一个 topic 不同的 partion 幂等。

![img](http://www.heartthinkdo.com/wp-content/uploads/2018/05/1-1.png)
实现幂等之后：

![img](http://www.heartthinkdo.com/wp-content/uploads/2018/05/2.png)

### 生成 PID 的流程

在执行创建事务时，如下：

```java
Producer<String, String> producer = new KafkaProducer<String, String>(props);
```

会创建一个 Sender，并启动线程，执行如下 run 方法，在 maybeWaitForProducerId()中生成一个 producerId，如下：

```java
====================================
类名：Sender
====================================

void run(long now) {
        if (transactionManager != null) {
            try {
                 ........
                if (!transactionManager.isTransactional()) {
                    // 为idempotent producer生成一个producer id
                    maybeWaitForProducerId();
                } else if (transactionManager.hasUnresolvedSequences() && !transactionManager.hasFatalError()) {
                   ........
```

### 幂等性的应用实例

（1）配置属性

需要设置：

- `enable.idempotence`，需要设置为 ture，此时就会默认把 acks 设置为 all，所以不需要再设置 acks 属性了。

```java
// 指定生产者的配置
final Properties properties = new Properties();
properties.put(ProducerConfig.BOOTSTRAP_SERVERS_CONFIG, "localhost:9092");
// 设置 key 的序列化器
properties.put("key.serializer", "org.apache.kafka.common.serialization.StringSerializer");
// 设置 value 的序列化器
properties.put("value.serializer", "org.apache.kafka.common.serialization.StringSerializer");

// 开启幂等性
properties.put("enable.idempotence", true);
// 设置重试次数
properties.put("retries", 3);
//Reduce the no of requests less than 0
properties.put("linger.ms", 1);
// buffer.memory 控制生产者可用于缓冲的内存总量
properties.put("buffer.memory", 33554432);

// 使用配置初始化 Kafka 生产者
producer = new KafkaProducer<>(properties);
```

（2）发送消息

跟一般生产者一样，如下

```java
public void produceIdempotMessage(String topic, String message) {
    // 创建Producer
    Producer producer = buildIdempotProducer();
    // 发送消息
    producer.send(new ProducerRecord<String, String>(topic, message));
    producer.flush();
}
```

此时，因为我们并没有配置 `transaction.id` 属性，所以不能使用事务相关 API，如下

```java
producer.initTransactions();
```

否则会出现如下错误：

```java
Exception in thread “main” java.lang.IllegalStateException: Transactional method invoked on a non-transactional producer.
    at org.apache.kafka.clients.producer.internals.TransactionManager.ensureTransactional(TransactionManager.java:777)
    at org.apache.kafka.clients.producer.internals.TransactionManager.initializeTransactions(TransactionManager.java:202)
    at org.apache.kafka.clients.producer.KafkaProducer.initTransactions(KafkaProducer.java:544)
```

## 六、事务

**Kafka 事务属性是指一系列的生产者生产消息和消费者提交偏移量的操作在一个事务，或者说是是一个原子操作），同时成功或者失败**。

Kafka 自 0.11 版本开始提供了对事务的支持，目前主要是在 read committed 隔离级别上做事情。它能保证多条消息原子性地写入到目标分区，同时也能保证 Consumer 只能看到事务成功提交的消息。

事务型 Producer 能够保证将消息原子性地写入到多个分区中。这批消息要么全部写入成功，要么全部失败。另外，事务型 Producer 也不惧进程的重启。Producer 重启回来后，Kafka 依然保证它们发送消息的精确一次处理。

**事务属性实现前提是幂等性**，即在配置事务属性 `transaction.id` 时，必须还得配置幂等性；但是幂等性是可以独立使用的，不需要依赖事务属性。

### 引入事务目的

在事务属性之前先引入了生产者幂等性，它的作用为：

- **生产者多次发送消息可以封装成一个原子操作**，要么都成功，要么失败。
- consumer-transform-producer 模式下，因为消费者提交偏移量出现问题，导致**重复消费**。需要将这个模式下消费者提交偏移量操作和生产者一系列生成消息的操作封装成一个原子操作。

**消费者提交偏移量导致重复消费消息的场景**：消费者在消费消息完成提交便宜量 o2 之前挂掉了（假设它最近提交的偏移量是 o1），此时执行再均衡时，其它消费者会重复消费消息(o1 到 o2 之间的消息）。

### 事务操作的 API

`Producer` 提供了 `initTransactions`, `beginTransaction`, `sendOffsets`, `commitTransaction`, `abortTransaction` 五个事务方法。

```java
    /**
     * 初始化事务。需要注意的有：
     * 1、前提
     * 需要保证transation.id属性被配置。
     * 2、这个方法执行逻辑是：
     *   （1）Ensures any transactions initiated by previous instances of the producer with the same
     *      transactional.id are completed. If the previous instance had failed with a transaction in
     *      progress, it will be aborted. If the last transaction had begun completion,
     *      but not yet finished, this method awaits its completion.
     *    （2）Gets the internal producer id and epoch, used in all future transactional
     *      messages issued by the producer.
     *
     */
    public void initTransactions();

    /**
     * 开启事务
     */
    public void beginTransaction() throws ProducerFencedException ;

    /**
     * 为消费者提供的在事务内提交偏移量的操作
     */
    public void sendOffsetsToTransaction(Map<TopicPartition, OffsetAndMetadata> offsets,
                                         String consumerGroupId) throws ProducerFencedException ;

    /**
     * 提交事务
     */
    public void commitTransaction() throws ProducerFencedException;

    /**
     * 放弃事务，类似回滚事务的操作
     */
    public void abortTransaction() throws ProducerFencedException ;
```

### Kafka 事务相关配置

使用 kafka 的事务 api 时的一些注意事项：

- 需要消费者的自动模式设置为 false，并且不能子再手动的进行执行 `consumer#commitSync` 或者 `consumer#commitAsyc`
- 设置 Producer 端参数 `transctional.id`。最好为其设置一个有意义的名字。
- 和幂等性 Producer 一样，开启 `enable.idempotence = true`。如果配置了 `transaction.id`，则此时 `enable.idempotence` 会被设置为 true
- 消费者需要配置事务隔离级别 `isolation.level`。在 `consume-trnasform-produce` 模式下使用事务时，必须设置为 `READ_COMMITTED`。
  - `read_uncommitted`：这是默认值，表明 Consumer 能够读取到 Kafka 写入的任何消息，不论事务型 Producer 提交事务还是终止事务，其写入的消息都可以读取。很显然，如果你用了事务型 Producer，那么对应的 Consumer 就不要使用这个值。
  - `read_committed`：表明 Consumer 只会读取事务型 Producer 成功提交事务写入的消息。当然了，它也能看到非事务型 Producer 写入的所有消息。

### Kafka 事务应用示例

#### 只有生成操作

创建一个事务，在这个事务操作中，只有生成消息操作。代码如下：

```java
/**
 * 在一个事务只有生产消息操作
 */
public void onlyProduceInTransaction() {
    Producer producer = buildProducer();

    // 1.初始化事务
    producer.initTransactions();

    // 2.开启事务
    producer.beginTransaction();

    try {
        // 3.kafka写操作集合
        // 3.1 do业务逻辑

        // 3.2 发送消息
        producer.send(new ProducerRecord<String, String>("test", "transaction-data-1"));

        producer.send(new ProducerRecord<String, String>("test", "transaction-data-2"));
        // 3.3 do其他业务逻辑,还可以发送其他topic的消息。

        // 4.事务提交
        producer.commitTransaction();


    } catch (Exception e) {
        // 5.放弃事务
        producer.abortTransaction();
    }

}
```

创建生产者，代码如下,需要:

- 配置 `transactional.id` 属性
- 配置 `enable.idempotence` 属性

```java
/**
 * 需要:
 * 1、设置transactional.id
 * 2、设置enable.idempotence
 * @return
 */
private Producer buildProducer() {

    // create instance for properties to access producer configs
    Properties props = new Properties();

    // bootstrap.servers是Kafka集群的IP地址。多个时,使用逗号隔开
    props.put("bootstrap.servers", "localhost:9092");

    // 设置事务id
    props.put("transactional.id", "first-transactional");

    // 设置幂等性
    props.put("enable.idempotence",true);

    //Set acknowledgements for producer requests.
    props.put("acks", "all");

    //If the request fails, the producer can automatically retry,
    props.put("retries", 1);

    //Specify buffer size in config,这里不进行设置这个属性,如果设置了,还需要执行producer.flush()来把缓存中消息发送出去
    //props.put("batch.size", 16384);

    //Reduce the no of requests less than 0
    props.put("linger.ms", 1);

    //The buffer.memory controls the total amount of memory available to the producer for buffering.
    props.put("buffer.memory", 33554432);

    // Kafka消息是以键值对的形式发送,需要设置key和value类型序列化器
    props.put("key.serializer",
            "org.apache.kafka.common.serialization.StringSerializer");

    props.put("value.serializer",
            "org.apache.kafka.common.serialization.StringSerializer");


    Producer<String, String> producer = new KafkaProducer<String, String>(props);

    return producer;
}
```

#### 消费-生产并存（consume-transform-produce）

在一个事务中，既有生产消息操作又有消费消息操作，即常说的 Consume-tansform-produce 模式。如下实例代码

```java
/**
 * 在一个事务内,即有生产消息又有消费消息
 */
public void consumeTransferProduce() {
    // 1.构建上产者
    Producer producer = buildProducer();
    // 2.初始化事务(生成productId),对于一个生产者,只能执行一次初始化事务操作
    producer.initTransactions();

    // 3.构建消费者和订阅主题
    Consumer consumer = buildConsumer();
    consumer.subscribe(Arrays.asList("test"));
    while (true) {
        // 4.开启事务
        producer.beginTransaction();

        // 5.1 接受消息
        ConsumerRecords<String, String> records = consumer.poll(500);

        try {
            // 5.2 do业务逻辑;
            System.out.println("customer Message---");
            Map<TopicPartition, OffsetAndMetadata> commits = Maps.newHashMap();
            for (ConsumerRecord<String, String> record : records) {
                // 5.2.1 读取消息,并处理消息。print the offset,key and value for the consumer records.
                System.out.printf("offset = %d, key = %s, value = %s\n",
                        record.offset(), record.key(), record.value());

                // 5.2.2 记录提交的偏移量
                commits.put(new TopicPartition(record.topic(), record.partition()),
                        new OffsetAndMetadata(record.offset()));


                // 6.生产新的消息。比如外卖订单状态的消息,如果订单成功,则需要发送跟商家结转消息或者派送员的提成消息
                producer.send(new ProducerRecord<String, String>("test", "data2"));
            }

            // 7.提交偏移量
            producer.sendOffsetsToTransaction(commits, "group0323");

            // 8.事务提交
            producer.commitTransaction();

        } catch (Exception e) {
            // 7.放弃事务
            producer.abortTransaction();
        }
    }
}
```

创建消费者代码，需要:

- 将配置中的自动提交属性（auto.commit）进行关闭
- 而且在代码里面也不能使用手动提交 commitSync( )或者 commitAsync( )
- 设置 isolation.level

```java
/**
 * 需要:
 * 1、关闭自动提交 enable.auto.commit
 * 2、isolation.level为
 */
public Consumer buildConsumer() {
    Properties props = new Properties();
    // bootstrap.servers是Kafka集群的IP地址。多个时,使用逗号隔开
    props.put("bootstrap.servers", "localhost:9092");
    // 消费者群组
    props.put("group.id", "group0323");
    // 设置隔离级别
    props.put("isolation.level","read_committed");
    // 关闭自动提交
    props.put("enable.auto.commit", "false");
    props.put("session.timeout.ms", "30000");
    props.put("key.deserializer",
            "org.apache.kafka.common.serialization.StringDeserializer");
    props.put("value.deserializer",
            "org.apache.kafka.common.serialization.StringDeserializer");
    KafkaConsumer<String, String> consumer = new KafkaConsumer
            <String, String>(props);

    return consumer;
}
```

#### 只有消费操作

创建一个事务，在这个事务操作中，只有生成消息操作，如下代码。这种操作其实没有什么意义，跟使用手动提交效果一样，无法保证消费消息操作和提交偏移量操作在一个事务。

```java
/**
 * 在一个事务只有消息操作
 */
public void onlyConsumeInTransaction() {
    Producer producer = buildProducer();

    // 1.初始化事务
    producer.initTransactions();

    // 2.开启事务
    producer.beginTransaction();

    // 3.kafka读消息的操作集合
    Consumer consumer = buildConsumer();
    while (true) {
        // 3.1 接受消息
        ConsumerRecords<String, String> records = consumer.poll(500);

        try {
            // 3.2 do业务逻辑;
            System.out.println("customer Message---");
            Map<TopicPartition, OffsetAndMetadata> commits = Maps.newHashMap();
            for (ConsumerRecord<String, String> record : records) {
                // 3.2.1 处理消息 print the offset,key and value for the consumer records.
                System.out.printf("offset = %d, key = %s, value = %s\n",
                        record.offset(), record.key(), record.value());

                // 3.2.2 记录提交偏移量
                commits.put(new TopicPartition(record.topic(), record.partition()),
                        new OffsetAndMetadata(record.offset()));
            }

            // 4.提交偏移量
            producer.sendOffsetsToTransaction(commits, "group0323");

            // 5.事务提交
            producer.commitTransaction();

        } catch (Exception e) {
            // 6.放弃事务
            producer.abortTransaction();
        }
    }

}
```

## 七、压缩

### Kafka 消息格式

目前 Kafka 共有两大类消息格式，社区分别称之为 V1 版本和 V2 版本。V2 版本是 Kafka 0.11.0.0 中正式引入的。

不论是哪个版本，Kafka 的消息层次都分为两层：消息集合（message set）以及消息（message）。一个消息集合中包含若干条日志项（record item），而日志项才是真正封装消息的地方。Kafka 底层的消息日志由一系列消息集合日志项组成。Kafka 通常不会直接操作具体的一条条消息，它总是在消息集合这个层面上进行写入操作。

那么社区引入 V2 版本的目的是什么呢？V2 版本主要是针对 V1 版本的一些弊端做了修正。

原来在 V1 版本中，每条消息都需要执行 CRC 校验，但有些情况下消息的 CRC 值是会发生变化的。比如在 Broker 端可能会对消息时间戳字段进行更新，那么重新计算之后的 CRC 值也会相应更新；再比如 Broker 端在执行消息格式转换时（主要是为了兼容老版本客户端程序），也会带来 CRC 值的变化。鉴于这些情况，再对每条消息都执行 CRC 校验就有点没必要了，不仅浪费空间还耽误 CPU 时间，因此在 V2 版本中，消息的 CRC 校验工作就被移到了消息集合这一层。

V2 版本还有一个和压缩息息相关的改进，就是保存压缩消息的方法发生了变化。之前 V1 版本中保存压缩消息的方法是把多条消息进行压缩然后保存到外层消息的消息体字段中；而 V2 版本的做法是对整个消息集合进行压缩。显然后者应该比前者有更好的压缩效果。

### Kafka 如何压缩

在 Kafka 中，压缩可能发生在两个地方：生产者端和 Broker 端。

生产者程序中配置 `compression.type` 参数即表示启用指定类型的压缩算法。

【示例】开启 GZIP 的 Producer 对象

```java
Properties props = new Properties();
props.put("bootstrap.servers", "localhost:9092");
props.put("acks", "all");
props.put("key.serializer", "org.apache.kafka.common.serialization.StringSerializer");
props.put("value.serializer", "org.apache.kafka.common.serialization.StringSerializer");
// 开启 GZIP 压缩
props.put("compression.type", "gzip");

Producer<String, String> producer = new KafkaProducer<>(props);
```

其实大部分情况下 Broker 从 Producer 端接收到消息后仅仅是原封不动地保存而不会对其进行任何修改，但这里的“大部分情况”也是要满足一定条件的。有两种例外情况就可能让 Broker 重新压缩消息。

情况一：Broker 端指定了和 Producer 端不同的压缩算法。

情况二：Broker 端发生了消息格式转换。

所谓的消息格式转换主要是为了兼容老版本的消费者程序。在一个生产环境中，Kafka 集群中同时保存多种版本的消息格式非常常见。为了兼容老版本的格式，Broker 端会对新版本消息执行向老版本格式的转换。这个过程中会涉及消息的解压缩和重新压缩。一般情况下这种消息格式转换对性能是有很大影响的，除了这里的压缩之外，它还让 Kafka 丧失了引以为豪的 Zero Copy 特性。

### 何时解压缩

通常来说解压缩发生在消费者程序中，也就是说 Producer 发送压缩消息到 Broker 后，Broker 照单全收并原样保存起来。当 Consumer 程序请求这部分消息时，Broker 依然原样发送出去，当消息到达 Consumer 端后，由 Consumer 自行解压缩还原成之前的消息。

那么现在问题来了，Consumer 怎么知道这些消息是用何种压缩算法压缩的呢？其实答案就在消息中。Kafka 会将启用了哪种压缩算法封装进消息集合中，这样当 Consumer 读取到消息集合时，它自然就知道了这些消息使用的是哪种压缩算法。如果用一句话总结一下压缩和解压缩，那么我希望你记住这句话：**Producer 端压缩、Broker 端保持、Consumer 端解压缩。**

### 压缩算法

在 Kafka 2.1.0 版本之前，Kafka 支持 3 种压缩算法：GZIP、Snappy 和 LZ4。从 2.1.0 开始，Kafka 正式支持 Zstandard 算法（简写为 zstd）。

在实际使用中，GZIP、Snappy、LZ4 甚至是 zstd 的表现各有千秋。但对于 Kafka 而言，它们的性能测试结果却出奇得一致，即在吞吐量方面：LZ4 > Snappy > zstd 和 GZIP；而在压缩比方面，zstd > LZ4 > GZIP > Snappy。

如果客户端机器 CPU 资源有很多富余，**强烈建议开启 zstd 压缩，这样能极大地节省网络资源消耗**。

## 参考资料

- **官方**
  - [Kakfa 官网](http://kafka.apache.org/)
  - [Kakfa Github](https://github.com/apache/kafka)
  - [Kakfa 官方文档](https://kafka.apache.org/documentation/)
- **书籍**
  - [《Kafka 权威指南》](https://item.jd.com/12270295.html)
- **教程**
  - [Kafka 中文文档](https://github.com/apachecn/kafka-doc-zh)
  - [Kafka 核心技术与实战](https://time.geekbang.org/column/intro/100029201)
- **文章**
  - [Kafak(04) Kafka 生产者事务和幂等](http://www.heartthinkdo.com/?p=2040#43)
# Kafka 消费者

<!-- TOC depthFrom:2 depthTo:3 -->

- [一、消费者简介](#一消费者简介)
  - [消费者](#消费者)
  - [消费者群组](#消费者群组)
  - [分区再均衡](#分区再均衡)
  - [轮询获取消息](#轮询获取消息)
- [二、消费者 API](#二消费者-api)
  - [创建消费者](#创建消费者)
  - [订阅主题](#订阅主题)
  - [轮询](#轮询)
- [三、提交偏移量](#三提交偏移量)
  - [提交偏移量的旧方案](#提交偏移量的旧方案)
  - [提交偏移量的新方案](#提交偏移量的新方案)
  - [自动提交](#自动提交)
  - [手动提交](#手动提交)
- [五、如何退出](#五如何退出)
- [六、反序列化器](#六反序列化器)
- [七、独立消费者](#七独立消费者)
- [八、消费者的配置](#八消费者的配置)
- [参考资料](#参考资料)

<!-- /TOC -->

## 一、消费者简介

### 消费者

Kafka 消费者以 **pull 方式**从 broker 拉取消息，消费者可以订阅一个或多个主题，然后按照消息生成顺序（**kafka 只能保证分区中消息的顺序**）读取消息。

**一个消息只有在所有跟随者节点都进行了同步，才会被消费者获取到**。如下图，只能消费 Message0、Message1、Message2：

![img](http://dunwu.test.upcdn.net/snap/20200621113917.png)

### 消费者群组

Kafka 消费者从属于消费者群组，**一个群组里的 Consumer 订阅同一个 Topic，一个主题有多个 Partition，每一个 Partition 只能隶属于消费者群组中的一个 Consumer**。

- 同一时刻，**一条消息只能被同一消费者组中的一个消费者实例消费**。
- **消费者群组之间互不影响**。

![img](http://dunwu.test.upcdn.net/snap/20200621114128.png)

### 分区再均衡

### 轮询获取消息

Kafka 消费者通过 `poll` 来获取消息，但是获取消息时并不是立刻返回结果，需要考虑两个因素：

- 消费者通过 `customer.poll(time)` 中设置的等待时间
- broker 会等待累计一定量数据，然后发送给消费者。这样可以减少网络开销。

<div align="center">
<img src="http://upload-images.jianshu.io/upload_images/3101171-d7d111e7c7e7f504.png" />
</div>

poll 处了获取消息外，还有其他作用：

- **发送心跳信息**。消费者通过向被指派为群组协调器的 broker 发送心跳来维护他和群组的从属关系，当机器宕掉后，群组协调器触发再均衡。

## 二、消费者 API

### 创建消费者

```java
Properties props = new Properties();
props.put(ConsumerConfig.BOOTSTRAP_SERVERS_CONFIG, "localhost:9092");
props.put(ConsumerConfig.GROUP_ID_CONFIG, "test");
props.put(ConsumerConfig.ENABLE_AUTO_COMMIT_CONFIG, "false");
props.put(ConsumerConfig.KEY_DESERIALIZER_CLASS_CONFIG,
          "org.apache.kafka.common.serialization.StringDeserializer");
props.put(ConsumerConfig.VALUE_DESERIALIZER_CLASS_CONFIG,
          "org.apache.kafka.common.serialization.StringDeserializer");
KafkaConsumer<String, String> consumer = new KafkaConsumer<>(props);
```

### 订阅主题

```java
// 订阅主题列表
consumer.subscribe(Arrays.asList("t1", "t2"));

// 订阅所有与 test 相关的主题
consumer.subscribe("test.*");
```

### 轮询

消息轮询是消费者 API 的核心。一旦消费者订阅了主题，轮询就会处理所有细节，包括：群组协调、分区再均衡、发送心跳和获取数据。

```java
try {
    // 3. 轮询
    while (true) {
        // 4. 消费消息
        ConsumerRecords<String, String> records = consumer.poll(Duration.ofMillis(100));
        for (ConsumerRecord<String, String> record : records) {
            log.debug("topic = {}, partition = {}, offset = {}, key = {}, value = {}",
                record.topic(), record.partition(),
                record.offset(), record.key(), record.value());
        }
    }
} finally {
    // 5. 退出程序前，关闭消费者
    consumer.close();
}
```

## 三、提交偏移量

**更新分区当前位置的操作叫作提交**。

### 提交偏移量的旧方案

老版本的 Consumer Group 把位移保存在 ZooKeeper 中。ZooKeeper 是一个分布式的协调服务框架，Kafka 重度依赖它实现各种各样的协调管理。将位移保存在 ZooKeeper 外部系统的做法，最显而易见的好处就是减少了 Kafka Broker 端的状态保存开销。

ZooKeeper 这类元框架其实并不适合进行频繁的写更新，而 Consumer Group 的位移更新却是一个非常频繁的操作。这种大吞吐量的写操作会极大地拖慢 ZooKeeper 集群的性能，因此 Kafka 社区渐渐有了这样的共识：将 Consumer 位移保存在 ZooKeeper 中是不合适的做法。

### 提交偏移量的新方案

新版本 Consumer 的位移管理机制其实也很简单，就是**将 Consumer 的位移数据作为一条条普通的 Kafka 消息，提交到 **consumer_offsets 中。可以这么说，**consumer_offsets 的主要作用是保存 Kafka 消费者的位移信息。**

**位移主题的 Key 中应该保存 3 部分内容：`<Group ID，主题名，分区号 >`**。

通常来说，**当 Kafka 集群中的第一个 Consumer 程序启动时，Kafka 会自动创建位移主题**。我们说过，位移主题就是普通的 Kafka 主题，那么它自然也有对应的分区数。但如果是 Kafka 自动创建的，分区数是怎么设置的呢？这就要看 Broker 端参数 `offsets.topic.num.partitions` 的取值了。它的默认值是 50，因此 Kafka 会自动创建一个 50 分区的位移主题。如果你曾经惊讶于 Kafka 日志路径下冒出很多 `__consumer_offsets-xxx` 这样的目录，那么现在应该明白了吧，这就是 Kafka 自动帮你创建的位移主题啊。

你可能会问，除了分区数，副本数或备份因子是怎么控制的呢？答案也很简单，这就是 Broker 端另一个参数 offsets.topic.replication.factor 要做的事情了。它的默认值是 3。

总结一下，**如果位移主题是 Kafka 自动创建的，那么该主题的分区数是 50，副本数是 3**。

如果消费者一直处于运行状态，那么偏移量就没有什么用处。不过，如果消费者发生崩溃或有新的消费者加入群组，就会**触发再均衡**，完成再均衡后，每个消费者可能分配到新的分区，而不是之前处理的那个。为了能够继续之前的工作，消费者需要读取每个分区最后一次提交的偏移量，然后从偏移量指定的地方继续处理。

（1）**如果提交的偏移量小于客户端处理的最后一个消息的偏移量，那么处于两个偏移量之间的消息就会被重复处理**。

![img](http://dunwu.test.upcdn.net/snap/20200620162858.png)

（2）**如果提交的偏移量大于客户端处理的最后一个消息的偏移量，那么处于两个偏移量之间的消息将会丢失**。

![img](http://dunwu.test.upcdn.net/snap/20200620162946.png)

由此可知，处理偏移量，会对客户端处理数据产生影响。

### 自动提交

自动提交是 Kafka 处理偏移量最简单的方式。

当 `enable.auto.commit` 属性被设为 true，那么每过 `5s`，消费者会自动把从 `poll()` 方法接收到的最大偏移量提交上去。提交时间间隔由 `auto.commit.interval.ms` 控制，默认值是 `5s`。

与消费者里的其他东西一样，**自动提交也是在轮询里进行的**。消费者每次在进行轮询时会检查是否该提交偏移量了，如果是，那么就会提交从上一次轮询返回的偏移量。

假设我们仍然使用默认的 5s 提交时间间隔，在最近一次提交之后的 3s 发生了再均衡，再均衡之后，消费者从最后一次提交的偏移量位置开始读取消息。这个时候偏移量已经落后了 3s（因为没有达到 5s 的时限，并没有提交偏移量），所以在这 3s 的数据将会被重复处理。虽然可以通过修改提交时间间隔来更频繁地提交偏移量，减小可能出现重复消息的时间窗的时间跨度，不过这种情况是无法完全避免的。

在使用自动提交时，每次调用轮询方法都会把上一次调用返回的偏移量提交上去，它并不知道具体哪些消息已经被处理了，所以在再次调用之前最好确保所有当前调用返回的消息都已经处理完毕（在调用 close() 方法之前也会进行自动提交）。一般情况下不会有什么问题，不过在处理异常或提前退出轮询时要格外小心。

**自动提交虽然方便，不过无法避免重复消息问题**。

### 手动提交

自动提交无法保证消息可靠性传输。

因此，为了解决丢失消息的问题，可以通过手动提交偏移量。

首先，**把 `enable.auto.commit` 设为 false，关闭自动提交**。

#### （1）同步提交

**使用 `commitSync()` 提交偏移量最简单也最可靠**。这个 API 会提交由 `poll()` 方法返回的最新偏移量，提交成功后马上返回，如果提交失败就抛出异常。

```java
while (true) {
    ConsumerRecords<String, String> records = consumer.poll(100);
    for (ConsumerRecord<String, String> record : records) {
        System.out.printf("topic = %s, partition = %s, offset = %d, customer = %s, country = %s\n",
            record.topic(), record.partition(),
            record.offset(), record.key(), record.value());
    }
    try {
        consumer.commitSync();
    } catch (CommitFailedException e) {
        log.error("commit failed", e)
    }
}
```

同步提交的缺点：**同步提交方式会一直阻塞，直到接收到 Broker 的响应请求，这会大大限制吞吐量**。

#### （2）异步提交

**在成功提交或碰到无法恢复的错误之前，`commitSync()` 会一直重试，但是 `commitAsync()` 不会**，这也是 `commitAsync()` 不好的一个地方。**它之所以不进行重试，是因为在它收到服务器响应的时候，可能有一个更大的偏移量已经提交成功**。假设我们发出一个请求用于提交偏移量 2000，这个时候发生了短暂的通信问题，服务器收不到请求，自然也不会作出任何响应。与此同时，我们处理了另外一批消息，并成功提交了偏移量 3000。如果 `commitAsync()` 重新尝试提交偏移量 2000，它有可能在偏移量 3000 之后提交成功。这个时候**如果发生再均衡，就会出现重复消息**。

```java
while (true) {
    ConsumerRecords<String, String> records = consumer.poll(Duration.ofMillis(100));
    for (ConsumerRecord<String, String> record : records) {
        System.out.printf("topic = %s, partition = %s, offset = % d, customer = %s, country = %s\n ",
            record.topic(), record.partition(), record.offset(),
            record.key(), record.value());
    }
    consumer.commitAsync();
}
```

**`commitAsync()` 也支持回调**，在 broker 作出响应时会执行回调。**回调经常被用于记录提交错误或生成度量指标，不过如果要用它来进行重试，则一定要注意提交的顺序**。

```java
while (true) {
    ConsumerRecords<String, String> records = consumer.poll(Duration.ofMillis(100));
    for (ConsumerRecord<String, String> record : records) {
        System.out.printf("topic = %s, partition = %s, offset = % d, customer = %s, country = %s\n ",
            record.topic(), record.partition(), record.offset(),
            record.key(), record.value());
    }
    consumer.commitAsync(new OffsetCommitCallback() {
        @Override
        public void onComplete(Map<TopicPartition, OffsetAndMetadata> offsets, Exception e) {
            if (e != null) { log.error("Commit failed for offsets {}", offsets, e); }
        }
    });
}
```

> **重试异步提交**
>
> 可以使用一个单调递增的序列号来维护异步提交的顺序。在每次提交偏移量之后或在回调里提交偏移量时递增序列号。在进行重试前，先检查回调の序列号和即将提交的偏移量是否相等，如果相等，说明没有新的提交，那么可以安全地进行重试；如果序列号比较大，说明有一个新的提交已经发送出去了，应该停止重试。

#### （3）同步和异步组合提交

一般情况下，针对偶尔出现的提交失败，不进行重试不会有太大问题，因为如果提交失败是因为临时问题导致的，那么后续的提交总会有成功的。但**如果这是发生在关闭消费者或再均衡前的最后一次提交，就要确保能够提交成功**。

因此，在消费者关闭前一般会组合使用 `commitSync()` 和 `commitAsync()`。

```java
try {
    while (true) {
        ConsumerRecords<String, String> records = consumer.poll(Duration.ofMillis(100));
        for (ConsumerRecord<String, String> record : records) {
            System.out.printf("topic = %s, partition = %s, offset = % d, customer = %s, country = %s\n ",
                record.topic(), record.partition(), record.offset(), record.key(), record.value());
        }
        consumer.commitAsync();
    }
} catch (Exception e) {
    log.error("Unexpected error", e);
} finally {
    try {
        consumer.commitSync();
    } finally {
        consumer.close();
    }
}
```

#### （4）提交特定的偏移量

提交偏移量的频率和处理消息批次的频率是一样的。如果想要更频繁地提交该怎么办？如果 `poll()` 方法返回一大批数据，为了避免因再均衡引起的重复处理整批消息，想要在批次中间提交偏移量该怎么办？这种情况无法通过调用 `commitSync()` 或 `commitAsync()` 来实现，因为它们只会提交最后一个偏移量，而此时该批次里的消息还没有处理完。

解决办法是：**消费者 API 允许在调用 `commitSync()` 和 `commitAsync()` 方法时传进去希望提交的分区和偏移量的 map**。

```java
private int count = 0;
private final Map<TopicPartition, OffsetAndMetadata> currentOffsets = new HashMap<>();


while (true) {
  ConsumerRecords<String, String> records = consumer.poll(100);
  for (ConsumerRecord<String, String> record : records) {
    System.out.printf("topic = %s, partition = %s, offset = % d, customer = %s, country = %s\n ",
                      record.topic(), record.partition(), record.offset(), record.key(), record.value());

    currentOffsets.put(new TopicPartition(record.topic(),
                                          record.partition()), new
                       OffsetAndMetadata(record.offset() + 1, "no metadata"));
    if (count % 1000 == 0) { consumer.commitAsync(currentOffsets, null); }
    count++;
  }
}
```

#### （5）从特定偏移量处开始处理

使用 `poll()` 方法可以从各个分区的最新偏移量处开始处理消息。

不过，有时候，我们可能需要从特定偏移量处开始处理消息。

- 从分区的起始位置开始读消息：`seekToBeginning(Collection<TopicPartition> partitions)` 方法
- 从分区的末尾位置开始读消息：`seekToEnd(Collection<TopicPartition> partitions)` 方法
- 查找偏移量：`seek(TopicPartition partition, long offset)` 方法

通过 `seek(TopicPartition partition, long offset)` 可以实现处理消息和提交偏移量在一个事务中完成。思路就是需要在客户端建立一张数据表，保证处理消息和和消息偏移量位置写入到这张数据表。在一个事务中，此时就可以保证处理消息和记录偏移量要么同时成功，要么同时失败。

```java
    consumer.subscribe(topic);
    // 1.第一次调用pool,加入消费者群组
    consumer.poll(0);
    // 2.获取负责的分区，并从本地数据库读取改分区最新偏移量，并通过seek方法修改poll获取消息的位置
    for (TopicPartition partition: consumer.assignment())
        consumer.seek(partition, getOffsetFromDB(partition));

    while (true) {
        ConsumerRecords<String, String> records =
        consumer.poll(100);
        for (ConsumerRecord<String, String> record : records)
        {
            processRecord(record);
            storeRecordInDB(record);
            storeOffsetInDB(record.topic(), record.partition(),
            record.offset());
        }
        commitDBTransaction();
    }
```

## 五、如何退出

**如果想让消费者从轮询消费消息的无限循环中退出，可以通过另一个线程调用 `consumer.wakeup()` 方法**。 **`consumer.wakeup()` 是消费者唯一一个可以从其他线程里安全调用的方法**。调用 `consumer.wakeup()` 可以退出 `poll()` ，并抛出 `WakeupException` 异常，或者如果调用 `consumer.wakeup()` 时线程没有等待轮询，那么异常将在下一轮调用 `poll()` 时抛出。

```java
Runtime.getRuntime().addShutdownHook(new Thread() {
    public void run() {
        System.out.println("Starting exit...");
        consumer.wakeup();
        try {
            mainThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
});

...

try {
    // looping until ctrl-c, the shutdown hook will cleanup on exit
    while (true) {
        ConsumerRecords<String, String> records =
            movingAvg.consumer.poll(1000);
        System.out.println(System.currentTimeMillis() +
            "--  waiting for data...");
        for (ConsumerRecord<String, String> record : records) {
            System.out.printf("offset = %d, key = %s, value = %s\n",
                record.offset(), record.key(), record.value());
        }
        for (TopicPartition tp: consumer.assignment())
            System.out.println("Committing offset at position:" +
                consumer.position(tp));
            movingAvg.consumer.commitSync();
    }
} catch (WakeupException e) {
    // ignore for shutdown
} finally {
    consumer.close();
    System.out.println("Closed consumer and we are done");
}
```

## 六、反序列化器

生产者需要用**序列化器**将 Java 对象转换成字节数组再发送给 Kafka；同理，消费者需要用**反序列化器**将从 Kafka 接收到的字节数组转换成 Java 对象。

## 七、独立消费者

通常，会有多个 Kafka 消费者组成群组，关注一个主题。

但可能存在这样的场景：只需要一个消费者从一个主题的所有分区或某个特定的分区读取数据。这时，就不需要消费者群组和再均衡了，只需要**把主题或分区分配给消费者**，然后开始读取消息并提交偏移量。

如果是这样，就不需要订阅主题，取而代之的是为自己分配分区。一个消费者可以订阅主题（并加入消费者群组），或为自己分配分区，但不能同时做这两件事。

```java
List<PartitionInfo> partitionInfos = null;
partitionInfos = consumer.partitionsFor("topic");

if (partitionInfos != null) {
    for (PartitionInfo partition : partitionInfos)
        partitions.add(new TopicPartition(partition.topic(),
            partition.partition()));
    consumer.assign(partitions);

    while (true) {
        ConsumerRecords<String, String> records = consumer.poll(1000);

        for (ConsumerRecord<String, String> record: records) {
            System.out.printf("topic = %s, partition = %s, offset = %d,
                customer = %s, country = %s\n",
                record.topic(), record.partition(), record.offset(),
                record.key(), record.value());
        }
        consumer.commitSync();
    }
}
```

## 八、消费者的配置

- **`bootstrap.servers`** - broker 集群地址，格式：ip1:port,ip2:port...，不需要设定全部的集群地址，设置两个或者两个以上即可。
- **`group.id`** - 消费者隶属的消费者组名称，如果为空会报异常，一般而言，这个参数要有一定的业务意义。
- **`fetch.min.bytes`** - 消费者获取记录的最小字节数。Kafka 会等到有足够的数据时才返回消息给消费者，以降低负载。
- **`fetch.max.wait.ms`** - 用于指定 broker 的等待时间。
- **`max.partition.fetch.bytes`** - 指定了服务器从每个分区返回给消费者的最大字节数。默认为 1 MB。
- **`session.timeout.ms`** - 指定了消费的心跳超时时间。如果消费者没有在超时时间内发送心跳给群组协调器，协调器会视消费者已经消亡，从而触发再均衡。默认为 3 秒。
- **`auto.offset.reset`** - 制定了消费者在读取一个没有偏移量的分区或偏移量无效的情况下，该如何处理。
  - latest，表示在偏移量无效时，消费者将从最新的记录开始读取分区记录。
  - earliest，表示在偏移量无效时，消费者将从起始位置读取分区记录。
- **`enable.auto.commit`** - 指定了是否自动提交消息偏移量，默认开启。
- **`partition.assignment.strategy`** - 消费者的分区分配策略。
  - Range，表示会将主题的若干个连续的分区分配给消费者。
  - RoundRobin，表示会将主题的所有分区逐个分配给消费者。
- **`client.id`** - 客户端标识。
- **`max.poll.records`** - 用于控制单次能获取到的记录数量。
- **`receive.buffer.bytes`** - 用于设置 Socket 接收消息缓冲区（SO_RECBUF）的大小，默认值为 64KB。如果设置为-1，则使用操作系统的默认值。
- **`send.buffer.bytes`** - 用于设置 Socket 发送消息缓冲区（SO_SNDBUF）的大小，默认值为 128KB。与 receive.buffer.bytes 参数一样，如果设置为-1，则使用操作系统的默认值。

## 参考资料

- **官方**
  - [Kakfa 官网](http://kafka.apache.org/)
  - [Kakfa Github](https://github.com/apache/kafka)
  - [Kakfa 官方文档](https://kafka.apache.org/documentation/)
- **书籍**
  - [《Kafka 权威指南》](https://item.jd.com/12270295.html)
- **教程**
  - [Kafka 中文文档](https://github.com/apachecn/kafka-doc-zh)
  - [Kafka 核心技术与实战](https://time.geekbang.org/column/intro/100029201)
# Kafka 集群

> Kafka 是一个分布式的、可水平扩展的、基于发布/订阅模式的、支持容错的消息系统。

<!-- TOC depthFrom:2 depthTo:3 -->

- [一、集群成员](#一集群成员)
- [二、复制](#二复制)
  - [Kafka 副本](#kafka-副本)
  - [ISR](#isr)
- [二、控制器](#二控制器)
  - [如何选举控制器](#如何选举控制器)
  - [控制器的作用](#控制器的作用)
- [四、选举 Leader](#四选举-leader)
  - [Unclean 领导者选举](#unclean-领导者选举)
- [五、处理请求](#五处理请求)
  - [元数据请求](#元数据请求)
  - [生产请求](#生产请求)
  - [消费请求](#消费请求)
  - [其他请求](#其他请求)
- [六、物理存储](#六物理存储)
  - [Partition 分配](#partition-分配)
  - [文件管理](#文件管理)
  - [文件格式](#文件格式)
  - [索引](#索引)
  - [清理](#清理)
  - [删除事件](#删除事件)
- [七、部署方案](#七部署方案)
  - [操作系统](#操作系统)
  - [磁盘](#磁盘)
  - [带宽](#带宽)
- [参考资料](#参考资料)

<!-- /TOC -->

## 一、集群成员

**Kafka 使用 Zookeeper 来维护集群成员的信息**。每个 broker 都有一个唯一标识符，这个标识符可以在配置文件里指定，也可以自动生成。在 broker 启动的时候，它通过创建**临时节点**把自己的 ID 注册到 Zookeeper。Kafka 组件订阅 Zookeeper 的 `/broker/ids` 路径，当有 broker 加入集群或退出集群时，这些组件就可以获得通知。

> ZooKeeper 两个重要特性：
>
> - 客户端会话结束时，ZooKeeper 就会删除临时节点。
> - 客户端注册监听它关心的节点，当节点状态发生变化（数据变化、子节点增减变化）时，ZooKeeper 服务会通知客户端。
>
> 详细内容可以参考：[ZooKeeper 应用指南](https://github.com/dunwu/bigdata-tutorial/blob/master/docs/zookeeper/zookeeper-quickstart.md)

## 二、复制

复制功能是 Kafka 架构的核心。复制之所以关键，是因为它可以在个别节点失效时仍能保证 Kafka 的可用性和持久性。

![img](http://dunwu.test.upcdn.net/cs/java/javaweb/distributed/mq/kafka/kafka-replication.png)

### Kafka 副本

Kafka 使用 Topic 来组织数据，每个 Topic 被分为若干个 Partition。每个 Partition 有多个副本。每个 broker 可以保存成百上千个属于不同 Topic 和 Partition 的副本。**Kafka 副本的本质是一个只能追加写入的提交日志**。

![img](http://dunwu.test.upcdn.net/snap/20200727164028.png)

副本有两种类型：

- Leader 副本（主）：每个 Partition 都有一个 Leader 副本。**Leader 处理一切对 Partition （分区）的读写请求**；
- Follower 副本（从）：Leader 副本以外的副本都是 Follower 副本。**Follower 唯一的任务就是从 Leader 那里异步复制消息，保持与 Leader 一致的状态**。如果 Leader 宕机，其中一个 Follower 会被选举为新的 Leader。

![img](http://dunwu.test.upcdn.net/snap/20200727165327.png)

为了与 Leader 保持同步，Follower 向 Leader 发起异步请求，拉取数据。请求消息里包含了 Follower 想要获取消息的偏移量，而这些偏移量总是有序的。通过查看每个 Follower 请求的最新偏移量，Leader 就会知道每个 Follower 复制的进度。

### ISR

ISR 即 In-sync Replicas，表示同步副本。Follower 副本不提供服务，只是定期地异步拉取领导者副本中的数据而已。既然是异步的，说明和 Leader 并非数据强一致性的。

**判断 Follower 是否与 Leader 同步的标准**：

Kafka Broker 端参数 `replica.lag.time.max.ms` 参数，指定了 Follower 副本能够落后 Leader 副本的最长时间间隔，默认为 10s。这意味着：只要一个 Follower 副本落后 Leader 副本的时间不连续超过 10 秒，那么 Kafka 就认为该 Follower 副本与 Leader 是**同步**的，即使此时 Follower 副本中保存的消息明显少于 Leader 副本中的消息。

ISR 是一个动态调整的集合，会不断将同步副本加入集合，将不同步副本移除集合。Leader 副本天然就在 ISR 中。

## 二、控制器

**控制器组件（Controller），是 Apache Kafka 的核心组件。它的主要作用是在 ZooKeeper 的帮助下管理和协调整个 Kafka 集群**。

![img](http://dunwu.test.upcdn.net/cs/java/javaweb/distributed/mq/kafka/kafka-metadata-flow.png)

### 如何选举控制器

集群中任意一台 Broker 都能充当控制器的角色，但是，在运行过程中，只能有一个 Broker 成为控制器，行使其管理和协调的职责。实际上，Broker 在启动时，会尝试去 ZooKeeper 中创建 `/controller` 节点。Kafka 当前选举控制器的规则是：**第一个成功创建 `/controller` 临时节点的 Broker 会被指定为控制器**。

选举控制器详细流程：

（1）第一个在 ZooKeeper 中成功创建 `/controller` 临时节点的 Broker 会被指定为控制器。

（2）其他 broker 在控制器节点上创建 Zookeeper watch 对象。

（3）如果控制器被关闭或者与 Zookeeper 断开连接，Zookeeper 临时节点就会消失。集群中的其他 broker 通过 watch 对象得到状态变化的通知，它们会尝试让自己成为新的控制器。

（4）第一个在 Zookeeper 里创建一个临时节点 `/controller` 的 broker 成为新控制器。其他 broker 在新控制器节点上创建 Zookeeper watch 对象。

（5）每个新选出的控制器通过 Zookeeper 的条件递增操作获得一个全新的、数值更大的 controller epoch。其他节点会忽略旧的 epoch 的消息。

（6）当一个 broker 离开集群，并且这个 broker 是某些 Partition 的 Leader。此时，控制器会遍历这些 Partition，并用轮询方式确定谁应该成为新 Leader，随后，新 Leader 开始处理生产者和消费者的请求，而 Follower 开始从 Leader 那里复制消息。

简而言之，**Kafka 使用 Zookeeper 的临时节点来选举控制器，并在节点加入集群或退出集群时通知控制器。控制器负责在节点加入或离开集群时进行 Partition Leader 选举。控制器使用 epoch 来避免“脑裂”，“脑裂”是指两个节点同时被认为自己是当前的控制器**。

### 控制器的作用

#### 主题管理（创建、删除、增加分区）

这里的主题管理，就是指控制器帮助我们完成对 Kafka 主题的创建、删除以及分区增加的操作。换句话说，当我们执行**kafka-topics 脚本**时，大部分的后台工作都是控制器来完成的。

#### 分区重分配

分区重分配主要是指，**kafka-reassign-partitions 脚本**（关于这个脚本，后面我也会介绍）提供的对已有主题分区进行细粒度的分配功能。这部分功能也是控制器实现的。

#### 领导者选举

Preferred 领导者选举主要是 Kafka 为了避免部分 Broker 负载过重而提供的一种换 Leader 的方案。在专栏后面说到工具的时候，我们再详谈 Preferred 领导者选举，这里你只需要了解这也是控制器的职责范围就可以了。

#### 集群成员管理

集群成员管理，包括自动检测新增 Broker、Broker 主动关闭及被动宕机。这种自动检测是依赖于前面提到的 Watch 功能和和 ZooKeeper 临时节点组合实现的。

比如，控制器组件会利用**Watch 机制**检查 ZooKeeper 的 /brokers/ids 节点下的子节点数量变更。目前，当有新 Broker 启动后，它会在 /brokers 下创建专属的 znode 节点。一旦创建完毕，ZooKeeper 会通过 Watch 机制将消息通知推送给控制器，这样，控制器就能自动地感知到这个变化，进而开启后续的新增 Broker 作业。

侦测 Broker 存活性则是依赖于刚刚提到的另一个机制：**临时节点**。每个 Broker 启动后，会在 /brokers/ids 下创建一个临时 znode。当 Broker 宕机或主动关闭后，该 Broker 与 ZooKeeper 的会话结束，这个 znode 会被自动删除。同理，ZooKeeper 的 Watch 机制将这一变更推送给控制器，这样控制器就能知道有 Broker 关闭或宕机了，从而进行“善后”。

#### 数据服务

控制器的最后一大类工作，就是向其他 Broker 提供数据服务。控制器上保存了最全的集群元数据信息，其他所有 Broker 会定期接收控制器发来的元数据更新请求，从而更新其内存中的缓存数据。

控制器中保存了多种数据，比较重要的的数据有：

- 所有主题信息。包括具体的分区信息，比如领导者副本是谁，ISR 集合中有哪些副本等。
- 所有 Broker 信息。包括当前都有哪些运行中的 Broker，哪些正在关闭中的 Broker 等。
- 所有涉及运维任务的分区。包括当前正在进行 Preferred 领导者选举以及分区重分配的分区列表。

值得注意的是，这些数据其实在 ZooKeeper 中也保存了一份。每当控制器初始化时，它都会从 ZooKeeper 上读取对应的元数据并填充到自己的缓存中。有了这些数据，控制器就能对外提供数据服务了。这里的对外主要是指对其他 Broker 而言，控制器通过向这些 Broker 发送请求的方式将这些数据同步到其他 Broker 上。

## 四、选举 Leader

### Unclean 领导者选举

因为 Leader 副本天然就在 ISR 中，如果 ISR 为空了，就说明 Leader 副本也“挂掉”了，Kafka 需要重新选举一个新的 Leader。

**Kafka 把所有不在 ISR 中的存活副本都称为非同步副本**。通常来说，非同步副本落后 Leader 太多，因此，如果选择这些副本作为新 Leader，就可能出现数据的丢失。毕竟，这些副本中保存的消息远远落后于老 Leader 中的消息。在 Kafka 中，选举这种副本的过程称为 Unclean 领导者选举。**Broker 端参数 `unclean.leader.election.enable` 控制是否允许 Unclean 领导者选举**。

**开启 Unclean 领导者选举可能会造成数据丢失**，但好处是：它使得 Partition Leader 副本一直存在，不至于停止对外提供服务，因此提升了高可用性。反之，禁止 Unclean 领导者选举的好处在于维护了数据的一致性，避免了消息丢失，但牺牲了高可用性。

## 五、处理请求

broker 的大部分工作是处理客户端、Partition 副本和控制器发送给 Partition Leader 的请求。Kafka 提供了一个二进制协议（基于 TCP），指定了请求消息的格式以及 broker 如何对请求作出响应。

broker 会在它所监听的每一个端口上运行一个 Acceptor 线程，这个线程会创建一个连接，并把它交给 Processor 线程去处理。Processor 线程负责从客户端获取请求消息，把它们放进请求队列，然后从响应队列获取响应消息，把它们发送给客户端。

当请求放进请求队列后，IO 线程负责进行处理。

![img](http://dunwu.test.upcdn.net/snap/20200621122854.png)

生产请求和拉取请求都需要发送给 Partition 的 Leader 副本处理。

### 元数据请求

客户端怎么知道哪个是主副本呢？客户端通过使用另一种类型的请求来实现，那就是**元数据请求（metadata request）**。这种请求包含了客户端感兴趣的 Topic 列表。broker 的响应消息指明了这些 Topic 所包含的 Partition、Partition 有哪些副本，以及那个副本是 Leader。元数据请求可以发给任意一个 broker，因为所有 broker 都缓存了这些信息。

客户端会把这些信息缓存起来，并直接往目标 broker 上发送生产请求和获取请求。它们需要时不时地通过发送元数据请求来刷新这些信息（刷新的时间间隔通过 `metadata.max.age.ms` 来配置），从而知道元数据是否发生了变化。

![img](http://dunwu.test.upcdn.net/snap/20200621123848.png)

### 生产请求

acks 参数控制多少个副本确认写入成功后生产者才认为消息生产成功。这个参数的取值可以为：

- `acks=0` - 消息发送完毕，生产者认为消息写入成功；
- `acks=1` - 主副本写入成功，生产者认为消息写入成功；
- `acks=all` - 所有同步副本写入成功，生产者才认为消息写入成功。

如果主副本收到生产消息，它会执行一些检查逻辑，包含：

- 发送的用户是否有权限写入 Topic？
- 请求的 acks 参数取值是否合法（只允许 0，1，all）？
- 如果 acks 设置为 all，是否有足够的 in-sync 副本来安全写入消息？（我们可以配置如果 in-sync 副本低于一定数量，主副本拒绝写入消息）

之后，消息被写入到本地磁盘。一旦消息本地持久化后，如果 acks 被设为 0 或 1 那么会返回结果给客户端，如果 acks 被设为 all 那么会将请求放置在一个称为 purgatory 的缓冲区中等待其他的副本写入完成。

### 消费请求

主副本处理拉取请求和处理生产请求的方式很相似：

1. 请求需要先到达指定的 Partition 主副本上，然后客户端通过查询元数据来确保请求的路由是正确的。
2. 主副本在收到请求时，会先检查请求是否有效。
3. 如果请求的偏移量存在，broker 将按照客户端指定的数量上限从 Partition 里读取消息，再把消息返回给客户端。

**客户端可以指定返回的最大数据量，防止数据量过大造成客户端内存溢出**。同时，**客户端也可以指定返回的最小数据量**，当消息数据量没有达到最小数据量时，请求会一直阻塞直到有足够的数据返回。指定最小的数据量在负载不高的情况下非常有用，通过这种方式**可以减轻网络往返的额外开销**。当然请求也不能永远的阻塞，客户端可以指定最大的阻塞时间，如果到达指定的阻塞时间，即便没有足够的数据也会返回。

Kafka 使用零复制（zero-copy）来提高性能。也就是说，Kafka 将文件（更准确的说，是文件系统缓存）的消息直接传给网络通道，并没有使用中间的 buffer。这避免了内存的字节拷贝和 buffer 维护，极大地提高了性能。

![img](http://dunwu.test.upcdn.net/snap/20200621124516.png)

不是所有主副本的数据都能够被读取。**当数据被所有同步副本写入成功后，它才能被客户端读取**。主副本知道每个消息会被复制到哪个副本上，在消息还没有被写入到所有同步副本之前，是不会发送给消费者的。

因为还没有被足够的副本持久化的消息，被认为是不安全的——如果主副本发生故障，另一个副本成为新的主副本，这些消息就丢失了。如果允许读取这些消息，就可能会破坏数据一致性。

这也意味着，如果 broker 间的消息复制因为某些原因变慢了，那么消息到达消费者的时间也会随之边长。延迟时间可以通过 replica.lag.time.max.ms 来配置，它指定了副本在复制消息时可被允许的最大延迟时间。

![img](http://dunwu.test.upcdn.net/snap/20200621124533.png)

### 其他请求

我们讨论了 Kafka 中最常见的三种请求类型：元信息请求，生产请求和拉取请求。这些请求都是使用的是 Kafka 的自定义二进制协议。集群中 broker 间的通信请求也是使用同样的协议，这些请求是内部使用的，客户端不能发送。比如在选举 Partition 主副本过程中，控制器会发送 LeaderAndIsr 请求给新的主副本和其他跟随副本。

这个协议目前已经支持 20 种请求类型，并且仍然在演进以支持更多的类型。

## 六、物理存储

**Kafka 的基本存储单元是 Partition**。Partition 无法在多个 broker 间进行再细分。

### Partition 分配

当创建一个新 Topic 时，Kafka 首先需要决定如何分配 Partition 到不同的 broker。分配策略主要的考虑因素如下：

- 尽可能将 Partition 副本均衡分配到集群的 broker 中；
- 对于每个 Partition，它的所有副本需要在不同的 broker；
- 如果为 broker 制定了机架信息（0.10.0 及更高版本），尽可能地把每个 Partition 的副本分配到不同的机架。

### 文件管理

**Kafka 不会一直保留数据，也不会等待所有的消费者读取了消息才删除消息**。只要数据量达到上限或者数据达到过期时间，Kafka 会删除老的消息数据。

因为在一个大文件中查找和删除消息是非常耗时且容易出错的。所以，Kafka 将每个 Partition 切割成段（segment）。**默认每个段大小不超过 1G，且只包含 7 天的数据**。如果段的消息量达到 1G，那么该段会关闭，同时打开一个新的段进行写入。

**正在写入的段称为活跃段（active segment），活跃段不会被删除**。

对于每个 Partition 的每个段（包括不活跃的段），broker 都会维护文件句柄，因此打开的文件句柄数通常会比较多，这个需要适度调整系统的进程文件句柄参数。

### 文件格式

Kafka 的消息和偏移量保存在文件里。**保存在磁盘上的数据格式和从生产者发送过来或消费者读取的数据格式是一样的。使用相同的数据格式使得 Kafka 可以进行零复制技术给消费者发送消息，同时避免了压缩和解压**。

除了键、值和偏移量外，消息里还包含了消息大小、校验和（检测数据损坏）、魔数（标识消息格式版本）、压缩算法（Snappy、GZip 或者 LZ4）和时间戳（0.10.0 新增）。时间戳可以是生产者发送消息的时间，也可以是消息到达 broker 的时间，这个是可配的。

如果发送者发送压缩的消息，那么批量发送的消息会压缩在一起，以“包装消息”（wrapper message）来发送，如下所示：

![img](http://dunwu.test.upcdn.net/snap/20200621134404.png)

如果生产者使用压缩功能，那么发送更大的批量消息可以得到更好的网络传输效率，并且节省磁盘存储空间。

### 索引

Kafka 允许消费者从任意有效的偏移量位置开始读取消息。Kafka 为每个 Partition 都维护了一个索引，该索引将偏移量映射到片段文件以及偏移量在文件里的位置。

索引也被分成片段，所以在删除消息时，也可以删除相应的索引。Kafka 不维护索引的校验和。如果索引出现损坏，Kafka 会通过重读消息并录制偏移量和位置来重新生成索引。

### 清理

每个日志片段可以分为以下两个部分：

- 干净的部分：这部分消息之前已经被清理过，每个键只存在一个值。
- 污浊的部分：在上一次清理后写入的新消息。

![img](http://dunwu.test.upcdn.net/snap/20200621135557.png)

如果在 Kafka 启动时启用了清理功能（通过 log.cleaner.enabled 配置），每个 broker 会启动一个清理管理器线程和若干个清理线程，每个线程负责一个 Partition。

清理线程会读取污浊的部分，并在内存里创建一个 map。map 的 key 是消息键的哈希吗，value 是消息的偏移量。对于相同的键，只保留最新的位移。其中 key 的哈希大小为 16 字节，位移大小为 8 个字节。也就是说，一个映射只有 24 字节，假设消息大小为 1KB，那么 1GB 的段有 1 百万条消息，建立这个段的映射只需要 24MB 的内存，映射的内存效率是非常高效的。

在配置 Kafka 时，管理员需要设置这些清理线程可以使用的总内存。如果设置 1GB 的总内存同时有 5 个清理线程，那么每个线程只有 200MB 的内存可用。在清理线程工作时，它不需要把所有脏的段文件都一起在内存中建立上述映射，但需要保证至少能够建立一个段的映射。如果不能同时处理所有脏的段，Kafka 会一次清理最老的几个脏段，然后在下一次再处理其他的脏段。

一旦建立完脏段的键与位移的映射后，清理线程会从最老的干净的段开始处理。如果发现段中的消息的键没有在映射中出现，那么可以知道这个消息是最新的，然后简单的复制到一个新的干净的段中；否则如果消息的键在映射中出现，这条消息需要抛弃，因为对于这个键，已经有新的消息写入。处理完会将产生的新段替代原始段，并处理下一个段。

对于一个段，清理前后的效果如下：

![img](http://dunwu.test.upcdn.net/snap/20200621140117.png)

### 删除事件

对于只保留最新消息的清理策略来说，Kafka 还支持删除相应键的消息操作（而不仅仅是保留最新的消息内容）。这是通过生产者发送一条特殊的消息来实现的，该消息包含一个键以及一个 null 的消息内容。当清理线程发现这条消息时，它首先仍然进行一个正常的清理并且保留这个包含 null 的特殊消息一段时间，在这段时间内消费者消费者可以获取到这条消息并且知道消息内容已经被删除。过了这段时间，清理线程会删除这条消息，这个键会从 Partition 中消失。这段时间是必须的，因为它可以使得消费者有一定的时间余地来收到这条消息。

## 七、部署方案

### 操作系统

Kafka 由 Scala 语言和 Java 语言编写而成，编译之后的源代码就是普通的“.class”文件。本来部署到哪个操作系统应该都是一样的，但是不同操作系统的差异还是给 Kafka 集群带来了相当大的影响。

目前常见的操作系统有 3 种：Linux、Windows 和 macOS。应该说部署在 Linux 上的生产环境是最多的。主要是在下面这三个方面上，Linux 的表现更胜一筹。

- I/O 模型的使用
- 数据网络传输效率
- 社区支持度

**在 Linux 部署 Kafka 能够享受到零拷贝技术所带来的快速数据传输特性。**

### 磁盘

Kafka 大量使用磁盘不假，可它使用的方式多是顺序读写操作（通过追加的方式写文件），一定程度上规避了机械磁盘最大的劣势，即随机读写操作慢。

- 追求性价比的公司可以不搭建 RAID，使用普通磁盘组成存储空间即可。
- 使用机械磁盘完全能够胜任 Kafka 线上环境。

磁盘容量如何估算？

规划磁盘容量时需要考虑的元素：

- 新增消息数
- 消息留存时间
- 平均消息大小
- 备份数
- 是否启用压缩

每天 1 亿条 1KB 大小的消息，保存两份且留存两周的时间，那么总的空间大小就等于 1 亿 _ 1KB _ 2 / 1000 / 1000 = 200GB。一般情况下 Kafka 集群除了消息数据还有其他类型的数据，比如索引数据等，故我们再为这些数据预留出 10% 的磁盘空间，因此总的存储容量就是 220GB。既然要保存两周，那么整体容量即为 220GB _ 14，大约 3TB 左右。Kafka 支持数据的压缩，假设压缩比是 0.75，那么最后你需要规划的存储空间就是 0.75 _ 3 = 2.25TB。

### 带宽

普通的以太网络，带宽也主要有两种：1Gbps 的千兆网络和 10Gbps 的万兆网络。

通常情况下只能假设 Kafka 会用到 70% 的带宽资源，因为总要为其他应用或进程留一些资源。根据实际使用经验，超过 70% 的阈值就有网络丢包的可能性了，故 70% 的设定是一个比较合理的值，也就是说单台 Kafka 服务器最多也就能使用大约 700Mb 的带宽资源。

通常要再额外预留出 2/3 的资源，即单台服务器使用带宽 700Mb / 3 ≈ 240Mbps。可以计算 1 小时内处理 1TB 数据所需的服务器数量了。根据这个目标，我们每秒需要处理 2336Mb 的数据，除以 240，约等于 10 台服务器。如果消息还需要额外复制两份，那么总的服务器台数还要乘以 3，即 30 台。

## 参考资料

- **官方**
  - [Kakfa 官网](http://kafka.apache.org/)
  - [Kakfa Github](https://github.com/apache/kafka)
  - [Kakfa 官方文档](https://kafka.apache.org/documentation/)
- **书籍**
  - [《Kafka 权威指南》](https://item.jd.com/12270295.html)
- **教程**
  - [Kafka 中文文档](https://github.com/apachecn/kafka-doc-zh)
  - [Kafka 核心技术与实战](https://time.geekbang.org/column/intro/100029201)
# Kafka 运维指南

> 环境要求：
>
> - JDK8
> - ZooKeeper

<!-- TOC depthFrom:2 depthTo:3 -->

- [一、Kafka 单点部署](#一kafka-单点部署)
  - [下载解压](#下载解压)
  - [启动服务器](#启动服务器)
  - [停止服务器](#停止服务器)
- [二、Kafka 集群部署](#二kafka-集群部署)
  - [修改配置](#修改配置)
  - [启动](#启动)
- [三、Kafka 命令](#三kafka-命令)
  - [主题（Topic）](#主题topic)
  - [生产者（Producers）](#生产者producers)
  - [消费者（Consumers）](#消费者consumers)
  - [配置（Config）](#配置config)
  - [ACL](#acl)
  - [ZooKeeper](#zookeeper)
- [四、Kakfa 工具](#四kakfa-工具)
- [五、Kafka 核心配置](#五kafka-核心配置)
  - [Broker 级别配置](#broker-级别配置)
  - [Topic 级别配置](#topic-级别配置)
  - [操作系统参数](#操作系统参数)
- [参考资料](#参考资料)

<!-- /TOC -->

## 一、Kafka 单点部署

### 下载解压

进入官方下载地址：<http://kafka.apache.org/downloads，选择合适版本。>

解压到本地：

```shell
tar -xzf kafka_2.11-1.1.0.tgz
cd kafka_2.11-1.1.0
```

现在您已经在您的机器上下载了最新版本的 Kafka。

### 启动服务器

由于 Kafka 依赖于 ZooKeeper，所以运行前需要先启动 ZooKeeper

```shell
$ bin/zookeeper-server-start.sh config/zookeeper.properties
[2013-04-22 15:01:37,495] INFO Reading configuration from: config/zookeeper.properties (org.apache.zookeeper.server.quorum.QuorumPeerConfig)
...
```

然后，启动 Kafka

```shell
$ bin/kafka-server-start.sh config/server.properties
[2013-04-22 15:01:47,028] INFO Verifying properties (kafka.utils.VerifiableProperties)
[2013-04-22 15:01:47,051] INFO Property socket.send.buffer.bytes is overridden to 1048576 (kafka.utils.VerifiableProperties)
...
```

### 停止服务器

执行所有操作后，可以使用以下命令停止服务器

```shell
bin/kafka-server-stop.sh config/server.properties
```

## 二、Kafka 集群部署

### 修改配置

复制配置为多份（Windows 使用 copy 命令代理）：

```shell
cp config/server.properties config/server-1.properties
cp config/server.properties config/server-2.properties
```

修改配置：

```properties
config/server-1.properties:
broker.id=1
listeners=PLAINTEXT://:9093
log.dir=/tmp/kafka-logs-1

config/server-2.properties:
broker.id=2
listeners=PLAINTEXT://:9094
log.dir=/tmp/kafka-logs-2
```

其中，broker.id 这个参数必须是唯一的。

端口故意配置的不一致，是为了可以在一台机器启动多个应用节点。

### 启动

根据这两份配置启动三个服务器节点：

```shell
$ bin/kafka-server-start.sh config/server.properties &
...
$ bin/kafka-server-start.sh config/server-1.properties &
...
$ bin/kafka-server-start.sh config/server-2.properties &
...
```

创建一个新的 Topic 使用 三个备份：
```shell
bin/kafka-topics.sh --create --zookeeper localhost:2181 --replication-factor 3 --partitions 1 --topic my-replicated-topic
```

查看主题：

```shell
$ bin/kafka-topics.sh --describe --zookeeper localhost:2181 --topic my-replicated-topic
Topic:my-replicated-topic   PartitionCount:1    ReplicationFactor:3 Configs:
    Topic: my-replicated-topic  Partition: 0    Leader: 1   Replicas: 1,2,0 Isr: 1,2,0
```

- leader - 负责指定分区的所有读取和写入的节点。每个节点将成为随机选择的分区部分的领导者。
- replicas - 是复制此分区日志的节点列表，无论它们是否为领导者，或者即使它们当前处于活动状态。
- isr - 是“同步”复制品的集合。这是副本列表的子集，该列表当前处于活跃状态并且已经被领导者捕获。

## 三、Kafka 命令

### 主题（Topic）

#### 创建 Topic

```shell
kafka-topics --create --zookeeper localhost:2181 --replication-factor 1 --partitions 3 --topic my-topic
```

#### 查看 Topic 列表

```shell
kafka-topics --list --zookeeper localhost:2181
```

#### 添加 Partition

```shell
kafka-topics --zookeeper localhost:2181 --alter --topic my-topic --partitions 16
```

#### 删除 Topic

```shell
kafka-topics --zookeeper localhost:2181 --delete --topic my-topic
```

#### 查看 Topic 详细信息

```shell
kafka-topics --zookeeper localhost:2181/kafka-cluster --describe
```

#### 查看备份分区

```shell
kafka-topics --zookeeper localhost:2181/kafka-cluster --describe --under-replicated-partitions
```

### 生产者（Producers）

#### 通过控制台输入生产消息

```shell
kafka-console-producer --broker-list localhost:9092 --topic my-topic
```

#### 通过文件输入生产消息

```shell
kafka-console-producer --broker-list localhost:9092 --topic test < messages.txt
```

#### 通过控制台输入 Avro 生产消息

```shell
kafka-avro-console-producer --broker-list localhost:9092 --topic my.Topic --property value.schema='{"type":"record","name":"myrecord","fields":[{"name":"f1","type":"string"}]}' --property schema.registry.url=http://localhost:8081
```

然后，可以选择输入部分 json key：

```json
{ "f1": "value1" }
```

#### 生成消息性能测试

```shell
kafka-producer-perf-test --topic position-reports --throughput 10000 --record-size 300 --num-records 20000 --producer-props bootstrap.servers="localhost:9092"
```

### 消费者（Consumers）

#### 消费所有未消费的消息

```shell
kafka-console-consumer --bootstrap-server localhost:9092 --topic my-topic --from-beginning
```

#### 消费一条消息

```shell
kafka-console-consumer --bootstrap-server localhost:9092 --topic my-topic  --max-messages 1
```

#### 从指定的 offset 消费一条消息

从指定的 offset `__consumer_offsets` 消费一条消息：

```shell
kafka-console-consumer --bootstrap-server localhost:9092 --topic __consumer_offsets --formatter 'kafka.coordinator.GroupMetadataManager$OffsetsMessageFormatter' --max-messages 1
```

#### 从指定 Group 消费消息

```shell
kafka-console-consumer --topic my-topic --new-consumer --bootstrap-server localhost:9092 --consumer-property group.id=my-group
```

#### 消费 avro 消息

```shell
kafka-avro-console-consumer --topic position-reports --new-consumer --bootstrap-server localhost:9092 --from-beginning --property schema.registry.url=localhost:8081 --max-messages 10
```

```shell
kafka-avro-console-consumer --topic position-reports --new-consumer --bootstrap-server localhost:8092 --from-beginning --property schema.registry.url=localhost:8081
```

#### 查看消费者 Group 列表

```shell
kafka-consumer-groups --new-consumer --list --bootstrap-server localhost:9092
```

#### 查看消费者 Group 详细信息

```shell
kafka-consumer-groups --bootstrap-server localhost:9092 --describe --group testgroup
```

### 配置（Config）

#### 设置 Topic 的保留时间

```shell
kafka-configs --zookeeper localhost:2181 --alter --entity-type topics --entity-name my-topic --add-config retention.ms=3600000
```

#### 查看 Topic 的所有配置

```shell
kafka-configs --zookeeper localhost:2181 --describe --entity-type topics --entity-name my-topic
```

#### 修改 Topic 的配置

```shell
kafka-configs --zookeeper localhost:2181 --alter --entity-type topics --entity-name my-topic --delete-config retention.ms
```

### ACL

#### 查看指定 Topic 的 ACL

```shell
kafka-acls --authorizer-properties zookeeper.connect=localhost:2181 --list --topic topicA
```

#### 添加 ACL

```shell
kafka-acls --authorizer-properties zookeeper.connect=localhost:2181 --add --allow-principal User:Bob --consumer --topic topicA --group groupA
```

```shell
kafka-acls --authorizer-properties zookeeper.connect=localhost:2181 --add --allow-principal User:Bob --producer --topic topicA
```

### ZooKeeper

```shell
zookeeper-shell localhost:2182 ls /
```

## 四、Kakfa 工具

- **[kafka-manager](https://github.com/yahoo/kafka-manager)**
- **[KafkaOffsetMonitor](https://github.com/quantifind/KafkaOffsetMonitor)**

## 五、Kafka 核心配置

### Broker 级别配置

#### 存储配置

首先 Broker 是需要配置存储信息的，即 Broker 使用哪些磁盘。那么针对存储信息的重要参数有以下这么几个：

- `log.dirs`：这是非常重要的参数，指定了 Broker 需要使用的若干个文件目录路径。要知道这个参数是没有默认值的，这说明什么？这说明它必须由你亲自指定。
- `log.dir`：注意这是 dir，结尾没有 s，说明它只能表示单个路径，它是补充上一个参数用的。

`log.dirs` 具体格式是一个 CSV 格式，也就是用逗号分隔的多个路径，比如`/home/kafka1,/home/kafka2,/home/kafka3`这样。如果有条件的话你最好保证这些目录挂载到不同的物理磁盘上。这样做有两个好处：

- 提升读写性能：比起单块磁盘，多块物理磁盘同时读写数据有更高的吞吐量。
- 能够实现故障转移：即 Failover。这是 Kafka 1.1 版本新引入的强大功能。要知道在以前，只要 Kafka Broker 使用的任何一块磁盘挂掉了，整个 Broker 进程都会关闭。但是自 1.1 开始，这种情况被修正了，坏掉的磁盘上的数据会自动地转移到其他正常的磁盘上，而且 Broker 还能正常工作。

#### zookeeper 配置

Kafka 与 ZooKeeper 相关的最重要的参数当属`zookeeper.connect`。这也是一个 CSV 格式的参数，比如我可以指定它的值为`zk1:2181,zk2:2181,zk3:2181`。2181 是 ZooKeeper 的默认端口。

现在问题来了，如果我让多个 Kafka 集群使用同一套 ZooKeeper 集群，那么这个参数应该怎么设置呢？这时候 chroot 就派上用场了。这个 chroot 是 ZooKeeper 的概念，类似于别名。

如果你有两套 Kafka 集群，假设分别叫它们 kafka1 和 kafka2，那么两套集群的`zookeeper.connect`参数可以这样指定：`zk1:2181,zk2:2181,zk3:2181/kafka1`和`zk1:2181,zk2:2181,zk3:2181/kafka2`。切记 chroot 只需
要写一次，而且是加到最后的。我经常碰到有人这样指定：`zk1:2181/kafka1,zk2:2181/kafka2,zk3:2181/kafka3`，这样的格式是不对的。

#### Broker 连接配置

- `listeners`：告诉外部连接者要通过什么协议访问指定主机名和端口开放的 Kafka 服务。
- `advertised.listeners`：和 listeners 相比多了个 advertised。Advertised 的含义表示宣称的、公布的，就是说这组监听器是 Broker 用于对外发布的。
- `host.name/port`：列出这两个参数就是想说你把它们忘掉吧，压根不要为它们指定值，毕竟都是过期的参数了。

我们具体说说监听器的概念，从构成上来说，它是若干个逗号分隔的三元组，每个三元组的格式为`<协议名称，主机名，端口号>`。这里的协议名称可能是标准的名字，比如 PLAINTEXT 表示明文传输、SSL 表示使用 SSL 或 TLS 加密传输等；也可能是你自己定义的协议名字，比如`CONTROLLER: //localhost:9092`。

**最好全部使用主机名，即 Broker 端和 Client 端应用配置中全部填写主机名。**

#### Topic 管理

- `auto.create.topics.enable`：是否允许自动创建 Topic。
- `unclean.leader.election.enable`：是否允许 Unclean Leader 选举。
- `auto.leader.rebalance.enable`：是否允许定期进行 Leader 选举。

第二个参数`unclean.leader.election.enable`是关闭 Unclean Leader 选举的。何谓 Unclean？还记得 Kafka 有多个副本这件事吗？每个分区都有多个副本来提供高可用。在这些副本中只能有一个副本对外提供服务，即所谓的 Leader 副本。

那么问题来了，这些副本都有资格竞争 Leader 吗？显然不是，只有保存数据比较多的那些副本才有资格竞选，那些落后进度太多的副本没资格做这件事。

好了，现在出现这种情况了：假设那些保存数据比较多的副本都挂了怎么办？我们还要不要进行 Leader 选举了？此时这个参数就派上用场了。

如果设置成 false，那么就坚持之前的原则，坚决不能让那些落后太多的副本竞选 Leader。这样做的后果是这个分区就不可用了，因为没有 Leader 了。反之如果是 true，那么 Kafka 允许你从那些“跑得慢”的副本中选一个出来当 Leader。这样做的后果是数据有可能就丢失了，因为这些副本保存的数据本来就不全，当了 Leader 之后它本人就变得膨胀了，认为自己的数据才是权威的。

这个参数在最新版的 Kafka 中默认就是 false，本来不需要我特意提的，但是比较搞笑的是社区对这个参数的默认值来来回回改了好几版了，鉴于我不知道你用的是哪个版本的 Kafka，所以建议你还是显式地把它设置成 false 吧。

第三个参数`auto.leader.rebalance.enable`的影响貌似没什么人提，但其实对生产环境影响非常大。设置它的值为 true 表示允许 Kafka 定期地对一些 Topic 分区进行 Leader 重选举，当然这个重选举不是无脑进行的，它要满足一定的条件才会发生。严格来说它与上一个参数中 Leader 选举的最大不同在于，它不是选 Leader，而是换 Leader！比如 Leader A 一直表现得很好，但若`auto.leader.rebalance.enable=true`，那么有可能一段时间后 Leader A 就要被强行卸任换成 Leader B。

你要知道换一次 Leader 代价很高的，原本向 A 发送请求的所有客户端都要切换成向 B 发送请求，而且这种换 Leader 本质上没有任何性能收益，因此我建议你在生产环境中把这个参数设置成 false。

#### 数据留存

- `log.retention.{hour|minutes|ms}`：都是控制一条消息数据被保存多长时间。从优先级上来说 ms 设置最高、minutes 次之、hour 最低。通常情况下我们还是设置 hour 级别的多一些，比如`log.retention.hour=168`表示默认保存 7 天的数据，自动删除 7 天前的数据。很多公司把 Kafka 当做存储来使用，那么这个值就要相应地调大。
- `log.retention.bytes`：这是指定 Broker 为消息保存的总磁盘容量大小。这个值默认是 -1，表明你想在这台 Broker 上保存多少数据都可以，至少在容量方面 Broker 绝对为你开绿灯，不会做任何阻拦。这个参数真正发挥作用的场景其实是在云上构建多租户的 Kafka 集群：设想你要做一个云上的 Kafka 服务，每个租户只能使用 100GB 的磁盘空间，为了避免有个“恶意”租户使用过多的磁盘空间，设置这个参数就显得至关重要了。
- `message.max.bytes`：控制 Broker 能够接收的最大消息大小。默认的 1000012 太少了，还不到 1MB。实际场景中突破 1MB 的消息都是屡见不鲜的，因此在线上环境中设置一个比较大的值还是比较保险的做法。毕竟它只是一个标尺而已，仅仅衡量 Broker 能够处理的最大消息大小，即使设置大一点也不会耗费什么磁盘空间的。

### Topic 级别配置

- `retention.ms`：规定了该 Topic 消息被保存的时长。默认是 7 天，即该 Topic 只保存最近 7 天的消息。一旦设置了这个值，它会覆盖掉 Broker 端的全局参数值。
- `retention.bytes`：规定了要为该 Topic 预留多大的磁盘空间。和全局参数作用相似，这个值通常在多租户的 Kafka 集群中会有用武之地。当前默认值是 -1，表示可以无限使用磁盘空间。

### 操作系统参数

- 文件描述符限制
- 文件系统类型
- Swappiness
- 提交时间

文件描述符系统资源并不像我们想象的那样昂贵，你不用太担心调大此值会有什么不利的影响。通常情况下将它设置成一个超大的值是合理的做法，比如`ulimit -n 1000000`。其实设置这个参数一点都不重要，但不设置的话后果很严重，比如你会经常看到“Too many open files”的错误。

其次是文件系统类型的选择。这里所说的文件系统指的是如 ext3、ext4 或 XFS 这样的日志型文件系统。根据官网的测试报告，XFS 的性能要强于 ext4，所以生产环境最好还是使用 XFS。对了，最近有个 Kafka 使用 ZFS 的[数据报告](https://www.confluent.io/kafka-summit-sf18/kafka-on-zfs)，貌似性能更加强劲，有条件的话不妨一试。

第三是 swap 的调优。网上很多文章都提到设置其为 0，将 swap 完全禁掉以防止 Kafka 进程使用 swap 空间。我个人反倒觉得还是不要设置成 0 比较好，我们可以设置成一个较小的值。为什么呢？因为一旦设置成 0，当物理内存耗尽时，操作系统会触发 OOM killer 这个组件，它会随机挑选一个进程然后 kill 掉，即根本不给用户任何的预警。但如果设置成一个比较小的值，当开始使用 swap 空间时，你至少能够观测到 Broker 性能开始出现急剧下降，从而给你进一步调优和诊断问题的时间。基于这个考虑，我个人建议将 swappniess 配置成一个接近 0 但不为 0 的值，比如 1。

最后是提交时间或者说是 Flush 落盘时间。向 Kafka 发送数据并不是真要等数据被写入磁盘才会认为成功，而是只要数据被写入到操作系统的页缓存（Page Cache）上就可以了，随后操作系统根据 LRU 算法会定期将页缓存上的“脏”数据落盘到物理磁盘上。这个定期就是由提交时间来确定的，默认是 5 秒。一般情况下我们会认为这个时间太频繁了，可以适当地增加提交间隔来降低物理磁盘的写操作。当然你可能会有这样的疑问：如果在页缓存中的数据在写入到磁盘前机器宕机了，那岂不是数据就丢失了。的确，这种情况数据确实就丢失了，但鉴于 Kafka 在软件层面已经提供了多副本的冗余机制，因此这里稍微拉大提交间隔去换取性能还是一个合理的做法。

## 参考资料

- **官方**
  - [Kakfa 官网](http://kafka.apache.org/)
  - [Kakfa Github](https://github.com/apache/kafka)
  - [Kakfa 官方文档](https://kafka.apache.org/documentation/)
- **书籍**
  - [《Kafka 权威指南》](https://item.jd.com/12270295.html)
- **教程**
  - [Kafka 中文文档](https://github.com/apachecn/kafka-doc-zh)
  - [Kafka 核心技术与实战](https://time.geekbang.org/column/intro/100029201)


# Kafka 可靠的数据传递

<!-- TOC depthFrom:2 depthTo:3 -->

- [一、可靠性保证](#一可靠性保证)
- [二、复制](#二复制)
- [三、Broker 的可靠性](#三broker-的可靠性)
  - [复制系数](#复制系数)
  - [不完全的选主](#不完全的选主)
  - [最少同步副本](#最少同步副本)
- [四、生产者的可靠性](#四生产者的可靠性)
  - [ACK](#ack)
  - [重试](#重试)
  - [错误处理](#错误处理)
- [五、消费者的可靠性](#五消费者的可靠性)
  - [消费者的可靠性配置](#消费者的可靠性配置)
  - [显示提交偏移量](#显示提交偏移量)
- [六、验证系统可靠性](#六验证系统可靠性)
- [参考资料](#参考资料)

<!-- /TOC -->

## 一、可靠性保证

Kafka 到底在什么情况下才能保证消息不丢失呢？

一句话概括，**Kafka 只对“已提交”的消息（committed message）做有限度的持久化保证**。

Kafka 的可靠性保证：

- Kafka **可以保证分区消息的顺序**。
- **只有当消息被写入分区的若干同步副本时，才被认为是已提交的**。为什么是若干个 Broker 呢？这取决于你对“已提交”的定义。你可以选择只要 Leader 成功保存该消息就算是已提交，也可以是令所有 Broker 都成功保存该消息才算是已提交。
- **只要还有一个副本是存活的，那么已提交的消息就不会丢失**。
- **消费者只能读取已提交的消息**。

## 二、复制

kafka 的复制机制和分区的多副本架构是 kafka 可靠性保证的核心。

Kafka 的主题被分为多个分区，分区时基本的数据块。每个分区可以有多个副本，其中一个是首领。所有事件都直接发送给主副本，或者直接从主副本读取事件。其他副本只需要与首领保持同步，并即时复制最新的事件。当主副本不可用时，其中一个同步副本将成为新的主副本。

## 三、Broker 的可靠性

broker 有 3 个配置参数会影响 Kafka 消息存储的可靠性。

### 复制系数

**`replication.factor` 的作用是设置每个分区的副本数**。`replication.factor` 是主题级别配置； `default.replication.factor` 是 broker 级别配置。

副本数越多，数据可靠性越高；但由于副本数增多，也会增加同步副本的开销，可能会降低集群的可用性。一般，建议设为 3，这也是 Kafka 的默认值。

### 不完全的选主

`unclean.leader.election.enable` 是 broker 级别（实际上是集群范围内）配置，默认值为 true。

- 如果设为 true，代表着**允许不同步的副本成为主副本**（即不完全的选举），那么将**面临丢失消息的风险**；
- 如果设为 false，就要**等待原先的主副本重新上线**，从而降低了可用性。

### 最少同步副本

**`min.insync.replicas` 控制的是消息至少要被写入到多少个副本才算是“已提交”**。`min.insync.replicas` 是主题级别和 broker 级别配置。

尽管可以为一个主题配置 3 个副本，但还是可能会出现只有一个同步副本的情况。如果这个同步副本变为不可用，则必须在可用性和数据一致性之间做出选择。Kafka 中，消息只有被写入到所有的同步副本之后才被认为是已提交的。但如果只有一个同步副本，那么在这个副本不可用时，则数据就会丢失。

如果要确保已经提交的数据被已写入不止一个副本，就需要把最小同步副本的设置为大一点的值。

> 注意：要确保 `replication.factor` > `min.insync.replicas`。如果两者相等，那么只要有一个副本挂机，整个分区就无法正常工作了。我们不仅要改善消息的持久性，防止数据丢失，还要在不降低可用性的基础上完成。推荐设置成 `replication.factor = min.insync.replicas + 1`。

## 四、生产者的可靠性

[Kafka 生产者](kafka-producer.md) 中提到了，Kafka 有三种发送方式：同步、异步、异步回调。

如果使用异步方式发送消息，通常会立即返回，但消息可能丢失。

解决生产者丢失消息：

Producer 使用异步回调方式 `producer.send(msg, callback)` 发送消息。callback（回调）能准确地告诉你消息是否真的提交成功了。一旦出现消息提交失败的情况，你就可以有针对性地进行处理。

- 如果是因为那些瞬时错误，那么仅仅让 Producer 重试就可以了；
- 如果是消息不合格造成的，那么可以调整消息格式后再次发送。

然后，需要基于以下几点来保证 Kafka 生产者的可靠性：

### ACK

生产者可选的确认模式有三种：`acks=0`、`acks=1`、`acks=all`。

`acks=0`、`acks=1` 都有丢失数据的风险。

`acks=all` 意味着会等待所有同步副本都收到消息。再结合 `min.insync.replicas` ，就可以决定在得到确认响应前，至少有多少副本能够收到消息。

这是最保险的做法，但也会降低吞吐量。

### 重试

如果 broker 返回的错误可以通过**重试**来解决，生产者会自动处理这些错误。

- **可重试错误**，如：`LEADER_NOT_AVAILABLE`，主副本不可用，可能过一段时间，集群就会选举出新的主副本，重试可以解决问题。
- **不可重试错误**，如：`INVALID_CONFIG`，即使重试，也无法改变配置选项，重试没有意义。

需要注意的是：有时可能因为网络问题导致没有收到确认，但实际上消息已经写入成功。生产者会认为出现临时故障，重试发送消息，这样就会出现重复记录。所以，尽可能在业务上保证幂等性。

设置 `retries` 为一个较大的值。这里的 `retries` 同样是 Producer 的参数，对应前面提到的 Producer 自动重试。当出现网络的瞬时抖动时，消息发送可能会失败，此时配置了 retries > 0 的 Producer 能够自动重试消息发送，避免消息丢失。

### 错误处理

开发者需要自行处理的错误：

- 不可重试的 broker 错误，如消息大小错误、认证错误等；
- 消息发送前发生的错误，如序列化错误；
- 生产者达到重试次数上限或消息占用的内存达到上限时发生的错误。

## 五、消费者的可靠性

只有被写入所有同步副本的消息，对消费者才是可用的，这就保证了消费者接收到消息时已经具备了数据一致性。

**消费者唯一要做的是确保哪些消息是已经读取过的，哪些是没有读取过的（通过提交的偏移量来判断）**。

如果消费者提交了偏移量却未能处理完消息，那么就有可能造成消息丢失，这也是消费者丢失消息的主要原因。

![img](http://dunwu.test.upcdn.net/snap/20200727140159.png)

### 消费者的可靠性配置

- `group.id` - 如果希望消费者可以看到主题的所有消息，那么需要为它们设置唯一的 `group.id`。
- `auto.offset.reset` - 有两个选项：
  - `earliest` - 消费者会从分区的开始位置读取数据
  - `latest` - 消费者会从分区末尾位置读取数据
- `enable.auto.commit` - 消费者自动提交偏移量。如果设为 true，处理流程更简单，但无法保证重复处理消息。
- `auto.commit.interval.ms` - 自动提交的频率，默认为每 5 秒提交一次。

### 显示提交偏移量

> 如果 `enable.auto.commit` 设为 true，即自动提交，就无需考虑提交偏移量的问题。

如果选择显示提交偏移量，需要考虑以下问题：

- 总是在处理完事件后再提交偏移量
- 提交频率是性能和重复消息数之间的权衡
- 确保对提交的偏移量心中有数
- 再均衡
- 消费者可能需要重试
- 消费者可能需要维护状态
- 长时间处理
- 幂等性设计

## 六、验证系统可靠性

建议从 3 个层面验证系统的可靠性：

- **配置验证**
- **应用验证**
  - 客户端和服务器断开连接
  - 选举
  - 依次重启 broker
  - 依次重启生产者
  - 依次重启消费者
- **监控可靠性**
  - 对于生产者来说，最重要的两个指标是消息的 `error-rate` 和 `retry-rate`。如果这两个指标上升，说明系统出了问题。
  - 对于消费者来说，最重要的指标是 `consumer-lag`，该指标表明了消费者的处理速度与最近提交到分区里的偏移量之间还有多少差距。

## 参考资料

- **官方**
  - [Kakfa 官网](http://kafka.apache.org/)
  - [Kakfa Github](https://github.com/apache/kafka)
  - [Kakfa 官方文档](https://kafka.apache.org/documentation/)
- **书籍**
  - [《Kafka 权威指南》](https://item.jd.com/12270295.html)
- **教程**
  - [Kafka 中文文档](https://github.com/apachecn/kafka-doc-zh)
  - [Kafka 核心技术与实战](https://time.geekbang.org/column/intro/100029201)

# Kafka 分区再均衡

<!-- TOC depthFrom:2 depthTo:3 -->

- [一、什么是 Rebalance](#一什么是-rebalance)
- [二、Rebalance 的触发时机](#二rebalance-的触发时机)
- [三、Rebalance 的过程](#三rebalance-的过程)
  - [查找协调者](#查找协调者)
- [四、Rebalance 的问题](#四rebalance-的问题)
- [五、避免 Rebalance](#五避免-rebalance)
  - [未及时发送心跳](#未及时发送心跳)
  - [Consumer 消费时间过长](#consumer-消费时间过长)
- [六、分区再均衡的应用](#六分区再均衡的应用)
- [参考资料](#参考资料)

<!-- /TOC -->

## 一、什么是 Rebalance

**分区的所有权从一个消费者转移到另一个消费者，这样的行为被称为分区再均衡（Rebalance）。**

**Rebalance 实现了消费者群组的高可用性和伸缩性**。

**消费者通过向被指派为群组协调器（Coordinator）的 broker 发送心跳来维持它们和群组的从属关系以及它们对分区的所有权**。

所谓协调者，在 Kafka 中对应的术语是 Coordinator，它专门为 Consumer Group 服务，负责为 Group 执行 Rebalance 以及提供位移管理和组成员管理等。具体来讲，Consumer 端应用程序在提交位移时，其实是向 Coordinator 所在的 Broker 提交位移。同样地，当 Consumer 应用启动时，也是向 Coordinator 所在的 Broker 发送各种请求，然后由 Coordinator 负责执行消费者组的注册、成员管理记录等元数据管理操作。

当在群组里面 新增/移除消费者 或者 新增/移除 kafka 集群 broker 节点 时，群组协调器 Broker 会触发再均衡，重新为每一个 Partition 分配消费者。**Rebalance 期间，消费者无法读取消息，造成整个消费者群组一小段时间的不可用。**

**Rebalance 本质上是一种协议，规定了一个 Consumer Group 下的所有 Consumer 如何达成一致，来分配订阅 Topic 的每个分区**。比如某个 Group 下有 20 个 Consumer 实例，它订阅了一个具有 100 个分区的 Topic。正常情况下，Kafka 平均会为每个 Consumer 分配 5 个分区。这个分配的过程就叫 Rebalance。

## 二、Rebalance 的触发时机

- **组成员数发生变更**。比如有新的 Consumer 实例加入组或者离开组，抑或是有 Consumer 实例崩溃被“踢出”组。
  - 新增消费者。customer 订阅主题之后，第一次执行 poll 方法
  - 移除消费者。执行 customer.close()操作或者消费客户端宕机，就不再通过 poll 向群组协调器发送心跳了，当群组协调器检测次消费者没有心跳，就会触发再均衡。
- **订阅主题数发生变更**。Consumer Group 可以使用正则表达式的方式订阅主题，比如 `consumer.subscribe(Pattern.compile(“t.*c”))` 就表明该 Group 订阅所有以字母 t 开头、字母 c 结尾的主题。在 Consumer Group 的运行过程中，你新创建了一个满足这样条件的主题，那么该 Group 就会发生 Rebalance。
- **订阅主题的分区数发生变更**。Kafka 当前只能允许增加一个主题的分区数。当分区数增加时，就会触发订阅该主题的所有 Group 开启 Rebalance。
  - 新增 broker。如重启 broker 节点
  - 移除 broker。如 kill 掉 broker 节点。

## 三、Rebalance 的过程

**Rebalance 是通过消费者群组中的称为“群主”消费者客户端进行的**。什么是群主呢？“群主”就是第一个加入群组的消费者。消费者第一次加入群组时，它会向群组协调器发送一个 JoinGroup 的请求，如果是第一个，则此消费者被指定为“群主”（群主是不是和 qq 群很想啊，就是那个第一个进群的人）。

![img](http://dunwu.test.upcdn.net/snap/20200727153700.png)

1. 群主从群组协调器获取群组成员列表，然后给每一个消费者进行分配分区 Partition。有两种分配策略：Range 和 RoundRobin。
   - **Range 策略**，就是把若干个连续的分区分配给消费者，如存在分区 1-5，假设有 3 个消费者，则消费者 1 负责分区 1-2,消费者 2 负责分区 3-4，消费者 3 负责分区 5。
   - **RoundRoin 策略**，就是把所有分区逐个分给消费者，如存在分区 1->消费 1，分区 2->消费者 2，分区 3>消费者 3，分区 4>消费者 1，分区 5->消费者 2。
2. 群主分配完成之后，把分配情况发送给群组协调器。
3. 群组协调器再把这些信息发送给消费者。**每一个消费者只能看到自己的分配信息，只有群主知道所有消费者的分配信息**。

### 查找协调者

所有 Broker 在启动时，都会创建和开启相应的 Coordinator 组件。也就是说，**所有 Broker 都有各自的 Coordinator 组件**。那么，Consumer Group 如何确定为它服务的 Coordinator 在哪台 Broker 上呢？答案就在我们之前说过的 Kafka 内部位移主题 `__consumer_offsets` 身上。

目前，Kafka 为某个 Consumer Group 确定 Coordinator 所在的 Broker 的算法有 2 个步骤。

1. 第 1 步：确定由位移主题的哪个分区来保存该 Group 数据：`partitionId=Math.abs(groupId.hashCode() % offsetsTopicPartitionCount)`。

2. 第 2 步：找出该分区 Leader 副本所在的 Broker，该 Broker 即为对应的 Coordinator。

## 四、Rebalance 的问题

- 首先，**在 Rebalance 过程中，所有 Consumer 实例都会停止消费，等待 Rebalance 完成**。
- 其次，**目前 Rebalance 的设计是所有 Consumer 实例共同参与，全部重新分配所有分区**。其实更高效的做法是尽量减少分配方案的变动。例如实例 A 之前负责消费分区 1、2、3，那么 Rebalance 之后，如果可能的话，最好还是让实例 A 继续消费分区 1、2、3，而不是被重新分配其他的分区。这样的话，实例 A 连接这些分区所在 Broker 的 TCP 连接就可以继续用，不用重新创建连接其他 Broker 的 Socket 资源。
- 最后，**Rebalance 实在太慢了**。曾经，有个国外用户的 Group 内有几百个 Consumer 实例，成功 Rebalance 一次要几个小时！这完全是不能忍受的。所谓“本事大不如不摊上”，也许最好的解决方案就是避免 Rebalance 的发生吧。

Rebalance 整个过程中，所有实例都不能消费任何消息，因此它对 Consumer 的 TPS 影响很大。

## 五、避免 Rebalance

了解了 Rebalance 的问题，我们可以知道，如果减少 Rebalance，可以整体提高 Consumer 的 TPS。

前面介绍了，Rebalance 的触发时机有三个。其中，增加 Consumer 实例的操作都是计划内的，可能是出于增加 TPS 或提高伸缩性的需要。

### 未及时发送心跳

**第一类非必要 Rebalance 是因为未能及时发送心跳，导致 Consumer 被“踢出”Group 而引发的**。因此，你需要仔细地设置 **`session.timeout.ms` 和 `heartbeat.interval.ms`**的值。我在这里给出一些推荐数值，你可以“无脑”地应用在你的生产环境中。

- 设置 `session.timeout.ms` = 6s。
- 设置 `heartbeat.interval.ms` = 2s。
- 要保证 Consumer 实例在被判定为“dead”之前，能够发送至少 3 轮的心跳请求，即 `session.timeout.ms >= 3 * heartbeat.interval.ms`。

将 `session.timeout.ms` 设置成 6s 主要是为了让 Coordinator 能够更快地定位已经挂掉的 Consumer。毕竟，我们还是希望能尽快揪出那些“尸位素餐”的 Consumer，早日把它们踢出 Group。希望这份配置能够较好地帮助你规避第一类“不必要”的 Rebalance。

### Consumer 消费时间过长

**第二类非必要 Rebalance 是 Consumer 消费时间过长导致的**。我之前有一个客户，在他们的场景中，Consumer 消费数据时需要将消息处理之后写入到 MongoDB。显然，这是一个很重的消费逻辑。MongoDB 的一丁点不稳定都会导致 Consumer 程序消费时长的增加。此时，**`max.poll.interval.ms`** 参数值的设置显得尤为关键。如果要避免非预期的 Rebalance，你最好将该参数值设置得大一点，比你的下游最大处理时间稍长一点。就拿 MongoDB 这个例子来说，如果写 MongoDB 的最长时间是 7 分钟，那么你可以将该参数设置为 8 分钟左右。

如果你按照上面的推荐数值恰当地设置了这几个参数，却发现还是出现了 Rebalance，那么我建议你去排查一下**Consumer 端的 GC 表现**，比如是否出现了频繁的 Full GC 导致的长时间停顿，从而引发了 Rebalance。为什么特意说 GC？那是因为在实际场景中，我见过太多因为 GC 设置不合理导致程序频发 Full GC 而引发的非预期 Rebalance 了。

## 六、分区再均衡的应用

如果 Kafka 触发了再均衡，我们需要在消费者失去对一个分区的所有权之前提交最后一个已处理记录的偏移量。如果消费者准备了一个缓冲区用于处理偶发的事件，那么在失去分区所有权之前，需要处理在缓冲区累积下来的记录。可能还需要关闭文件句柄、数据库连接等。

在为消费者分配新分区或移除旧分区时，可以通过消费者 API 执行一些应用程序代码，在调用 `subscribe()` 方法时传进去一个 `ConsumerRebalanceListener` 实例就可以了。 `ConsumerRebalanceListener` 有两个需要实现的方法。

- `public void onPartitionsRevoked(Collection partitions)` 方法会在再均衡开始之前和消费者停止读取消息之后被调用。如果在这里提交偏移量，下一个接管分区的消费者就知道该从哪里开始读取了。
- `public void onPartitionsAssigned(Collection partitions)` 方法会在重新分配分区之后和消费者开始读取消息之前被调用。

```java
private Map<TopicPartition, OffsetAndMetadata> currentOffsets=
  new HashMap<>();

private class HandleRebalance implements ConsumerRebalanceListener {
    public void onPartitionsAssigned(Collection<TopicPartition>
      partitions) {
    }

    public void onPartitionsRevoked(Collection<TopicPartition>
      partitions) {
        System.out.println("Lost partitions in rebalance.
          Committing current
        offsets:" + currentOffsets);
        consumer.commitSync(currentOffsets);
    }
}

try {
    consumer.subscribe(topics, new HandleRebalance());

    while (true) {
        ConsumerRecords<String, String> records =
          consumer.poll(100);
        for (ConsumerRecord<String, String> record : records)
        {
            System.out.printf("topic = %s, partition = %s, offset = %d,
             customer = %s, country = %s\n",
             record.topic(), record.partition(), record.offset(),
             record.key(), record.value());
             currentOffsets.put(new TopicPartition(record.topic(),
             record.partition()), new
             OffsetAndMetadata(record.offset()+1, "no metadata"));
        }
        consumer.commitAsync(currentOffsets, null);
    }
} catch (WakeupException e) {
    // 忽略异常，正在关闭消费者
} catch (Exception e) {
    log.error("Unexpected error", e);
} finally {
    try {
        consumer.commitSync(currentOffsets);
    } finally {
        consumer.close();
        System.out.println("Closed consumer and we are done");
    }
}
```

## 参考资料

- **官方**
  - [Kakfa 官网](http://kafka.apache.org/)
  - [Kakfa Github](https://github.com/apache/kafka)
  - [Kakfa 官方文档](https://kafka.apache.org/documentation/)
- **书籍**
  - [《Kafka 权威指南》](https://item.jd.com/12270295.html)
- **教程**
  - [Kafka 中文文档](https://github.com/apachecn/kafka-doc-zh)
  - [Kafka 核心技术与实战](https://time.geekbang.org/column/intro/100029201)
- **文章**
  - [Kafka 设计解析（七）：流式计算的新贵 Kafka Stream](https://www.infoq.cn/article/kafka-analysis-part-7)
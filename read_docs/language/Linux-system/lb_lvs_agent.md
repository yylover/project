1. 一台机器只能提供一个LVS服务，只能有一个VIP么？
2. 三种方式都有hash路由么?根据ip进行路由
3. DR和IPTUN方式的源IP是VIP么？(是，但是需要RS节点服务器需要在本地回环接口配置VIP；DR:本地的回环借口上面配置VIP。另：由于网络接口都会进行ARP广播响应，但集群的其他机器都有这个VIP的lo接口，都响应就会冲突。所以我们需要把真实服务器的lo接口的ARP响应关闭掉。）然后真实服务器做成请求响应，之后根据自己的路由信息将这个响应数据包发送回给客户，并且源IP地址还是VIP。
4. )


### DNS
1. 动静分离:动、静对于服务器的要求是不一样的，动要求计算性能，静强调并发IO处理能力。
2. 组件分离：浏览器下载一个网页已经页面中的多个组件时，采用多线程并发下载方式，但是同一个URL的并发数是有最大限制的。
3. WEB DB 不要放到一个机器上。

### 反向代理(将缓存建立在反向代理上)

主流反向代理软件:
Nginx:反向代理是其中一个模块，功能仍在完善中。
Squid:专注代理多年，能胜任各种模式，很重。
Varnish:专注于反向代理，轻量级，稳定。


### 利用http重定向301/302实例负载均衡，多用于下载场景GSLB

### 利用DNS实现负载均衡
    CNAME,A记录结合、QDNS
### LVS
三种模式:DNAT,DR,隧道


## LVS

LVS：linux virtual server，linux虚拟服务器，通过LVS 提供的负载均衡技术实现高性能、高可用的服务器集群。

### LVS体系结构:
    一个机器只能提供一个LVS服务么？
最前端的负载层，中间的服务器集群Server Array,最后段的数据共享存储层:Shared Storage,用户看来，所有的内部应用都是透明的，用户只是在使用一个虚拟服务器提供的高性能服务。

> 包含三种方式:
> NAT: 网络地址转换
> IP Tunneling: IP隧道
> Direct Routing: 直接路由
> 不同的转发模式决定不同的Cluster网络结构。

### NAT

调度器，将请求包的IP地址和端口号改成real server的， 然后将报警请求发送到Real server,返回数据时，需要经过调度器将报文的源地址和源端口修改，然后返回给用户。

这样请求和响应都经过Directror Server,调度器的处理能力可能成为瓶颈。

### VS/Tun(Virtual Server via IP tunneling)
连接调度和管理与VS/NAT方式一样，只是报文转发方法不同。通过IP隧道直接将请求包转发给RealServer,响应包不再经过调度器。

### VS/DR(Virtual Server Via Direct Routing)
VS/DR通过改写请求报文的MAC地址，将请求发送到Real Server，而Real Server将响应直接返回给客户，免去了VS/TUN中的IP隧道开销。

性能最高，但是要求Director Server 和Real Server在同一个网段。

返回的响应包源IP是VIP


### 负载调度算法

LVS实现了八种调度算法，常用有四种:
#### :轮叫:
1:1调度，按顺序1:1分配到集群中每个RealServer上，
#### 加权轮叫
根据不同的处理能力来调度。为每个Real Server设置不能的权值。

#### 最小连接调度。
将网络请求调度到已建立的连接数最小的服务器上。

#### 加权最小连接调度。


## 反向代理和正向代理
正向代理代理的对象是客户端，反向代理代理的对象是服务端



### nginx 反向代理流程

请求包和响应包也都经过代理服务器。

#### 简单构建反向代理

location ~ /.php$ {
    proxy_pass   158.37.70.143:80 ;
}
#### 支持两台服务器

location ^~ /phpMyAdmin/ {
    proxy_pass   127.0.0.1:80 ;
}
location ~ /.php$ {
    proxy_pass   158.37.70.143:80 ;
}

#### 同一页面的负载
```
http module:
http {
    upstream myCluster {
        server 127.0.0.1:80 ;
        server 158.37.70.143:80 ;
    }    
}

//server module
server{
    location ~ /.php$ {
        proxy_pass  http://myCluster ; #这里的名字和上面的cluster的名字相同
        proxy_redirect     off;
        proxy_set_header   Host             $host;
        proxy_set_header   X-Real-IP        $remote_addr;
        proxy_set_header   X-Forwarded-For  $proxy_add_x_forwarded_for;
    }    
}

````

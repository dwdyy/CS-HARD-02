# Network Programming

下面写的全没写完,只是一些大概思路

## SOCKET

为了便于互联网进行通信,操作系统对计算机网络内部进行封装,提供一种接口,提供给程序使用,这就是套接字,可以把它看成通信的端点

`sockaddr_in` 是一个IPV4的套接字地址

```
struct sockaddr_in {
     short            sin_family;    // 2 字节 ，地址族，
     unsigned short   sin_port;      // 2 字节 ，端口号
     struct in_addr   sin_addr;      // 4 字节 ，IP地址
     char             sin_zero[8];   // 8 字节 ，填充用
};
```

为了使函数支持更多协议如IPV6,而不仅仅是一种协议,要对各种协议描述地址进行封装为一个sockaddr类型

```
struct sockaddr
{ 
　　unsigned short sa_family;//2字节 地址族
　　char sa_data[14]; //14字节 包含套接字中的目标地址和端口信息 
};
```

### 各种函数

`int socket(int domin,int type,int protocol)` 

​	创造一个套接字描述符,linux将其视为一个文件,返回的其实是一个文件描述符,出错返回-1

​	`domin` 地址族,使用什么类型

​	`type` 套接字类型,数据的传输方式

  - SOCK_STREAM 面向链接 双方使用前会建立可靠的链接

  - SOCK_DGRAM 直接发送

  `protocol ` 传输层协议,如果为0就会根据type默认设置,如果SOCK_STREAM就是TCP,如果SOCK_DGRAM 就是UDP,否则需要自己选

### connect

`int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)`

连接socket套接字，成功0失败-1

sockfd 客户端的套接字描述符

addr 服务器地址

addrlen 地址长度

如果链接成功,客户端的socket会自动绑定上一个本地地址和随机端口以及服务器地址和端口

到这里客户端就已经成功了

### bind

`int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`

手动将socket绑定端口和connect参数相同

### listen

`int listen(int sockfd, int backlog);`

监听socket套接字,成功返回0失败返回-1

sockfd 是主动套接字,lisnten完后会转化成监听套接字

backlog 最多等待的连接数

### accpet

`int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);`：

接受连接请求

成功返回新套接字,这里套接字就会绑定上本地地址和客户端地址

sockfd 监听套接字

addr 这是返回值,返回客户端地址

addrlen 这是指定客户端地址长度

这里accept成功后监听的套接字并不会删除,而是继续监听

这里我想到了一个问题accept产生的新套接字会分配新端口吗,如果分配新端口的话,可能不会通过防火墙并且端口很快就用完了,所以应该是不会的,那么假设这个端口有很多已连接的描述符会知道传来的文件给谁吗

其实TCP协议确定一个连接是{源端口和ip目的地的端口和ip}尽管目的地的端口一样,操作系统会判断源端口与ip确定这是给谁的

### getaddrinfo

当我们如果想使用域名的时候,需要用到DNS解析域名成为ip地址

getaddrinfo 可以快速构造套接字并自动解析

```
#include <netdb.h>

int getaddrinfo(const char *host, 
                const char *service, 
                const struct addrinfo *hints, 
                struct addrinfo **res);

```

host 主机ip或者网址

service 服务(一般服务会默认端口比如http默认是80)或确定的端口

hints 我们想要的解析要求(比如我们只要IPv4)

res 解析完成后生成地addrinfo链表,因为一个域名DNS解析后可能会有多个ip和服务

接着我们可以访问链表来连接到服务器

```
struct addrinfo {
    int              ai_flags;     // 额外的标志
    int              ai_family;    // 地址族 (如 AF_INET 或 AF_INET6)
    int              ai_socktype;  // 套接字类型 (如 SOCK_STREAM 或 SOCK_DGRAM)
    int              ai_protocol;  // 协议 (如 IPPROTO_TCP)
    size_t           ai_addrlen;   // 地址长度
    struct sockaddr *ai_addr;      // 指向 sockaddr 结构的指针
    char           * ai_canonname; // 规范名称
    struct addrinfo *ai_next;      // 指向下一个 addrinfo 结构的指针
};
```

### 数据表示

在网络编程中,不同机器会用不同表示方法,比如低地址储存整数的最低值就是小端法，高地址储存整数的最低值就是大端法,为了在不同设备中实现通信,默认使用大端法

```
<arpa/inet.h>
// host to internet long/short
htonl(): 将一个 32 位整数从主机字节顺序转换为网络字节顺序（大端法）
htons(): 将一个 16 位整数从主机字节顺序转换为网络字节顺序（大端法）
ntohl(): 将一个 32 位整数从网络字节顺序转换为主机字节顺序
ntohs(): 将一个 16 位整数从网络字节顺序转换为主机字节顺序
```

```text
INADDR_ANY
```

```
int` `send( SOCKET s, ``const` `char` `FAR *buf, ``int` `len, ``int` `flags );
```

```
int` `send( SOCKET s, ``const` `char` `FAR *buf, ``int` `len, ``int` `flags );
```

```
int` `recv( SOCKET s, ``char` `FAR *buf, ``int` `len, ``int` `flags);
```

```
 6 /* 若成功，返回32位二进制的网络字节序地址；若出错，返回INADDR_NONE */
 7 in_addr_t inet_addr(const char *strptr);
```


### Part 1

```
// user 信息
struct user{
    char name[MAXLEN_NAME];
    char pwd[MAXLEN_PWD];
    char birth[8]; //xxxx/xx/xx
    uint age ; // 年龄
    uint gender; // 1男 0女 2其它
    uint uid; // uid
};
// 简化user类型 用于登录和注册
struct user_base{
    char name[MAXLEN_NAME];
    char pwd[MAXLEN_PWD];
};
// 消息信息
struct message{
    uint n; // 大小
    uint send_uid ; // 发送者的uid
    uint groupid; //   接收者的groupid
    char *text; // 内容的指针

};
```

思路

- 客户端-服务器通信 ： 

  利用socket实现tcp协议保证数据稳定传输

  对于每个子用户fork一个子进程用来通信

  然后通信的时候将信息序列化,一条消息格式为 

  [SIZE(unsigned int)] + [type(uint)] + [context] 

  本地端和服务端阅读的时候先读一个 uint 表示判断大小 , 再读 size 个char 其中第一个uint表示消息类型,后面是正文(用户名-- UID--通信内容)

- 日志记录:写在服务端即可

- 注册 : 向服务器发送一个user_base,服务器检测账号是否被注册,返回是否注册成功

  然后再传入user类型要求填写相关信息

- 登入 : 向服务器发送一个user_base,服务器检测账号密码是否与服务器的相同,成功登入返回user类型,本地储存一下uid

- 数据库:手写一个简单数据库,用来存储日志和账号信息

  运行的时候服务器先打开一个管道 fork子进程再execve到数据库进程

- readline库

  动态链接库 编译的时候记得加上`-lreadline` 

  `readline("chat:")` 返回一个char指针

  `add_history(ptr)` 把一个char指针对应的信息加到历史文件中

- 消息发送,两个人的聊天也看做群聊,一个人向另一个人发送消息就给对应的组发消息,服务器在将组的消息转发给每个人,

  这里和数据库一样采用管道通信,服务器需要开两个线程,一个监听连接,一个读取管道文件并转发给每个子进程

  子进程也是用两个线程,一个用来接收客户端消息,一个用来接收父进程的消息并发给客户

问题:

1. 这里可能解决一下线程冲突问题,看一下jyy的操作系统课

2. 服务器需要维护一下 {groupid,组中的人员个数,组中的人员uid}

   

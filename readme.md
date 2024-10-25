# Network Programming

下面写的全没写完,只是一些大概思路

[socket 学习笔记](socket.md)

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

   

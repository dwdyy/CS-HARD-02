#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

// 该文件定义chat中用户结构体,文件结构体,各类长度
#ifndef CHAT_H
#define CHAT_H

// 名字长度
#define MAXLEN_NAME 24
// 密码长度
#define MAXLEN_PWD 24
// 消息长度
#define LEN_MESSAGE 1024

// 用于区分给服务器的不同信号

#define REGISTER_TYPE 1 // 注册信号 
#define LOGGIN_TYPE 2 // 登录信号
#define MESSAGE_TYPE 3 // 消息信号


// 用于给客户端的不同信号


#define uint unsigned int

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

struct message{
    uint n; // 大小
    uint send_uid ; // 发送者的uid
    uint groupid; //   接收者的groupid
    char *text; // 内容的指针

};



#endif

// 该文件定义简单数据库,储存用户名和密码;
#ifndef DATABASE
#define DATABASE
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
// 最大支持的用户数量-1,因为储存室下标从1开始
// 2043 支持2042 个用户
#define MAX_USER 2043
// 最多支持的群组数量-1
#define MAX_GROUP 2043
// 名字最大长度
#define NAME_LEN 1024
// 密码最大长度
#define PWD_LEN 1024
// 消息最大长度
#define MESSAGE_LEN 1024
#define USER_PATH "user.txt" 
#define LOG(name) "name/log.txt"


#define MAX(a,b) (a>b?a:b)
void build_database();
bool del_database(char *name);
bool add_database(char *name,char *pwd);
int find_name(char *name);
void init_database();


//当前用户数量

#endif
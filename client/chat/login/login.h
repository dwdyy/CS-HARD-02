// 该文件实现和服务器通信实现注册登陆服务
#include "../name/name.h"
#include "../file/file.h"
/*
    实现注册用户
    成功 0 
    错误 -1 名字已经被使用
*/
int regist();

/*

    实现登录
    成功 0 
    错误 -1 用户不存在
    错误 -2 密码错误
*/
int loggin(char *name,char *pwd); 

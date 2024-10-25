/* 用于区分给服务器的不同信号

#define REGISTER_TYPE 1 // 注册信号 
#define LOGGIN_TYPE 2 // 登录信号
#define MESSAGE_TYPE 3 // 消息信号

*/
#include "file.h"
// #define DEBUG
/*
    将user_base类型序列化
    参数: s    : userbase结构体指针
          type : 信号类型
          len : 长度指针
    返回序列化后的char指针
*/
extern int socket_fd;
char *SL_userbase(struct user_base *s,uint type,uint *len){
    *len = sizeof(s->name) + sizeof(s->pwd) + sizeof(type) + sizeof(uint); // 计算长度
    char *ar = malloc(LEN_MESSAGE); // 申请空间
    if (ar == NULL) { // 检查 malloc 是否成功
        printf("Failed to allocate memory in SL_userbase\n");
        return NULL;
    }
    memcpy(ar,len,sizeof(uint));
    memcpy(ar+sizeof(uint),&type,sizeof(type));
    memcpy(ar+sizeof(uint)+sizeof(type),s->name,sizeof(s->name));
    memcpy(ar+sizeof(uint)+sizeof(type)+sizeof(s->name),s->pwd,sizeof(s->pwd));
    return ar;
}



/*
    将user_base类型反序列化
    参数: s    : userbase结构体指针
          ar   : char数组
    成功返回0
    失败-1
*/
int DL_userbase(struct user_base *s,char *ar){
    int offest = sizeof(uint);
    memcpy(s->name,ar+offest,sizeof(s->name));
    offest+=sizeof(s->name);
    memcpy(s->pwd,ar+offest,sizeof(s->pwd));
    return 0;
}
/*
    向服务器发送数据
    参数：s 数组指针
*/
int sd(char *s,int len){
    send(socket_fd,s,len,0);
    return 1;
}
/*
    向服务器接受数据
    参数：s 数组指针
*/
int rv(char *s,int len){
    recv(socket_fd,s,LEN_MESSAGE,0);
}

#ifdef DEBUG
int main(){
    struct user_base s;int len ;
    scanf("%s",s.name);
    scanf("%s",s.pwd);
    char *t = SL_userbase(&s,REGISTER_TYPE,&len);
    struct user_base w;
    DL_userbase(&w,t);
    printf("%s\n%s",w.name,w.pwd);

}
#endif

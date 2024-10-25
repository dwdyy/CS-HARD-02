#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define LISTEN_MAX 20
#define PORT  8001
#define PROGRAM ./bin/chat 
#define MAXLEN 1024
static char buf[MAXLEN];
int main(){
    int socket_fd ,connect_fd; // 套接字
    struct sockaddr_in servaddr ; // ipv4地址
    int n ;
    memset(&servaddr,0,sizeof (servaddr));


    socket_fd = socket(AF_INET,SOCK_STREAM,0); // tcp
    if(socket_fd==-1){
        printf("Get socket wrong!");
        exit(0);
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // 所有本地ip地址
    if(bind(socket_fd,(struct sockaddr*)&servaddr,sizeof (servaddr)) == -1){
        printf("Bind socket wrong!");
        exit(0);
    }

    if(listen(socket_fd,LISTEN_MAX) == -1){
        printf("listen socket wrong!");
        exit(0);
    }

    printf("Begin Listening\n");
    printf("-----Wating for connect-----\n");
    while(1){
        connect_fd = accept(socket_fd,(struct sockaddr*)NULL,NULL);
        if(connect_fd== -1){
            printf("connect wrong!");
            exit(0);
        }
        if(fork()==0){ // 子进程
            //send(connect_fd,"Hello",5,0);
            //close(connect_fd);
            char *arg = malloc(MAXLEN);
            printf(arg,"%d",connect_fd);
            const char* argv[] = {arg,NULL};
            if(execve(PROGRAM,argv,NULL) == -1){
                printf("execve wrong!");
                free(arg);
                close(connect_fd);
                exit(0);
            }
        }
    }
    close(socket_fd);



}
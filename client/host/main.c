#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define MAXLEN 4096
#define PORT  8001

// static char recvbuf[MAXLEN],sendbuf[MAXLEN];
int socket_fd ;// 套接字
int main(int argc,char **argv){
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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(socket_fd ,(struct sockaddr*)&servaddr,sizeof (servaddr)) == -1){
        printf("connect socket wrong!");
        exit(0);
    }
    regist();
    close(socket_fd);
}
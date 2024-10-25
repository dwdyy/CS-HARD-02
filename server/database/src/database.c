#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "database.h"
int user_num ;
int group_num ;
// 这里的下标做为其编号
static char *username[MAX_USER]; // 名字
static char *userpwd[MAX_USER]; // 密码
static char TMP_FILE[10] = "tmp.txt"; 
/*
该函数用来初始化数据库,读写本地数据库文件
如果这是第一次使用,会新建数据文件
*/
void init_database(){
    user_num = group_num = 0;
    FILE *fp = fopen(USER_PATH,"r"); // 打开用户信息
    if(fp == NULL) { // 新建数据文件
        build_database();
        init_database();
        return ;
    }
    int LEN = MAX(NAME_LEN,PWD_LEN);
    char *buf= malloc(sizeof(char) * LEN);
    
    
    // buf 中最大长度位账号和密码长度取max
    while(1){
        // 读取名字和密码
        fgets(buf,LEN,fp);
        if(strcmp(buf , "END\n") == 0) break;

        username[++user_num] = buf;
        buf = malloc(sizeof(char) * LEN); // 重新申请

        fgets(buf,LEN,fp);

        userpwd[user_num] = buf;
        buf = malloc(sizeof(char) * LEN);// 重新申请
    }
    free(buf); // 释放掉最后的"END\n"
    fclose(fp);
}

/*

在数据库中通过查询USERNAME,并返回其编号,错误返回0 

*/
int find_name(char *name){
    for(int i=1;i<=user_num;i++) // 遍历查找
        if(strcmp(username[i] ,name) == 0)
            return i;
    return 0;
}
/*

往数据库里新增名字和密码

*/
bool add_database(char *name,char *pwd){

    if(find_name(name) != 0) return false;

    FILE *fp = fopen(USER_PATH,"r+"); // 打开用户信息
    int LEN = MAX(NAME_LEN,PWD_LEN);
    long pos = ftell(fp) ; // 记录文件"END”前一行的位置
    char *buf = malloc(sizeof(char) * LEN);
    while(1){
        fgets(buf,LEN,fp);
        if(strcmp(buf,"END\n") == 0){
            fseek(fp,pos,SEEK_SET); // 回到END之前
            fputs(name,fp);
            fputs(pwd,fp);
            fputs("END\n",fp);
            fclose(fp);
            free(buf);
            init_database();
            return true;
        }
        pos =ftell(fp);
    }
    free(buf);
    fclose(fp);
    fprintf(stderr,"add_database:fail");
    return false;
}
bool del_database(char *name){
    FILE *ftmp =  fopen(TMP_FILE,"w"); // 打开临时文件
    int uid = find_name(name); // 找到删除的内容
    if(uid ==0) return false;        
    for(int i=1;i<=user_num;i++){
        if(i==uid)  continue;
        fputs(username[i],ftmp);
        fputs(userpwd[i],ftmp);
    }
    fputs("END\n",ftmp);
    fclose(ftmp);
    remove(USER_PATH);
    rename(TMP_FILE,USER_PATH);
    init_database();
    return true;
}
/*

该函数新建一个数据库文件储存用户名和密码

*/
void build_database(){
    FILE *fp = fopen(USER_PATH,"w");
    fputs("END\n",fp);
    fclose(fp);
}

bool check(char *name,char *pwd){
    int x = find_name(name);
    if(x == 0) return false;
    return strcmp(pwd,userpwd[x]) ==  0;
}

// int main(){
//     init_database();
//     add_database("NIKO\n","123\n");
// }
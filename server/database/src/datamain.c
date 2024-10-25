#include <stdio.h>
#include <string.h>
#include "database.h"
int main(){
    // freopen("a.in","r",stdin);
    int LEN = MAX(NAME_LEN,PWD_LEN);
    char *name = malloc(sizeof(char) * LEN);
    char *pwd = malloc(sizeof(char) * LEN);
    init_database();
    while(1){
        memset(name,0,sizeof name);
        memset(pwd,0,sizeof pwd);
        char x;
        scanf("%c",&x);
        if(x == 'q') break;
        if(x == 'a') {
            scanf("%s%s",name,pwd);getchar();
            name[strlen(name)] = '\n';
            pwd[strlen(pwd)] = '\n';
            int y = add_database(name,pwd);
            printf("%d\n",y);
        }
        if(x=='d'){
            scanf("%s%s",name,pwd);getchar();
            name[strlen(name)] = '\n';
            pwd[strlen(pwd)] = '\n';
            int y = del_database(name);
            printf("%d\n",y);
        }
        if(x== 'c'){
            scanf("%s%s",name,pwd);getchar();
            name[strlen(name)] = '\n';
            pwd[strlen(pwd)] = '\n';
            printf("%d\n",check(name,pwd));
        }
    }
}
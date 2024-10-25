#include "login.h"

int regist(){
    struct user_base *np=malloc(sizeof(struct user_base));
    uint *len = malloc(sizeof(int));
    char *name = readline("Enter name:");
    char *pwd  = readline("Enter password");
    memcpy(np->name,name,MAXLEN_NAME);
    memcpy(np->pwd,pwd,MAXLEN_PWD);
    free(name);free(pwd);
    char *mes = SL_userbase(np,REGISTER_TYPE,len);
    sd(mes,len);
    free(len);
    return 1;
}



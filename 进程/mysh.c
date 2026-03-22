#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<glob.h>
#include<string.h>
#include<sys/wait.h>


#define DELIMS " \t\n"

struct cmd_st{
    glob_t globres;

};

//打印提示符
static void prompt(){
    printf("mysh-0.1$ ");

}

static void parse(char *line, struct cmd_st *res){
    char *tok;
    int i = 0;

    while(1){
    tok = strsep(&line, DELIMS);

    if(tok == NULL){
        //printf("error strsep");
        break;
    }

    //多个连续的分隔符出现
    if(tok[0] == '\0'){
        continue;
    }

    //i的目的就是globres里面一开始是随机的，
    // 然后一开始不追加，先覆盖一个值，再进行追加
    glob(tok, GLOB_NOCHECK|GLOB_APPEND*i, NULL, &(res->globres));
    i = 1;
    }

}

int main(){
    char *buff = NULL;
    size_t buff_size = 0;
    struct cmd_st cmd; 
    pid_t pid;

    while(1){
        prompt();

        int line = getline(&buff, &buff_size, stdin);
        if(line < 0){
            perror("getline()");
            break;
        }

        parse(buff, &cmd);

        if(0){  // 内部命令
            /*do sth*/
        }
        else{  // 外部命令
            pid = fork();

            if(pid < 0){
                perror("fork()");
                exit(1);
            }

            if(pid == 0){
                execvp(cmd.globres.gl_pathv[0], cmd.globres.gl_pathv);
                perror("execvp()");
                exit(1);
            }
            else{ // parent
                wait(NULL);
            }
        }
    }
}
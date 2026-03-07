#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<pwd.h>


int main(int argc, char **argv){
    if(argc < 2){
        fprintf(stderr,"error User.....\n");
        exit(1);
    }

    struct passwd* wd_tmp = NULL;

    // 字符串转换为整形
    wd_tmp = getpwuid(atoi(argv[1]));

    if(wd_tmp == NULL){
        perror("getpwuid()");
        exit(1);
    }

    puts(wd_tmp->pw_name);
    exit(0);
}
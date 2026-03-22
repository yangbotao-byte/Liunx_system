#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

#define PAT "/home/book/Liunx_system/file_systrem"

int main(int argc, char** argv){
    DIR* tmp = opendir(PAT);
    struct dirent *readres = NULL;

    if(tmp == NULL){
        perror("opendir()");
        exit(1);
    }

    while((readres = readdir(tmp)) != NULL){
        printf("%s\n", readres->d_name);
    }

    exit(0);
}
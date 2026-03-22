#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    puts("begin...\n");

    int tmp = execl("/bin/date", "date", "+%s", NULL);
    if(tmp < 0){
        perror("execl()");
        exit(1);
    }

    puts("end...\n");

    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char* argv[]){
    //open放置文件到3上面
    int fd = open(argv[1], O_RDWR|O_CREAT, 0644);
    if(fd < 0){
        perror("open()");
        exit(1);
    }

    // close(1);
    // dup(fd);

    dup2(fd, 1);

    close(fd);

    /*************************************/

    puts("hello");

    return 0;
}
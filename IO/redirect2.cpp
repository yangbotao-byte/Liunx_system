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

    // 关闭 输出 stream 1
    close(1);
    // 这个是将历史文件的fd复制再放一次
    // 注意这里有个原则：
    // 从最小的文件描述符进行放置
    dup(fd);
    //关闭原来的fd
    close(fd);

    /*************************************/

    puts("hello");

    return 0;
}
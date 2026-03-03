#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char* argv[]){
    // 关闭 输出 stream
    close(1);

    // 此时可以将fd放到文件描述符1上面
    // 有了open，直接放到最小的位置
    int fd = open(argv[1], O_RDWR|O_CREAT, 0644);
    if(fd < 0){
        perror("open()");
        exit(1);
    }

    /*************************************/

    puts("hello");

    return 0;
}
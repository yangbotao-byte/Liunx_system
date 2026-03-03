#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h> 
#define SIZE 1572864

int main(int argc, char* argv[]){
    if (argc < 3)
	{
		printf("Usage: ./mycp_1 srcfile desfile");
		exit(1);
	}

    int fd;  // 1 only read file
    int fs;  // 2 write

    char buff[SIZE];
    
    /*
    int open(const char *pathname, int flags, mode_t mode);
    return:
      success: file descriptor(0/1/2)
      fail: -1 and set error
    */

    fd = open(argv[1], O_RDWR, 0644);
    if(fd == -1){
        // perror 一定要是string类型
        perror("open()");
        exit(1);
    }

    fs = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fs == -1){
        perror("open()");
        close(fd);
        exit(1);
    }

    /*
    // 核心：从fd关联的文件读取数据到buf，期望读count字节
    ssize_t read(int fd, void *buf, size_t count);
    注：ssize_t 是有符号的整数类型（对应 long），
       size_t 是无符号整数类型（对应 unsigned long)
       区别是 read() 可能返回 - 1（失败），需要有符号类型表示。

    正整数	
    成功：返回实际读取到的字节数（可能 < count，比如文件剩余数据不足、管道 / 网络流中断）。
    0	成功：读到文件末尾（EOF） —— 没有更多数据可读取（比如空文件、读到文件最后 1 字节后再读）。
   -1	失败：返回 - 1，同时设置全局变量 errno（可通过 perror() 打印具体错误）。

    // 核心：把buf中的数据写入fd关联的文件，期望写count字节
    ssize_t write(int fd, const void *buf, size_t count);

    返回值	含义
    正整数	成功：返回实际写入的字节数（可能 < count，比如内核写缓冲区满、磁盘空间不足）。
    -1	失败：返回 - 1，设置 errno（常见原因和 read() 类似，核心是权限 /fd 无效 / 缓冲区非法）。
    */

    while(1){
        int read_num = read(fd, buff, SIZE);

        if(read_num < 0){
            perror("read()");
            exit(0);
        }

        if(read_num == 0){
            break;
        }

        /*
			我们先明确一个关键特性：
			write() 函数不保证一次性写入你期望的所有字节。
			比如你要求写 10 字节，但内核缓冲区满、磁盘 IO 繁忙等原因，
			可能只写入了 6 字节（wrnum=6）
			所以这里需要设计一个position
		*/

        if(read_num > 0){
            int position = 0;

            while(read_num > 0){
                int write_num = write(fs, buff + position, read_num);

                if(write_num < 0){
                    perror("write()");
                    close(fd);
                    close(fs);
                    exit(1);
                }

                read_num -= write_num;
                position += write_num;
            }
        }
    }


    /*
    int close(FILE* stream)
    0	成功：文件描述符被释放，内核回收该文件的关联资源。
   -1	失败：返回 - 1，设置errno（常见原因：fd无效 / 已关闭、权限问题）。
    */
    close(fd);
    close(fs);

}
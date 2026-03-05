#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>   // 包含 stat 结构体、stat() 函数和 S_ISxxx 宏
#include <unistd.h>     // 包含 stat() 函数的声明（部分系统需要）

// 检查文件类型并返回对应的字符
static int ftype(const char* fname)
{
    struct stat statres;

    // 获取文件状态信息
    if (stat(fname, &statres) < 0) {
        perror("stat()");
        exit(EXIT_FAILURE);
    }

    // 判断文件类型并返回对应字符
    if (S_ISREG(statres.st_mode))
        return '-';  // 普通文件
    else if (S_ISDIR(statres.st_mode))
        return 'd';  // 目录
    else if (S_ISCHR(statres.st_mode))
        return 'c';  // 字符设备
    else if (S_ISBLK(statres.st_mode))
        return 'b';  // 块设备
    else if (S_ISFIFO(statres.st_mode))
        return 'p';  // 管道（FIFO）
    else if (S_ISLNK(statres.st_mode))
        return 'l';  // 符号链接
    else if (S_ISSOCK(statres.st_mode))
        return 's';  // 套接字
    else
        return '?';  // 未知类型
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 调用 ftype 函数并打印结果
    char type = ftype(argv[1]);
    printf("File type: %c\n", type);

    return 0;
}
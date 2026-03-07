#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <glob.h>
#include <string.h>

#define PATHSIZE 1024

static int pathloop(const char* path) {
    char* position;
    // 找到最后一个 / 的位置
    position = strrchr(path, '/');

    if(position == NULL)
		exit(1);

    if (strcmp(position + 1, ".") == 0 || strcmp(position + 1, "..") == 0) {
        return 0; // 过滤 . 和 ..
    } else {
        return 1; // 正常文件/目录，需要统计
    }
}

static long long mydu(char *pathname) {
    struct stat statres;
    static char nextpath[PATHSIZE];
    glob_t globres;
    long long sum = 0; // 初始化sum，避免未定义行为
    int glob_err;      // 存储glob的返回值

    // 修正错误处理：lstat失败不直接exit，返回0（跳过该文件）
    if (lstat(pathname, &statres) < 0) {
        perror("lstat() error");
        return 0;
    }

    // 如果是目录文件，才遍历子文件
    if (S_ISDIR(statres.st_mode)) {
        memset(nextpath, 0, PATHSIZE);
        strncpy(nextpath, pathname, PATHSIZE - 1);
        
        // 处理路径末尾的 /：如果最后一个字符是/，不再拼接/
        size_t len = strlen(nextpath);
        if (len > 0 && nextpath[len - 1] != '/') {
            strncat(nextpath, "/", PATHSIZE - len - 1);
        }

        // 拼接 /*，匹配非隐藏文件
        strncat(nextpath, "*", PATHSIZE - strlen(nextpath) - 1);
        
        // 处理glob错误
        glob_err = glob(nextpath, 0, NULL, &globres);
        if (glob_err == GLOB_NOSPACE || glob_err == GLOB_ABORTED) {
            perror("glob() error");
            globfree(&globres);
            exit(1);
        }
        
        memset(nextpath, 0, PATHSIZE);
        strncpy(nextpath, pathname, PATHSIZE - 1);
        len = strlen(nextpath);
        if (len > 0 && nextpath[len - 1] != '/') {
            strncat(nextpath, "/", PATHSIZE - len - 1);
        }
        strncat(nextpath, ".*", PATHSIZE - strlen(nextpath) - 1);

        // 追加模式匹配隐藏文件，处理错误
        glob_err = glob(nextpath, GLOB_APPEND, NULL, &globres);
        if (glob_err == GLOB_NOSPACE || glob_err == GLOB_ABORTED) {
            perror("glob() error");
            globfree(&globres);
            exit(1);
        }

        for (size_t i = 0; i < globres.gl_pathc; i++) {
            if (pathloop(globres.gl_pathv[i])) {
                sum += mydu(globres.gl_pathv[i]); // 递归计算子文件的块数
            }
        }

        globfree(&globres); // 释放glob分配的内存

        sum += statres.st_blocks; // 累加当前目录自身的块数
        return sum;
    }

    // 非目录文件：直接返回自身的块数
    return statres.st_blocks;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]); // 错误输出到stderr更规范
        exit(1);
    }
    
    printf("%lld\n", mydu(argv[1])/2); 
    return 0;
}
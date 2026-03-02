#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
    read how many char in the one's text
*/


int main(int argc, char *argv[]) 
{
    if(argc != 2){
        printf("Usage: ./fseek_1 filepath");
		return 1;
    }

    //通过seek计算文件大小

	FILE *fp;
	long filesize;

	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}

    /*
    int fseek(FILE* stream, long offset, int whence);
    success is 0  
    fail is non-0
    */

    /*
    while(fseek(fp, 0, SEEK_SET) == 0){
        filesize += 1;
    }

    printf("%d", filesize);

    this is error, because this is not move
    */

    // 步骤1：把指针移到文件末尾
    fseek(fp, 0, SEEK_END);
    // 步骤2：获取指针位置 = 文件总大小
    filesize = ftell(fp);
    printf("文件总大小：%ld 字节\n", filesize);

    return 0;
}

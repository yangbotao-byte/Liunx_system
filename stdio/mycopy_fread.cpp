#include<stdio.h>
#include<stdlib.h>

#define SIZE 1200

int main(int argc, char* argv[]){
    
    FILE *fd, *fs;
    char buff[SIZE];
    int read_num;
    
    if(argc != 3){
    	printf("Use erro.....%s <fd> <fs>",argv[0]);
    	return 1;
    }

    fd = fopen(argv[1],"w");
    
    if(fd == NULL){
    	perror("fopen()");
	return 1;
    }


    fs = fopen(argv[2], "r");

    if(fs == NULL){
        perror("fopen()");
        fclose(fd);
        return 1;
    }

    while ((read_num = fread(buff, 1, SIZE, fs)) > 0) {
    // 1. fread从源文件fs读取最多SIZE个字节到buff，返回实际读取的字节数
    // 2. 只要返回值>0，说明还有内容可读，继续循环
    // 3. 当返回值=0时，说明已读到文件末尾，退出循环
    fwrite(buff, 1, read_num, fd);
    }

    fclose(fd);
    fclose(fs);
}

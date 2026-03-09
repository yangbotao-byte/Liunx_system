#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define PATH "/home/book/Liunx_system/file_and_user/1.txt"
#define BUFFSIZE 1024

int main(int argc, char **argv){

    FILE *fp = NULL;
    char buff[BUFFSIZE];
    int count = 0;
    time_t tmp;
    struct tm* mytm;
    
    fp = fopen(PATH, "a+");
    if(fp == NULL){
        perror("fopen()");
        exit(1);
    }

    while((fgets(buff, BUFFSIZE, fp)) != NULL){
        count++;
    }

    while(1){
        time(&tmp);
        mytm = localtime(&tmp);
        // strftime();
        fprintf(fp, "%-4d%d-%d-%d %d:%d:%d\n", ++count, \
			mytm->tm_year+1900, mytm->tm_mon+1, mytm->tm_mday,\
			 mytm->tm_hour, mytm->tm_min, mytm->tm_sec); // %-4d左对齐

		fflush(fp); // 手动刷新缓冲区,因为只有文件IO为行缓冲,其他的默认为全缓冲
        // /n起不到刷新缓冲区的作用了

		
		sleep(1);
    }

    fclose(fp);

    exit(0);
}
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define SIZE 1024

int main(int argc, char **argv){
    time_t tm_pos;
    char buff[SIZE];
    struct tm *tm_message;

    time(&tm_pos);
    tm_message = localtime(&tm_pos);
    strftime(buff, SIZE, "%Y-%m-%d %H:%M:%S", tm_message);
    printf("Now: %s\n", buff);

   tm_message->tm_mday += 100; // 只能加到mday上，不能加到yday上

	mktime(tm_message);

	strftime(buff, SIZE, "%Y-%m-%d %H:%M:%S", tm_message);
	printf("100 days after: %s\n", buff);

    exit(0);
}
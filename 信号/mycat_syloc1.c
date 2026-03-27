#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

static volatile int token = 0;

#define CPS 10
#define BUFSIZE CPS
#define BURST 100  // 最大值

static void alarm_handler(){
    alarm(1);
    token++;
    if(token > BURST){
        token = BURST;
    }
}

int main(int argc, char **argv)
{
	int sfd, dfd=1; // dfd为标准输出
	char buf[BUFSIZE];
	int len, ret, pos;

	if(argc < 2)
	{
		fprintf(stderr, "Usage...\n");
		exit(1); 
	}

    signal(SIGALRM, alarm_handler);
    alarm(1);

	do
	{
		sfd = open(argv[1], O_RDONLY);
		if(sfd < 0)
		{
			if(errno != EINTR)
			{
				perror("open()");
				exit(1);
			}
		}
	}while(sfd < 0);


	while(1)
	{
		while(token <= 0)
            pause();

        token--;

		// 1. 从文件读数据到缓冲区
		while((len = read(sfd, buf, BUFSIZE)) < 0)
		{
			if(errno == EINTR) continue; // 信号中断，重试读取
			perror("read()"); break;     // 真正的读取错误
		}

		if(len == 0) break; // len=0 → 读到文件末尾，退出循环

		// 2. 把缓冲区数据写入屏幕（标准输出）
		pos = 0;
		while(len > 0)
		{
			ret = write(dfd, buf + pos, len);
			if(ret < 0)
			{
				if(errno == EINTR) continue;
				perror("write()"); exit(1);
			}
			pos += ret;  // 偏移：下次从写入完成的位置继续
			len -= ret;  // 剩余未写入的长度
		}
	}

	close(sfd);

	exit(0);


}

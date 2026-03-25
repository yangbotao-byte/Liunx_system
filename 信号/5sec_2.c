#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

static volatile int loop = 1;

static void sig_handler(int s)
{

	loop = 0;

}

int main()
{
	time_t end;
	int64_t count=0;

    signal(SIGALRM, sig_handler);
	alarm(5);

	while(loop) // 每次调用time都会从内核取时间戳，比较耗时
	{
		count++;
	}

	printf("%ld", count);

	exit(0);
}

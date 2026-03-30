#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void sig_handler(int s)
{
	write(1, "!", 1);
}

int main()
{
	int i,j;
	sigset_t set, oset, saveset;


	signal(SIGINT, sig_handler);

	sigemptyset(&set);
	sigaddset(&set, SIGINT);

	// 保存初始状态
	sigprocmask(SIG_UNBLOCK, &set, &saveset);
    sigprocmask(SIG_BLOCK, &set, &oset);

	for(j = 0; j < 1000; j++)
	{
		for(i=0; i<5; i++)
		{
			write(1, "*", 1);
			sleep(1);
		}
		write(1, "\n", 1);

        sigsuspend(&oset);  // 恢复非阻塞状态 + 接受信号后恢复阻塞状态

        /*
		sigset_t tmpset;
		sigprocmask(SIG_UNBLOCK, &set, &tmpset); // 恢复非阻塞状态
		pause();
        sigprocmask(SIG_SETMASK, &tmpset, NULL); // 恢复阻塞状态
        */
	}

	// 确保进入和离开模块后，信号的行为不发生改变
	sigprocmask(SIG_SETMASK, &saveset, NULL);
}
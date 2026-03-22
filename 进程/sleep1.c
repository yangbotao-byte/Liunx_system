#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;

	puts("begin...");

	fflush(NULL);

	pid = fork();
	if(pid < 0)
	{
		perror("fork()");
		exit(1);
	}
	else if(pid == 0)
	{
		execl("/bin/sleep", "hettp","100", NULL);
		perror("exec()");
		exit(1);
	}

	wait(NULL);
	
	

	puts("end...");
	exit(0);
}
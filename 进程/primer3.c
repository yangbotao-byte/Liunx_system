#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MIN 3000000
#define MAX 3000200
#define N 3

int main()
{
        pid_t pid;

        printf("[%d]: Begin!\n", getpid());

        fflush(NULL);

        int i,j,n,m;
        int primer_flag;

        for(n = 0; n < N; n++){
            pid = fork();
            if(pid < 0)
            {
                perror("fork()");
                for(m = 0; m < n; m++){
                    wait(NULL);
                }
                exit(1);
            }

            else if(pid > 0){

            }

            else if(pid == 0){ // 子进程执行判断操作
                for(i=MIN + n; i<=MAX; i+=N)
                {                
                    primer_flag = 1;
                    for(j = 2; j <= i/2; j++){
                        if(i % j ==0){ // 能够整除，不是质数
                            primer_flag = 0;
                            break;
                            }
                    }
                    if(primer_flag == 1){
                    printf("%d is primer\n", i);
                    }
                }
            exit(0);
            }
        }

        for(n=0; n < N; n++){
           wait(NULL);  
        }

        printf("[%d]: End!\n", getpid());
        exit(0);
}
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h> 
#include<syslog.h>
#include<errno.h>
#include<string.h>
#include<signal.h>


#define FNAME "/tmp/out"

static FILE* fp;

static int daemonize(){

    pid_t pid;
    int fd;

    pid = fork();
    if(pid < 0){
        // perror("fork()");
        return -1;
    }

    if(pid > 0){  // 父进程直接退出
        exit(0);
    }

    // 重定向输入输出到 /dev/null（丢弃所有终端输出）
    fd = open("/dev/null",O_RDWR);
    if(fd < 0){
        // perror("open()");
        return -1;
    }

    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);
    if(fd > 2)
        close(fd);

    setsid();  // 创建新会话，脱离终端

    chdir("/"); // 切换工作目录到根目录，防止占用磁盘

    return 0;
}

static void daemo_exit(int s){
    // 整形s就是为了处理多个信号公用同一个函数
    fclose(fp);
    closelog();
    exit(0);

}

int main(){
    struct sigaction sa;

    sa.sa_handler = daemo_exit;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGINT); 
    sigaddset(&sa.sa_mask, SIGQUIT);
    sigaddset(&sa.sa_mask, SIGTERM);

    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);


    // signal(SIGINT, daemo_exit);
    // signal(SIGQUIT, daemo_exit);  
    // signal(SIGTERM, daemo_exit);


    //我接下来要打日志了，我的名字叫 
    // mydaemon，日志带上 PID，我是守护进程类型的程序！
    openlog("mydaemon", LOG_PID, LOG_DAEMON);

    if(daemonize()){
        //补药写\n，因为格式是syslog服务决定的
        syslog(LOG_ERR, "daemonize() failed!");
        exit(1);
    }
    else{
        syslog(LOG_INFO, "daemonize() successded!");
    }

    fp = fopen(FNAME, "w");
    if(fp == NULL){
        // perror("fopen()");
        syslog(LOG_ERR, "fopen():%s", strerror(errno));
        exit(1);
    }

    syslog(LOG_INFO, "%s was opend.", FNAME);

    // 死循环，每秒写入数字
    for(int i = 0; ;i++){
        fprintf(fp,"%d\n", i);
        fflush(NULL); // 刷新缓冲区，立即写入文件
        syslog(LOG_DEBUG, "%d is printed.", i);
        sleep(1);
    }

    exit(0);
}
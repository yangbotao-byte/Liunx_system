#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

#include "anytimer.h"

struct at_job_st{
    int job_state;
    int sec;
    int time_remain;    
    at_jobfunc_t *jobp;
    void* arg;
};

static struct at_job_st* job[JOB_MAX];
//定时器模块 信号注册+setitimer启动只需初始化1次
static int inited = 0; 
//保存系统原来的 SIGALRM 信号处理方式
static struct sigaction alrm_sa_save;

static void model_load(void){
    /*
     Linux 信号编程的专用结构体，作用是：
     告诉操作系统，收到某个信号时，要执行哪个函数、用
     什么方式执行, 就是sigaction里面的类型
     */
     
    struct sigaction sa;
    struct initmerval itv;

    sa.sa_sigaction = alrm_action;

}

int at_addjob(int sec, at_jobfunc_t *jobp, void *arg){
    int pos;
    struct at_job_st *me;

    if(sec < 0){
        return -EINVAL;
    }
    
    if(!inited){
        model_load();
        inited = 1;
    }
}
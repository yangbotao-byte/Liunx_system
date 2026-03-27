#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "mytbf.h"  // 必须包含头文件！

// 系统已有 sighandler_t，删除自定义定义
static struct mytbf_st *job[MYTBF_MAX];
static int inited = 0;
static void (*alrm_handler_save)(int);  // 修复信号指针类型

// 令牌桶结构体
struct mytbf_st
{
    int cps;
    int burst;
    int token;
    int pos;
};

// 统一函数名：alrm_handler
static void alrm_handler(int s)
{
    int i;
    alarm(1);

    for(i = 0; i < MYTBF_MAX; i++)
    {
        if(job[i] != NULL)
        {
            job[i]->token += job[i]->cps;
            if(job[i]->token > job[i]->burst)
                job[i]->token = job[i]->burst;
        }
    }
}

// 修复拼写错误：module_unload
static void module_unload(void)
{
    int i;
    signal(SIGALRM, alrm_handler_save);
    alarm(0);
    for(i = 0; i < MYTBF_MAX; i++)
        free(job[i]);
}

static void module_load(void)
{
    // 保存原信号处理函数
    alrm_handler_save = signal(SIGALRM, alrm_handler);
    alarm(1);
    atexit(module_unload);
}

static int get_free_pos(void)
{
    int i;
    for(i = 0; i < MYTBF_MAX; i++)
    {
        if(job[i] == NULL)
            return i;
    }
    return -1;
}

mytbf_t *mytbf_init(int cps, int burst)
{
    struct mytbf_st *me;
    int pos;

    if(!inited)
    {
        module_load();
        inited = 1;
    }

    pos = get_free_pos();
    if(pos < 0)
        return NULL;

    // 修复拼写错误：melloc → malloc
    // 修复大小：sizeof(*me) 不是 sizeof(me)
    me = malloc(sizeof(*me));
    if(me == NULL)
        return NULL;

    me->token = 0;
    me->cps = cps;
    me->burst = burst;
    me->pos = pos;

    job[pos] = me;

    return me;
}

static int min(int a, int b)
{
    return a < b ? a : b;
}

int mytbf_fetchtoken(mytbf_t *ptr, int size)
{
    struct mytbf_st *me = ptr;
    int n;

    if(size <= 0)
        return -EINVAL;

    while(me->token <= 0)
        pause();

    n = min(me->token, size);
    me->token -= n;
    return n;
}

int mytbf_returntoken(mytbf_t *ptr, int size)
{
    struct mytbf_st *me = ptr;

    if(size <= 0)
        return -EINVAL;

    me->token += size;
    if(me->token > me->burst)
        me->token = me->burst;

    return size;
}

int mytbf_destroy(mytbf_t *ptr)
{
    struct mytbf_st *me = ptr;
    job[me->pos] = NULL;
    free(ptr);
    return 0;
}
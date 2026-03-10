#include<stdio.h>
#include<stdlib.h>
#include<setjmp.h>

static jmp_buf save1;

void d(){
    printf("%s():Begin.\n", __FUNCTION__);
    printf("%s():Begin Jump.\n",__FUNCTION__);
    longjmp(save1, 9);
    
    printf("%s():End.\n", __FUNCTION__);
}

void c(){
    printf("%s():Begin.\n", __FUNCTION__);
    printf("%s():Call d().\n", __FUNCTION__);
    d();
    printf("%s():d() returned", __FUNCTION__);
    printf("%s():End.\n", __FUNCTION__);
}

void b(){
    printf("%s():Begin.\n", __FUNCTION__);
    printf("%s():Call c().\n", __FUNCTION__);
    c();
    printf("%s():c() returned", __FUNCTION__);
    printf("%s():End.\n", __FUNCTION__);
}

void a(){

    int ret;

    printf("%s():Begin.\n", __FUNCTION__);
    printf("%s():Call b().\n", __FUNCTION__);

    ret = setjmp(save1);
    if(ret == 0){
        printf("%s():Call b().\n", __FUNCTION__);
        b();
        printf("%s():b() returned", __FUNCTION__);
    }
    else{
        printf("%s():Jumped back here with code %d\n", __FUNCTION__, ret);
    }

    printf("%s():End.\n", __FUNCTION__);
}

int main(){

    printf("%s():Begin.\n", __FUNCTION__);
    printf("%s():Call a().\n", __FUNCTION__);
    a();
    printf("%s():a() returned", __FUNCTION__);
    printf("%s():End.\n", __FUNCTION__);

    exit(0);
}
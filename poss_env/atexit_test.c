#include <stdio.h>
#include <stdlib.h>


static void f1(void)
{
	puts("f1() is working!");
}

static void f2(void)
{
	puts("f2() is working!");
}

static void f3(void)
{
	puts("f3() is working!");
}

int main()
{
	puts("Begin!");

	// 不是函数调用，注册和调用顺序相反，在进程即将正常退出时调用
	// 有点像线程清理函数，注册和清理的顺序相反
	atexit(f1);
	atexit(f2);
	atexit(f3);

	puts("End!");

	exit(0);

}
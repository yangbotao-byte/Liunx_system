#include<stdio.h>
#include<stdlib.h>
#include<glob.h>
#include<string.h>
#include <sys/stat.h>   // 包含 stat 结构体、stat() 函数和 S_ISxxx 宏
#include <unistd.h>     // 包含 stat() 函数的声明（部分系统需要）

#define PATH "/etc/*"

static int errfunc (const char *epath, int eerrno)
{
	puts(epath);
	fprintf(stderr, "ERROR MSG: %s\n", strerror(eerrno));

}


int main(int argc, char** argv){
    glob_t glob_tmp;
    int ret = glob(PATH, 0, NULL, &glob_tmp);

        // 检查返回值，失败则退出
    if (ret != 0) {
        printf("Error code = %d", ret);
		exit(1);
    }

    for(int i = 0; i < glob_tmp.gl_pathc; i++){
        printf("%s\n", glob_tmp.gl_pathv[i]);
    }

    globfree(&glob_tmp);
}
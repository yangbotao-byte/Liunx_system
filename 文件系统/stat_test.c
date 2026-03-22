#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// 注意返回值
static off_t myflen(const char* filename){

    struct stat buff;
    stat(filename, &buff);

    return buff.st_size;
}


int main(int argc, char** argv){
    int fd;
	if(argc < 2)
	{
		fprintf(stderr, "Usage..\n");
		exit(1);
	}

    printf("%lld\n", (long long)myflen(argv[1]));

	exit(0);
}

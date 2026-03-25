#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h> 
#define SIZE 1572864

int main(int argc, char* argv[]){
    if (argc < 3)
	{
		printf("Usage: ./mycp_1 srcfile desfile");
		exit(1);
	}

    int fd;  // 1 only read file
    int fs;  // 2 write

    char buff[SIZE];

    do{
        fd = open(argv[1], O_RDWR, 0644);
        if(fd != EINTR){
            if(fd == -1){
                // perror 一定要是string类型
                perror("open()");
                exit(1);
            }
        }
    }
    }whlile(fd < 0);

    fs = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fs == -1){
        perror("open()");
        close(fd);
        exit(1);
    }

    while(1){
        int read_num = read(fd, buff, SIZE);

        if(read_num < 0){
            perror("read()");
            exit(0);
        }

        if(read_num == 0){
            break;
        }

        if(read_num > 0){
            int position = 0;

            while(read_num > 0){
                int write_num = write(fs, buff + position, read_num);

                if(write_num < 0){
                    perror("write()");
                    close(fd);
                    close(fs);
                    exit(1);
                }

                read_num -= write_num;
                position += write_num;
            }
        }
    }


    close(fd);
    close(fs);

}
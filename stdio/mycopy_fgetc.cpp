#include<stdio.h>
#include<stdlib.h>

#define SIZE 1200

int main(int argc, char* argv[]){
    
    FILE *fd, *fs;
    char buffer[SIZE];
    /*
    use this way, if parameter != 3, 
    get a error printf managers
    end return
    */
    
    if(argc != 3){
    	printf("Use erro.....%s <fd> <fs>",argv[0]);
    	return 1;
    }

    /*
    check the FILE pointer is NULL
    fopen return a FILE*
    */

    fd = fopen(argv[1],"w");
    if(fd == NULL){
    	perror("fopen()");
	return 1;
    }

    fs = fopen(argv[2], "r");

    if(fs == NULL){
        perror("fopen()");
        fclose(fd);
        return 1;
    }

    /*
    fgets() return a youself define a buffer array pointer, kind is a char*
    char* fgets(buffer, SIZE, read file)
    check pointer is NULL


    fputs return int, kinds is success or fail
    int fputs(buffer, wirt file)
    */

    while(fgets(buffer, SIZE, fs) != NULL)
	fputs(buffer, fd);

    fclose(fd);
    fclose(fs);
    
    return 0;
}

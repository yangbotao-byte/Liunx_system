#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
    
    FILE *fd, *fs;
    int ch;
    
    if(argc != 3){
    	printf("Use erro.....%s <fd> <fs>",argv[0]);
    	return 1;
    }

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

    while((ch = fgetc(fs)) != EOF)
	fputc(ch, fd);

    fclose(fd);
    fclose(fs);
    
    return 0;
}

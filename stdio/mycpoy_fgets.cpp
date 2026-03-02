#include<stdio.h>
#include<stdlib.h>

#define SIZE 1200


int main(int argc, char* argv[]){
    FILE* fp, *fd;
    char buff[SIZE];

    if(argc != 3){
        printf("Use erro.....%s <fd> <fs>",argv[0]);
    	return 1;
    }

    // fopen w and r not is char, is string 
    fp = fopen(argv[1], "w");
    if(fp == NULL){
        printf("Use erro.....%s <fd> <fs>",argv[0]);
    	return 1;
    }

    fd = fopen(argv[2], "r");
    if(fd == NULL){
        fclose(fp);
        printf("Use erro.....%s <fd> <fs>",argv[0]);
    	return 1;
    } 

    /*
    char *fgets(char *buf, int n, FILE *stream);
     myself definded buffer arrays ,read (n - 1) characters, read file
     
    */

    /*
       input:
       when meet '/n', fgets is end
       only get a line
    */

    if(fgets(buff, SIZE, fd) == NULL){
        printf("fgets is NULL\n");
        fclose(fp);
        fclose(fd);
        return 1;
    }

    fputs(buff, fp);

    fclose(fp);
    fclose(fd);

    return 0;
}
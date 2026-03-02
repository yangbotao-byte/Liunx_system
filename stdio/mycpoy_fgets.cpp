#include<stdio.h>
#include<stdlib.h>

#define SIZE 1200


int main(int argc, char* argv[]){
    FILE* fp, fd

    if(argc != 3){
        printf("Use erro.....%s <fd> <fs>",argv[0]);
    	return 1;
    }


    fp = fopen(argv[1], 'w');
    if(fp == NULL){
        printf("Use erro.....%s <fd> <fs>",argv[0]);
    	return 1;
    }

    fs = fopen(argv[2], 'r');
    if(fs == NULL){
        fclose(fp);
        printf("Use erro.....%s <fd> <fs>",argv[0]);
    	return 1;
    } 

    /*
    
    
    */


}
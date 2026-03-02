#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
	/*
	If the input is incorrect,
	report an error
	*/
	if (argc < 2)
	{
		printf("miss filename\n");
	}

	/*
	fopen return FILE*
	*/

	FILE *fp = NULL;

	/*
	fp get a FILE* use fopen 
	*/

	fp = fopen(argv[1], "r+");
	if (fp == NULL)
	{
		perror("fopen()");
		return -1;
	}
	fwrite('bbb', 1, 3, fp);
	fclose(fp);
	

}

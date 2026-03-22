#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <shadow.h>
#include <string.h>
#include <crypt.h>


int main(int argc, char** argv){
    char *password = NULL;
    struct spwd *message = NULL;

    if(argc < 2){
        fprintf(stderr, "User error....");
        exit(1);
    }

    password = getpass("input your password:");

    message = getspnam(argv[1]);

    char* new_pass = message->sp_pwdp;

    char* crypted_pass = crypt(password, new_pass);

    if(strcmp(crypted_pass,message->sp_pwdp) == 0)
	{
		printf("password succ.\n");
	}
	else{
		printf("password fail.\n");
	}

	

	exit(0);
}


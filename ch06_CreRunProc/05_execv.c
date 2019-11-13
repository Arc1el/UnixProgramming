#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void)
{
        char *my_argv[3];
        printf("Before exec fuction\n");

        my_argv[0]="ls";
        my_argv[1]="-a";
        my_argv[2]=NULL;

        if(execv("/usr/bin/ls", my_argv) ==-1)
        {
                perror("execv");
                exit(1);
        }

        printf("After exec function\n");

        return 0;
}

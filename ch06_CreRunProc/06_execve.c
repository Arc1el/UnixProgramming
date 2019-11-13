#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void)
{
        char *my_argv[3];
        char *my_envp[2];

        printf("Before exec fuction\n");

        my_argv[0] = "./06_execve_arg.exe";
        my_argv[1] = "100";
        my_argv[2] = NULL;

        my_envp[0] = "MYENV=UNIX2TEST";
        my_envp[1] = NULL;

        if(execve("./06_execve_arg.exe", my_argv, my_envp)==-1)
        {
                perror("execve");
                exit(1);
        }
        printf("After exec function\n");

        return 0;
}
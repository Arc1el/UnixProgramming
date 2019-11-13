#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/errno.h>
#include<string.h>

int main(int argc, char *argv[])
{
        if(argc!=2)
        {
                fprintf(stderr,"Usage : %s pid\n", argv[0]);
                exit(1);
        }

        int target_pid=atoi(argv[1]);

        printf("PID : %d\n", (int)getpid());
        printf("PGRP : %d\n", (int)getpgrp());
        printf("PGID(0) : %d\n", (int)getpgid(0));
        printf("PGID(%d) : %d\n", target_pid, (int)getpgid(target_pid));
        fprintf(stdout,"%s\n",strerror(errno));
        return 0;
}